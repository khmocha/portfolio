const { SlashCommandBuilder, EmbedBuilder } = require("discord.js");

const FileSystem = require("fs");
const Path = require("path");

const FileName = Path.basename(__filename).replace(/\.js$/, '');

const CommandsPath = Path.join(__dirname, "../cmds");
const CommandFiles = FileSystem.readdirSync(CommandsPath).filter(File => !File.startsWith("help"));

const Commands = [];

for (const File of CommandFiles) {
    const FilePath = Path.join(CommandsPath, File);

    const Command = require(FilePath);

    Commands.push(Command.Content);
};

const GenerateCategoryList = (Category, CategoryTitle = "") => {
    let List = CategoryTitle;

    Commands.forEach(Command => {
        if (Command.Category === Category) {
            List += `- ${Command.Name} \`${Command.Cmd}\`: ${Command.Description}\n\n`;
        }
    }) 

    return List;
};

const HelpDescription = "TypeQuest is a RPG with a blend of type racing for each action that you make. "
+ "The performance of your type race and the contribution of your stats determine the outcome of your action. "
+ "These actions can occur in various activities. All commands including the activities are listed below.\n"
+ `${GenerateCategoryList("General", "### Commands:\n")}`
+ `${GenerateCategoryList("Non-Skill", "**Non-Skill Activities (activities that are not dependent on a skill level):**\n")}` 
+ `${GenerateCategoryList("Skill", "**Skill Activities:**\n")}`;

const HelpEmbed = new EmbedBuilder()
    .setAuthor({ name: "TypeQuest | Help Page" })
    .setTitle("Introduction")
    .setThumbnail("https://i.imgur.com/AYJZrku.png")
    .setDescription(HelpDescription)
    .setColor("#000000");

module.exports = {
    Data: new SlashCommandBuilder()
        .setName(FileName)
        .setDescription("Provides useful information and commands for this bot."),

    async execute(Interaction) {
        await Interaction.reply({ embeds: [HelpEmbed ], ephemeral: true });
    }
};