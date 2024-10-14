const { Client, IntentsBitField, Collection } = require("discord.js");

const FileSystem = require('node:fs');
const Path = require('node:path');

const { Token } = require("../config.json");

const UserClient = new Client({
    intents: [
        IntentsBitField.Flags.Guilds,
        IntentsBitField.Flags.GuildMembers,
        IntentsBitField.Flags.GuildMessages,
        IntentsBitField.Flags.GuildMessageTyping,
        IntentsBitField.Flags.MessageContent,
        IntentsBitField.Flags.GuildMessageReactions
    ]
});

UserClient.commands = new Collection();

const CommandsPath = Path.join(__dirname, "./cmds");
const CommandFiles = FileSystem.readdirSync(CommandsPath).filter(File => File.endsWith(".js"));

for (const file of CommandFiles) {
    const Command = require(Path.join(CommandsPath, file));

    UserClient.commands.set(Command.Data.name, Command);
};

UserClient.on("ready", (ClientInfo) => {
    console.log(ClientInfo.user.tag, "is now online.");
});

UserClient.on("interactionCreate", async Interaction => {
    if (!Interaction.isCommand()) {
        return;
    };

    const Command = UserClient.commands.get(Interaction.commandName);

    if (!Command) {
        return;
    };

    try {
        await Command.execute(Interaction);
    } catch (Error) {
        console.error("There was an error while executing this command:", Error);

        await Interaction.reply({ content: "There was an error while executing this command.", ephemeral: true });
    }
});

UserClient.login(Token);