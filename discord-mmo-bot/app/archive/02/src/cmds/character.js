const { SlashCommandBuilder, EmbedBuilder } = require("discord.js");

const Path = require("path");

const FileName = Path.basename(__filename).replace(/\.js$/, '');
const UppercaseFileName = FileName.charAt(0).toUpperCase() + FileName.slice(1);

const Content =  {
    Category: "General", 
    Name: `${UppercaseFileName}`, 
    Cmd: `/${FileName}`,  
    Description: "Provides your stats, equipment and inventory."
};

module.exports = {
    Content, 

    Data: new SlashCommandBuilder()
        .setName(FileName)
        .setDescription(Content.Description),

    async execute(Interaction) {}
};