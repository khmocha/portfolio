const { SlashCommandBuilder } = require("discord.js");

const DisplaySettlementsMessage = require("../../modules/msg-objs/settlements.js");

module.exports = {
    Data: new SlashCommandBuilder()
        .setName("traveling")
        .setDescription("Travel across the world."),

    async execute(Interaction) {
        await Interaction.deferReply({ ephemeral: false });

        DisplaySettlementsMessage(Interaction, true);
    }
};