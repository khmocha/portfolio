const Express = require("express");
const Mongoose = require("mongoose");
const BodyParser = require("body-parser");
const FileSystem = require("fs");
const Path = require("path");

const { Username, Password } = require("../config.json");

const Server = Express();
const Port = 3000;

const DataBaseURI = `mongodb+srv://${Username}:${Password}@TypeQuest.oigrn0g.mongodb.net/TypeQuestDB`;

const RoutesPath = Path.join(__dirname, "./routes");

Server.use(BodyParser.json());

FileSystem.readdirSync(RoutesPath).forEach(File => {
    const RoutePath = Path.join(RoutesPath, File);
    const Route = require(RoutePath);

    Server.use(Route);
});

Mongoose.connect(DataBaseURI).then(() => {
    Server.listen(Port, () => {
        console.log("Connected to TypeQuestDB. Server is now listening on port", Port);
    })
}).catch(Error => {
    console.log("An error occurred while connecting to MongoDB:", Error);
});