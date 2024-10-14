require("dotenv").config();

const { REST, Routes, ApplicationCommandOptionType } = require("discord.js");

const Commands = [
    {
        name: "hey",
        description: "Responds with Hi!"
    }, 

    {
        name: "add",
        description: "Add two numbers",
        options: [
            {
                name: "first-number",
                description: "The first number",
                type: ApplicationCommandOptionType.Number,
                choices: [
                    {
                        name: "1",
                        value: 1
                    },

                    {
                        name: "2",
                        value: 2
                    },

                    {
                        name: "3",
                        value: 3
                    }
                ],
                required: true
            },

            {
                name: "second-number",
                description: "The second number",
                type: ApplicationCommandOptionType.Number,
                required: true
            }
        ]
    },

    {
        name: "embed",
        description: "Sends an embed!"
    },

    {
        name: "add-role",
        description: "Add a role"
    },

    {
        name: "typerace",
        description: "Type race"
    },

    {
        name: "send",
        description: "Send another message"
    },

    {
        name: "typerace2",
        description: "Actual type racing unlike the original command"
    },

    {
        name: "show-pets",
        description: "Show a menu drop down of pets"
    },

    {
        name: "react",
        description: "react to different emojis and see what happens"
    }
];

const UserREST = new REST({ version: "10" }).setToken(process.env.TOKEN);

(async () => {
    try {
        await UserREST.put(
            Routes.applicationCommands(process.env.CLIENT_ID),
            {body: Commands}
        )

        console.log("Slash commands were registered successfully")
    } catch (Error) {
        console.log("An error occurred while registering slash commands:", Error);
    }
})();