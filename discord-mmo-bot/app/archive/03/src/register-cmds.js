const { REST, Routes } = require('discord.js');

const { Token, ClientID, GuildID } = require("../config.json");

const FileSystem = require("fs");
const Path = require("path");

const CommandsPath = Path.join(__dirname, "./cmds");
const CommandFiles = FileSystem.readdirSync(CommandsPath);

const Commands = [];

for (const File of CommandFiles) {
    const FilePath = Path.join(CommandsPath, File);

    const Command = require(FilePath);

    Commands.push(Command.Data.toJSON());
};

console.log(Commands);

const ClientREST = new REST({ version: "10" }).setToken(Token);

(async () => {
    try {
        await ClientREST.put(
            Routes.applicationGuildCommands(ClientID, GuildID),
            { body: Commands },
        );

        console.log("Successfully updated slash commands.");
    } catch (Error) {
        console.error("There was an error while updating slash commands:", Error);
    }
})();
