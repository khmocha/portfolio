const { Collection } = require("discord.js");

const FileSystem = require("fs");
const Path = require("path");

const CommandsPath = Path.join(__dirname, "../../cmds");
const CommandDirectories = FileSystem.readdirSync(CommandsPath);

const CommandsData = [];
const Commands = new Collection();

for (const Directory of CommandDirectories) {
    const DirectoryPath = Path.join(CommandsPath, Directory);

    const DirectoryFiles = FileSystem.readdirSync(DirectoryPath);

    for (const File of DirectoryFiles) {
        const FilePath = Path.join(DirectoryPath, File);
        const Command = require(FilePath);

        CommandsData.push(Command.Data.toJSON());
        Commands.set(Command.Data.name, Command);
    }
}

module.exports = { CommandsData, Commands };