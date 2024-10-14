const { SlashCommandBuilder, EmbedBuilder } = require("discord.js");

const Path = require("path");

const FileName = Path.basename(__filename).replace(/\.js$/, '');
const UppercaseFileName = FileName.charAt(0).toUpperCase() + FileName.slice(1);

const Content = {
    Category: "Skill", 
    Name: `${UppercaseFileName}`, 
    Cmd: `/${FileName}`,  
    Description: "Plant, grow, and harvest crops and provides info on how to farm and the different types of crops."
};

module.exports = {
    Content,

    Data: new SlashCommandBuilder()
        .setName(FileName)
        .setDescription(Content.Description),

    async execute(Interaction) {}
};