const { error } = require("console");
const { SlashCommandBuilder, EmbedBuilder, ActionRowBuilder, ButtonBuilder, ButtonStyle, StringSelectMenuBuilder, StringSelectMenuOptionBuilder, ComponentType, ButtonInteraction } = require("discord.js");

const Path = require("path");

const FileName = Path.basename(__filename).replace(/\.js$/, '');
const UppercaseFileName = FileName.charAt(0).toUpperCase() + FileName.slice(1);

const Content = {
    Category: "Non-Skill", 
    Name: `${UppercaseFileName}`, 
    Cmd: `/${FileName}`, 
    Description: "Travel places and provides info on settlements and stores within settlements."
};

const Settlements = [
    {Name: "Springwood Village", Description: "", Value: "springwood-village"},
    {Name: "City of Isles", Description: "", Value: "city-of-isles"}
];

const Establishments = [
    {Name: "Armor Shop: ", Description: "", Value: "armor-shop"},
    {Name: "Weapon Shop: ", Description: "", Value: "weapon-shop"},
    {Name: "Potion Shop: ", Description: "", Value: "potion-shop"},
    {Name: "Fishing Shop: ", Description: "", Value: "fishing-shop"},
    {Name: "Mining Shop: ", Description: "", Value: "mining-shop"},
    {Name: "Farming Shop: ", Description: "", Value: "farming-shop"},
    {Name: "Fishing Site: ", Description: "", Value: "fishing-site"},
    {Name: "Mining Site: ", Description: "", Value: "mining-site"},
    {Name: "Smithing Site: ", Description: "", Value: "smithing-site"},
    {Name: "Farming Site: ", Description: "", Value: "farming-site"},
    {Name: "Outskirts: ", Description: "", Value: "outskirts"}
];

const Buttons = [
    {ID: "settlements", Label: "Settlements", Style: ButtonStyle.Primary},
    {ID: "establishments", Label: "Establishments", Style: ButtonStyle.Primary},
    {ID: "current", Label: "Current", Style: ButtonStyle.Primary},
    {ID: "info", Label: "Info", Style: ButtonStyle.Secondary}
];

const GenerateLocationList = (Locations, ListTitle) => {
    let List = `${ListTitle}`;

    Locations.forEach(Location => {
        List += `- ${Location.Name}\n`;
    })

    return List;
};

const CurrentLocation = "[Settlement], [Establishment]";

const SettlementDescription = `**Current Location: ${CurrentLocation}**\n\n` 
+ `${GenerateLocationList(Settlements, "**Settlements:**\n")}`;

const EstablishmentDescription = `**Current Location: ${CurrentLocation}**\n\n` 
+ `${GenerateLocationList(Establishments, "**Establishments:**\n")}`;

const ButtonsRow = new ActionRowBuilder();

Buttons.forEach(Button => {
    ButtonsRow.components.push(
        new ButtonBuilder().setCustomId(Button.ID).setLabel(Button.Label).setStyle(Button.Style)
    );
});

const SettlementEmbed = new EmbedBuilder()
    .setAuthor({ name: "TypeQuest | Traveling Activity" })
    .setTitle("Settlements")
    .setDescription(SettlementDescription)
    .setThumbnail("https://i.imgur.com/KcbtzPg.png")
    .setFooter({ text: "Need help? Press the \"Info\" button below." })
    .setColor("#000000");

const SelectSettlementMenu = new StringSelectMenuBuilder()
    .setCustomId("select-settlement-menu")
    .setPlaceholder("Choose a settlement to travel to.")
    .setMinValues(0)
    .setMaxValues(1)
    .addOptions(
        Settlements.map(Settlement => {
            return new StringSelectMenuOptionBuilder()
                .setLabel(Settlement.Name)
                .setValue(Settlement.Value);
        })
    );

const SettlementMenuRow = new ActionRowBuilder().addComponents(SelectSettlementMenu);

