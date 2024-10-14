const { SlashCommandBuilder, EmbedBuilder } = require("discord.js");

const Path = require("path");

const FileName = Path.basename(__filename).replace(/\.js$/, '');
const UppercaseFileName = FileName.charAt(0).toUpperCase() + FileName.slice(1);

const Content = {
    Category: "Non-Skill", 
    Name: `${UppercaseFileName}`, 
    Cmd: `/${FileName}`, 
    Description: "Make potions and provides the recipes for making different potions and their effects."
};

module.exports = {
    Content,

    Data: new SlashCommandBuilder()
        .setName(FileName)
        .setDescription(Content.Description),

    async execute(Interaction) {}
};