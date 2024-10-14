const { SlashCommandBuilder } = require("discord.js");

const { ReturnSettlementsReply, ReturnButtonsRow, ReturnMenuRow, AwaitButtonResponse, CollectMenuInteractions } = require("../modules/replies/settlements.js");

module.exports = {
    Data: new SlashCommandBuilder()
        .setName("traveling")
        .setDescription("Travel across the world."),

    async execute(Interaction) {
        await Interaction.deferReply({ ephemeral: false });

        const {SettlementsEmbed, Settlement} = await ReturnSettlementsReply(Interaction.user.id);
        const ButtonsRow = ReturnButtonsRow(SettlementsEmbed.data.title);
        const SettlementsMenuRow = ReturnMenuRow();

        const Reply = await Interaction.editReply({embeds: [SettlementsEmbed], components: [ButtonsRow, SettlementsMenuRow]});

        AwaitButtonResponse(Reply, Interaction, Settlement);
        CollectMenuInteractions(Interaction, Interaction.user.id);
    }
};