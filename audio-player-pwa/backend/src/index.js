const HTTPS = require("https");
const FS = require("fs");
const Express = require("express");
const Cors = require("cors");
const BodyParser = require("body-parser");

const Server = Express();
const Port = 3001;
const Domain = "10.0.0.36";

const StreamRoute = require("./routes/stream.js");

const ServerOptions = {
    key: FS.readFileSync("../frontend/https/10.0.0.36.key"),  
    cert: FS.readFileSync("../frontend/https/10.0.0.36.crt") 
};

Server.use(Cors({
    origin: "*",
    credentials: true
}));

Server.use(BodyParser.json());

Server.use((_, Response, Next) => {
    Response.header("Access-Control-Allow-Credentials", true);
    Next();
});

Server.use(StreamRoute);

HTTPS.createServer(ServerOptions, Server).listen(Port, Domain, () => {
    console.log("Server is now listening to https://" + Domain + ":" + Port);
})