const EstablishmentEmbed = new EmbedBuilder()
    .setAuthor({ name: "TypeQuest | Traveling Activity" })
    .setTitle("Establishments")
    .setDescription(EstablishmentDescription)
    .setThumbnail("https://i.imgur.com/Kz2bJZb.png")
    .setFooter({ text: "Need help? Press the \"Info\" button below." })
    .setColor("#000000");

const SelectEstablishmentMenu = new StringSelectMenuBuilder()
    .setCustomId("select-establishment-menu")
    .setPlaceholder("Choose an establishment to travel to.")
    .setMinValues(0)
    .setMaxValues(1)
    .addOptions(
        Establishments.map(Establishment => {
            return new StringSelectMenuOptionBuilder()
                .setLabel(Establishment.Name)
                .setValue(Establishment.Value);
        })
    );

const EstablishmentMenuRow = new ActionRowBuilder().addComponents(SelectEstablishmentMenu);

const AwaitMessageComponent = (Message, Filter, Interaction) => {
    Message.awaitMessageComponent({ filter: Filter, componentType: ComponentType.Button, time: 10000000 })
        .then(async ButtonInteraction => {
            await ButtonInteraction.deferUpdate();

            switch(ButtonInteraction.customId) {
                case "settlements":
                    ButtonsRow.components.forEach(Button => {
                        if (Button.data.custom_id === "settlements") {
                            Button.setDisabled(true);
                        } else {
                            Button.setDisabled(false);
                        }
                    });

                    await Interaction.editReply({ embeds: [SettlementEmbed], components: [ButtonsRow, SettlementMenuRow], ephemeral: false });
                    break;

                case "establishments":
                    ButtonsRow.components.forEach(Button => {
                        if (Button.data.custom_id === "establishments") {
                            Button.setDisabled(true);
                        } else {
                            Button.setDisabled(false);
                        }
                    });

                    await Interaction.editReply({ embeds: [EstablishmentEmbed], components: [ButtonsRow, EstablishmentMenuRow], ephemeral: false });
                    break;

                case "current":
                    break;

                case "info":
                    break;

                default: 
                    await ButtonInteraction.reply("An unexpected error occurred");
                    throw Error("Button's custom id does not exist.");
            }

            AwaitMessageComponent(Message, Filter, Interaction)
        }).catch(Error => {
            console.log("An error occurred while collecting button clicks.", Error)
        });
}

module.exports = {
    Content,

    Data: new SlashCommandBuilder()
        .setName(FileName)
        .setDescription(Content.Description),

    async execute(Interaction) {
        ButtonsRow.components.forEach(Button => {
            if (Button.data.custom_id === "settlements") {
                Button.setDisabled(true);
            } else {
                Button.setDisabled(false);
            }
        });

        const Message = await Interaction.reply({ embeds: [SettlementEmbed], components: [ButtonsRow, SettlementMenuRow], ephemeral: false });

        const Filter = (NewInteraction) => {
            return NewInteraction.user.id === Interaction.user.id;
        };

        AwaitMessageComponent(Message, Filter, Interaction);

        /*const ButtonCollector = Interaction.channel.createMessageComponentCollector({ filter: Filter, componentType: ComponentType.Button });

        ButtonCollector.on('collect', async ButtonInteraction => {
            switch(ButtonInteraction.customId) {
                case "settlements":
                    await Interaction.editReply({ embeds: [SettlementEmbed], components: [ButtonsRow, SettlementMenuRow], ephemeral: false });
                    break;

                case "establishments":
                    await Interaction.editReply({ embeds: [EstablishmentEmbed], components: [ButtonsRow, EstablishmentMenuRow], ephemeral: false });
                    break;

                case "current":
                    break;

                case "info":
                    break;

                default: 
                    await ButtonInteraction.reply("An unexpected error occurred");
                    throw Error("Button's custom id does not exist.");
            }
        });*/
    }
};