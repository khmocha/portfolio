const Express = require("express");
const YTDL = require("@distube/ytdl-core"); // YouTube downloader
const https = require("https");
const { PassThrough } = require('stream')
const ffmpeg = require("fluent-ffmpeg");

const Router = Express.Router();

Router.get("/stream", async (req, res) => {
  const YoutubeURL = req.query.url; // Get YouTube URL from query parameter

  if (!YoutubeURL) {
    return res.status(400).send("No URL provided");
  }

  try {
    const info = await YTDL.getInfo(YoutubeURL);

    const audioFormats = YTDL.filterFormats(info.formats, 'audioonly');

    audioFormats.forEach(format => {
      console.log(`  - MimeType: ${format.mimeType} ${format.filesize}`);
    });

    const audioMp4Format = audioFormats.find(format => 
        format.mimeType.startsWith('audio/mp4') || format.mimeType.startsWith("audio/mpeg")
        || format.mimeType.startsWith("audio/wav")
    );

    if (!audioMp4Format) {
        return res.status(500).send("No suitable audio/mp4 format found");
    }

    const AudioStream = YTDL(YoutubeURL, { 
      format: audioMp4Format,
      begin: 10000,
      end: 30000
    });

    const chunks = [];
    let totalBytes = 0;

    AudioStream.on('data', chunk => {
      chunks.push(chunk);
      totalBytes += chunk.length;
    });

    AudioStream.on('end', () => {
        console.log("Audio stream ended.");

        res.setHeader("Content-Type", audioMp4Format.mimeType.split(';')[0]);
        res.setHeader("Content-Length", totalBytes);

        const buffer = Buffer.concat(chunks);
        res.send(buffer);
    });

    AudioStream.on('error', (error) => {
        console.log("Error streaming audio", error);
        res.status(500).send("Error streaming audio");
    });

    /*res.setHeader("Content-Type", audioMp4Format.mimeType.split(';')[0]);
    res.setHeader('Transfer-Encoding', 'chunked');
    AudioStream.pipe(res);*/

  } catch (error) {
    console.log("Error streaming audio", error);
    res.status(500).send("Error streaming audio");
  }
});

async function getContentLength(requestUrl) {
  return new Promise((resolve, reject) => {
      const req = https.request(requestUrl, { method: 'HEAD' }, (res) => {
          const contentLength = res.headers['content-length'];

          if (contentLength) {
              //console.log(`Content-Length: ${contentLength} bytes`);
              resolve(parseInt(contentLength));
          } else {
              reject(new Error('Content-Length not found'));
          }
      });

      req.on('error', reject);  // Handle request errors
      req.end();  // End the request
  });
}

Router.get("/streamseeking", async (Req, Res) => {
  try {
    const url = Req.query.url;

    //const range = Req.headers.range || "bytes=0-";
    //const startBytes = parseInt(range.replace(/bytes=/, "").split("-")[0]);
    //console.log("range:", range, startBytes);

    const info = await YTDL.getInfo(url);

    const format = YTDL.chooseFormat(info.formats, {
        filter: (format) => 
        !format.hasVideo &&
        format.hasAudio && 
        format.container === 'mp4' && 
        format.audioCodec === 'mp4a.40.2'
    });

    if (format) {
        const requestUrl = format.url;

        //const contentLength = await getContentLength(requestUrl);

        //const endBytes = contentLength - 1;
        //const partSent = endBytes - 0 + 1;
        //Res.setHeader("Content-Range", `bytes ${0}-${endBytes}/${contentLength}`);

        //Res.setHeader("Content-Length", contentLength);

        Res.setHeader("Content-Type", format.mimeType.split(';')[0]);
        Res.setHeader('Transfer-Encoding', 'chunked');
        Res.setHeader("Accept-Ranges", "bytes");
        Res.setHeader("Cache-Control", "no-cache");
        Res.setHeader("Pragma", "no-cache");

        const stream = YTDL(url, { format });

        stream.on('error', (err) => {
          console.error("Stream Error:", err);
          Res.status(500).send("Error streaming audio");
        });
  
        stream.pipe(Res);
    } else {
      Res.status(404).send('No suitable format found');
    }
  } catch (Error) {
    console.log("Error streaming audio", Error);
    Res.status(500).send("Error streaming audio");
  }
});

Router.get("/stream-seeking2", async (req, res) => {
  try {
    const url = req.query.url;

    const info = await YTDL.getInfo(url);

    const format = YTDL.chooseFormat(info.formats, {
      filter: (format) => 
        !format.hasVideo &&
        format.hasAudio && 
        format.container === 'mp4' && 
        format.audioCodec === 'mp4a.40.2'
    });

    console.log(format.mimeType);

    // Create a PassThrough stream to pipe the output to the client
    const passthrough = new PassThrough();

    // Set the response headers
    res.header('Content-Type', 'audio/mp4');
    res.header('Cache-Control', 'no-cache');

    // Pipe the passthrough stream to the response
    passthrough.pipe(res);

    // Create a readable stream from ytdl-core
    const ytdlStream = YTDL(url, { format });

    // Create an ffmpeg command
    const command = ffmpeg()
      .input(ytdlStream)
      .format('mp4') // Set the output format to MP4
      .audioCodec('aac'); // Set the audio codec to AAC

    // Pipe the ffmpeg output to the passthrough stream
    command.pipe(passthrough, { end: true });


    } catch (Error) {
      console.log("Error streaming audio", Error);
      res.status(500).send("Error streaming audio");
    }
});

Router.get("/test", async (req, res) => {
    res.send("hey");
})

module.exports = Router;