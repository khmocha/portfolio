const FileSystem = require("fs");
const Path = require("path");

const MessageObjectsDirectory = Path.join(__dirname, "../msg-objs");
const MessageObjects = {};

FileSystem.readdirSync(MessageObjectsDirectory).forEach(File => {
    const MessageObjectsPath = Path.join(MessageObjectsDirectory, File);
    const FileName = Path.basename(File, ".js");
    const MessageObjectName = "Display" + FileName.charAt(0).toUpperCase() + FileName.slice(1);

    Object.defineProperty(MessageObjects, MessageObjectName, {
        enumerable: true,
        get: function () {
            return require(MessageObjectsPath);
        }
    });
});

module.exports = MessageObjects;