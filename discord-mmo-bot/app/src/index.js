const { Client, IntentsBitField } = require("discord.js");

const { private } = require("../config.json");
const { Commands } = require("./modules/general/get-cmds.js");

const UserClient = new Client({
    intents: [
        IntentsBitField.Flags.Guilds,
        IntentsBitField.Flags.GuildMembers,
        IntentsBitField.Flags.GuildMessages,
        IntentsBitField.Flags.GuildMessageTyping,
        IntentsBitField.Flags.MessageContent
    ]
});

UserClient.commands = Commands;

UserClient.on("ready", (ClientInfo) => {
    console.log(ClientInfo.user.tag, "is now online.");
});

UserClient.on("interactionCreate", Interaction => {
    try {
        if (!Interaction.isCommand()) {
            return;
        };

        const Command = UserClient.commands.get(Interaction.commandName);

        if (!Command) {
            console.error(`The command "${Interaction.commandName}" was not found.`);

            return Interaction.reply({ content: "There was an error while executing this command.", ephemeral: true });
        };

        Command.execute(Interaction);
    } catch (Error) {
        console.error("There was an error while executing this command:", Error);

        return Interaction.reply({ content: "There was an error while executing this command.", ephemeral: true });
    }
});

//UserClient.login(private);