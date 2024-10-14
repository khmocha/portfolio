const { SlashCommandBuilder, EmbedBuilder } = require("discord.js");

const Path = require("path");

const FileName = Path.basename(__filename).replace(/\.js$/, '');
const UppercaseFileName = FileName.charAt(0).toUpperCase() + FileName.slice(1);

const Content = {
    Category: "Skill", 
    Name: `${UppercaseFileName}`, 
    Cmd: `/${FileName}`, 
    Description: "Fish and find treasure and provides info on how fishing works and the various loot you can get."
};

module.exports = {
    Content,

    Data: new SlashCommandBuilder()
        .setName(FileName)
        .setDescription(Content.Description),

    async execute(Interaction) {}
};