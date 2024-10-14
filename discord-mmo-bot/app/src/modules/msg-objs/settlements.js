const { EmbedBuilder, ActionRowBuilder, ButtonBuilder, ButtonStyle, StringSelectMenuBuilder } = require("discord.js");

const Settlements = require("../general/all-settlements.js");

const { ReturnCurrentLocationObject, UpdateSettlement } = require("../general/users-location.js");
const { GetRecentMessageID, UpdateRecentMessage } = require("../general/users-misc.js");

const MessageObjects = require("../general/all-msg-objs.js");

const ReturnEmbed = async (UserID) => {
    const { Settlement, Establishment } = await ReturnCurrentLocationObject(UserID);

    if (!Settlement && !Establishment) {
        throw new Error("Settlement and establishment are undefined. It's possible the server is not up.");
    }

    const Description = "Current Location: " + Settlement + ", " + Establishment;
    
    const Embed = new EmbedBuilder()
    .setAuthor({ name: "TypeQuest | Traveling Activity"})
    .setTitle("Settlements | " + Settlement)
    .setDescription(Description)
    .addFields(Object.values(Settlements).map(Settlement => ({ name: Settlement.Name, value: " - " + Settlement.Description })))
    .setThumbnail("https://i.imgur.com/KcbtzPg.png")
    .setColor("#000000");

    return Embed;
};

const ReturnButtonsRow = (EmbedTitle) => {
    const Buttons = [
        {ID: "settlements", Label: "Settlements", Style: ButtonStyle.Primary, Disabled: false},
        {ID: "establishments", Label: "Establishments", Style: ButtonStyle.Primary, Disabled: false},
        {ID: "current", Label: "Current", Style: ButtonStyle.Primary, Disabled: false},
        {ID: "info", Label: "Info", Style: ButtonStyle.Secondary, Disabled: false}
    ];

    for (let i = 0; i < Buttons.length; i++) {
        if (EmbedTitle.includes(Buttons[i].Label)) {
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
    const Menu = new StringSelectMenuBuilder()
    .setCustomId("select-settlement-menu")
    .setPlaceholder("Choose a settlement to travel to.")
    .setMinValues(0)
    .setMaxValues(1)
    .addOptions(Object.values(Settlements).map(Settlement => ({ label: Settlement.Name, value: Settlement.Value })));

    const MenuRow = new ActionRowBuilder().addComponents(Menu);

    return MenuRow;
};

const CollectButtonInteraction = async (Interaction, Message, Collectors) => {
    Collectors.ButtonCollector = Message.createMessageComponentCollector({ 
        filter: Interaction => Interaction.isButton(),
        time: 180000 
    });

    Collectors.ButtonCollector.on("collect", async ButtonInteraction => {
        try {
            await ButtonInteraction.deferUpdate();

            const RecentMessageID = await GetRecentMessageID(Interaction.user.id);

            if (ButtonInteraction.user.id != Interaction.user.id) {
                return ButtonInteraction.followUp({content: "You do not have access to this button interaction.", ephemeral: true});
            } else if (RecentMessageID !== ButtonInteraction.message.id) {
                Collectors.ButtonCollector.stop();

                return ButtonInteraction.followUp({
                    content: "This button interaction has expired. Please use the latest message or call a new one.", 
                    ephemeral: true
                });
            }

            Collectors.ButtonCollector.stop();

            switch(ButtonInteraction.customId) {
                case "establishments":
                    return MessageObjects.DisplayEstablishments(Interaction);
                case "current":
                    return ButtonInteraction.editReply({content: ButtonInteraction.customId, ephemeral: true});
                case "info":
                    return ButtonInteraction.editReply({content: ButtonInteraction.customId, ephemeral: true});
                default:
                    throw new Error("This button interaction id " + ButtonInteraction.customId + " does not exist.");
            }
        } catch (Error) {
            console.error("An error occurred while clicking a button interaction:", Error);

            Interaction.editReply({content: "An unexpected error occurred.", embeds: [], components: [], ephemeral: true});
        }
    });

    Collectors.ButtonCollector.on("end", () => {
        Collectors.MenuCollector.stop();
    });
};

const CollectMenuInteractions = async (Interaction, Message, Collectors) => {
    Collectors.MenuCollector = Message.createMessageComponentCollector({ 
        filter: Interaction => Interaction.isStringSelectMenu(),
        time: 180000 
    });

    Collectors.MenuCollector.on("collect", async MenuInteraction => {
        try {
            await MenuInteraction.deferUpdate();

            const RecentMessageID = await GetRecentMessageID(Interaction.user.id);

            if (MenuInteraction.user.id != Interaction.user.id) {
                return MenuInteraction.followUp({content: "You do not have access to this menu interaction.", ephemeral: true});
            } else if (RecentMessageID !== MenuInteraction.message.id) {
                Collectors.MenuCollector.stop();

                return MenuInteraction.followUp({
                    content: "This menu interaction has expired. Please use the latest message or call a new one.", 
                    ephemeral: true
                });
            }

            let SelectedValueWords = MenuInteraction.values[0].split("-");

            SelectedValueWords = SelectedValueWords.map(Word => Word.charAt(0).toUpperCase() + Word.slice(1));

            const Destination = SelectedValueWords.join(" ");
            const TyperaceTitle = "Traveling to " + Destination;

            await UpdateSettlement(Interaction.user.id, Destination);

            Collectors.ButtonCollector.stop();
            Collectors.MenuCollector.stop();

            await MessageObjects.DisplayTyperace(Interaction, TyperaceTitle, 3);

            //DisplaySettlementsMessage(Interaction);
        } catch (Error) {
            console.error("An error occurred while collecting a menu interaction:", Error);

            Interaction.editReply({content: "An unexpected error occurred.", embeds: [], components: [], ephemeral: true});
        }
    });

    Collectors.MenuCollector.on("end", () => {
        Collectors.ButtonCollector.stop();
    });
};

const ReturnMessageObject = async (UserID) => {
    const Embed = await ReturnEmbed(UserID);
    const ButtonsRow = ReturnButtonsRow(Embed.data.title);
    const MenuRow = ReturnMenuRow();

    return { embeds: [Embed], components: [ButtonsRow, MenuRow] };
};

const CollectSettlementsInteractions = async (Interaction, Message, Collectors) => {
    CollectMenuInteractions(Interaction, Message, Collectors);
    CollectButtonInteraction(Interaction, Message, Collectors);
};

var DisplaySettlementsMessage = async (Interaction, NewMessage = false) => {
    try {
        const Message = await Interaction.editReply(await ReturnMessageObject(Interaction.user.id));
        
        if (NewMessage) {
            await UpdateRecentMessage(Interaction.user.id, Message.id);
        }

        let Collectors = {ButtonCollector: undefined, MenuCollector: undefined};
    
        CollectSettlementsInteractions(Interaction, Message, Collectors);
    } catch (Error) {
        console.log("An error occurred inside the settlements tab:", Error);

        Interaction.editReply({content: "An unexpected error occurred.", embeds: [], components: [], ephemeral: true});
    }
};

module.exports = DisplaySettlementsMessage;