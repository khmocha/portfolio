const { EmbedBuilder, ActionRowBuilder, ButtonBuilder, ButtonStyle, StringSelectMenuBuilder, StringSelectMenuOptionBuilder, ComponentType } = require("discord.js");

const LocationsModule = require("../locations.js");
const EstablishmentsObject = require("./establishments.js");

const ReturnSettlementsReply = async (UserID) => {
    try {
        const {Settlement, Establishment} = await LocationsModule.ReturnCurrentLocationObject(UserID);
        let SettlementsDescription = "Current Location: **" + Settlement + "**, **" + Establishment + "**\n";

        const Settlements = [
            {name: "New Leaf", value: " - This is the village that all beginners start."},
            {name: "City of Isles", value: " - 2nd Village and the meanest one."},
            {name: "Hamburger Mountains", value: " - Fuck you this is just a test."},
            {name: "The Lord of Losses", value: " - A new test but an established city for others to witness."}
        ]

        for (var i = 0; i < Settlements.length; i++) {
            if (Settlements[i].name === Settlement) {
                Settlements[i].name += " **[Current]**";
                break;
            }
        }
        
        const SettlementsEmbed = new EmbedBuilder()
        .setAuthor({ name: "TypeQuest | Traveling Activity" })
        .setTitle("Settlements")
        .setDescription(SettlementsDescription)
        .addFields(...Settlements)
        .setThumbnail("https://i.imgur.com/KcbtzPg.png")
        .setColor("#000000");

        return {SettlementsEmbed, Settlement};
    } catch (Error) {
        console.error("There was an error while trying to return the settlements reply:", Error);

        return "An unexpected error occurred.";
    }
};

const ReturnButtonsRow = (CategoryTitle) => {
    const Buttons = [
        {ID: "settlements", Label: "Settlements", Style: ButtonStyle.Primary, Disabled: false},
        {ID: "establishments", Label: "Establishments", Style: ButtonStyle.Primary, Disabled: false},
        {ID: "current", Label: "Current", Style: ButtonStyle.Primary, Disabled: false},
        {ID: "info", Label: "Info", Style: ButtonStyle.Secondary, Disabled: false}
    ];

    for (var i = 0; i < Buttons.length; i++) {
        if (Buttons[i].Label === CategoryTitle) {
            Buttons[i].Disabled = true;
            break;
        }
    }

    const ButtonsRow = new ActionRowBuilder();

    Buttons.forEach(Button => {
        ButtonsRow.components.push(
            new ButtonBuilder().setCustomId(Button.ID).setLabel(Button.Label).setStyle(Button.Style).setDisabled(Button.Disabled)
        );
    });

    return ButtonsRow;
};

const ReturnMenuRow = () => {
    const SelectSettlementMenu = new StringSelectMenuBuilder()
    .setCustomId("select-settlement-menu")
    .setPlaceholder("Choose a settlement to travel to.")
    .setMinValues(0)
    .setMaxValues(1)
    .addOptions(
        Object.values(LocationsModule.Settlements).map(Settlement => {
            return new StringSelectMenuOptionBuilder()
                .setLabel(Settlement.Name)
                .setValue(Settlement.Value);
        })
    );

    const SettlementsMenuRow = new ActionRowBuilder().addComponents(SelectSettlementMenu);

    return SettlementsMenuRow;
};

const AwaitButtonResponse = (Reply, Interaction, Settlement) => {
    Reply.awaitMessageComponent({componentType: ComponentType.Button})
    .then(async ButtonInteraction => {
        try {
            await ButtonInteraction.deferUpdate();

            let Embed;
            let ButtonsRow;
            let MenuRow

            if (ButtonInteraction.user.id !== Interaction.user.id) {
                ButtonInteraction.followUp({content: "This is not your message.", ephemeral: true});

                AwaitButtonResponse(Reply, Interaction, Settlement);
                return;
            }

            switch(ButtonInteraction.customId) {
                case "settlements":
                    const SettlementsObject = await ReturnSettlementsReply(ButtonInteraction.user.id);
                    const SettlementsEmbed = SettlementsObject.SettlementsEmbed;
                    Settlement = SettlementsObject.Settlement;

                    ButtonsRow = ReturnButtonsRow(SettlementsEmbed.data.title);
                    MenuRow = ReturnMenuRow();

                    await Interaction.editReply({embeds: [SettlementsEmbed], components: [ButtonsRow, MenuRow]});
                    break;

                case "establishments":
                    Embed = await EstablishmentsObject.ReturnEmbed(ButtonInteraction.user.id);
                    ButtonsRow = EstablishmentsObject.ReturnButtonsRow(Embed.data.title);

                    MenuRow = EstablishmentsObject.ReturnMenuRow(Settlement);

                    await Interaction.editReply({embeds: [Embed], components: [ButtonsRow, MenuRow]});
                    EstablishmentsObject.CollectMenuInteractions(Interaction);
                    break;

                case "current":
                    break;

                case "info":
                    break;

                default: 
                    console.error("Button's custom ID does not exist:");

                    await ButtonInteraction.followUp("An unexpected error occurred.");
            }

            AwaitButtonResponse(Reply, Interaction, Settlement);
        } catch (Error) {
            console.error("An error occurred while awaiting a button response:", Error);

            await ButtonInteraction.followUp("An unexpected error occured.");
        }
    })
};

const CollectMenuInteractions = (Interaction, UserID) => {
    const Collector = Interaction.channel.createMessageComponentCollector({componentType: ComponentType.StringSelect});

    Collector.on("collect", async (MenuInteraction) => {
        Collector.stop();

        try {
            await MenuInteraction.deferUpdate({ephemeral: true});

            switch (MenuInteraction.values[0]) {
                case "new-leaf":
                    await LocationsModule.UpdateSettlement(UserID, "New Leaf");
                    await Interaction.editReply({content: MenuInteraction.values[0]});
    
                    break;
                case "kid": 
                    await LocationsModule.UpdateSettlement(UserID, "Kid");
                    await Interaction.editReply({content: MenuInteraction.values[0]});
    
                    break;
                default: 
                    console.error("Menu's custom ID does not exist:", MenuInteraction.values[0]);
    
                    await MenuInteraction.followUp("An unexpected error occurred.");
            }
        } catch (Error) {
            console.error("An error occurred while collecting a menu interaction:", Error);

            await MenuInteraction.followUp("An unexpected error occured.");
        }
    });
}

module.exports = {ReturnSettlementsReply, ReturnButtonsRow, ReturnMenuRow, AwaitButtonResponse, CollectMenuInteractions};
