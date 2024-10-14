const { REST, Routes } = require('discord.js');

const { Token, ClientID, GuildID } = require("../config.json");
const { CommandsData } = require("./modules/general/get-cmds.js");

const ClientREST = new REST({ version: "10" }).setToken(Token);

(async () => {
    await ClientREST.put(
        Routes.applicationGuildCommands(ClientID, GuildID),
        { body: CommandsData },
    );

    console.log("Successfully updated slash commands.");
})();