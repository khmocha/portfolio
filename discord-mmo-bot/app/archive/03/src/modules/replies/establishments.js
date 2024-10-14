const { EmbedBuilder, ActionRowBuilder, ButtonBuilder, ButtonStyle, StringSelectMenuBuilder, StringSelectMenuOptionBuilder, ComponentType } = require("discord.js");

const LocationsModule = require("../locations.js");

const ReturnEmbed = async (UserID) => {
    try {
        const {Settlement, Establishment} = await LocationsModule.ReturnCurrentLocationObject(UserID);
        let EstablishmentsDescription = "Current Location: **" + Settlement + "**, **" + Establishment + "**\n";

        const Establishments = Object.values(JSON.parse(JSON.stringify(LocationsModule.Settlements[Settlement].Establishments)));

        for (var i = 0; i < Establishments.length; i++) {
            if (Establishments[i].name === Establishment) {
                Establishments[i].name += " **[Current]**";
                break;
            }
        }
        
        const EstablishmentsEmbed = new EmbedBuilder()
        .setAuthor({ name: "TypeQuest | Traveling Activity" })
        .setTitle("Establishments")
        .setDescription(EstablishmentsDescription)
        .addFields(
            Establishments.map(Establishment => {
                return {name: Establishment.Name, value: Establishment.Description}
            })
        )
        .setThumbnail("https://i.imgur.com/Kz2bJZb.png")
        .setColor("#000000");

        return EstablishmentsEmbed;
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

const ReturnMenuRow = (Settlement) => {
    const SelectMenu = new StringSelectMenuBuilder()
    .setCustomId("select-establishment-menu")
    .setPlaceholder("Choose an establishment to travel to.")
    .setMinValues(0)
    .setMaxValues(1)
    .addOptions(
        Object.values(LocationsModule.Settlements[Settlement].Establishments).map(Establishment => {
            return new StringSelectMenuOptionBuilder()
                .setLabel(Establishment.Name)
                .setValue(Establishment.Value);
        })
    );

    const SelectMenuRow = new ActionRowBuilder().addComponents(SelectMenu);

    return SelectMenuRow;
};

const CollectMenuInteractions = (Interaction) => {
    const Collector = Interaction.channel.createMessageComponentCollector({componentType: ComponentType.StringSelect});

    Collector.on("collect", async (MenuInteraction) => {
        console.log("Ok");
        
        Collector.stop();

        await MenuInteraction.deferUpdate({ephemeral: true});

        switch (MenuInteraction.values[0]) {
            case "greenleaf-river": 
                Interaction.editReply({content: MenuInteraction.values[0]});

                break;
            default: 
                console.error("Menu's custom ID does not exist in establishments:", MenuInteraction.values[0]);

                await MenuInteraction.followUp("An unexpected error occurred.");
        }
    });
}

module.exports = {ReturnEmbed, ReturnButtonsRow, ReturnMenuRow, CollectMenuInteractions};