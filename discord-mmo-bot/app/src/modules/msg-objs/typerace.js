const { EmbedBuilder, ActionRowBuilder, ButtonBuilder, ButtonStyle, StringSelectMenuBuilder, Embed } = require("discord.js");

const TyperaceWords = require("../general/typerace-words.js");

const Delay = (ms) => {
    return new Promise(Resolve => {
        setTimeout(Resolve, ms);
    });
};

const RandomlyShuffleArray = (Array) => {
    let RandomIndex;

    for (let i = Array.length - 1; i > 0; i--) {
        RandomIndex = Math.floor(Math.random() * (i + 1));

        [Array[i], Array[RandomIndex]] = [Array[RandomIndex], Array[i]];
    };
};

const ReturnTyperaceText = (TyperaceBlueprint) => {
    let SelectedWords = [];
    let TyperaceText = "";

    Object.entries(TyperaceBlueprint).forEach(([Name, Count]) => {
        let RandomNumber; 

        for (let i = 0; i < Count; i++) {
            RandomNumber = Math.floor(Math.random() * TyperaceWords[Name].length);
            SelectedWords.push(TyperaceWords[Name][RandomNumber]);
        }
    })

    RandomlyShuffleArray(SelectedWords);

    SelectedWords.forEach(Word => {
        TyperaceText += Word + " ";
    })

    return { TyperaceText: TyperaceText.slice(0, -1), WordCount: SelectedWords.length };
};

const ReturnEmbed = (Time, EmbedTitle, CurrentCount, TotalTypeRaces, TyperaceText, WordCount) => {
    if (!TyperaceText) {
        const TyperaceBlueprint = { Level1Words: 10, Level8Words: 5, Level7Words: 15, Level3Words: 10 };
        const TyperaceVariables = ReturnTyperaceText(TyperaceBlueprint);

        TyperaceText = TyperaceVariables.TyperaceText;
        WordCount = TyperaceVariables.WordCount;
    }

    Description = "```Word Count: " + WordCount + "                            " + "Time Left: " + Time +
    "s\n\n" + TyperaceText + "```";

    const Embed = new EmbedBuilder()
    .setAuthor({ name: `TypeQuest | Typerace Activity | Typeraces Completed: ${CurrentCount}/${TotalTypeRaces}`})
    .setTitle(EmbedTitle)
    .setDescription(Description);

    return { Embed, TyperaceText, WordCount };
};

const ExecuteCountdown = async (Time, Interaction, EmbedTitle, CurrentCount, TotalTypeRaces, TyperaceText, WordCount) => {
    for (let i = Time; i >= 0; i--) {
        const { Embed } = ReturnEmbed(i, EmbedTitle, CurrentCount, TotalTypeRaces, TyperaceText, WordCount);

        await Interaction.editReply({embeds: [Embed], components: []});

        await Delay(1000);
    }
}

const DisplayTyperaceMessage = async (Interaction, EmbedTitle, TotalTypeRaces, CurrentCount = 0, NewMessage = false) => {
    const Time = 30;

    const { Embed, TyperaceText, WordCount } = ReturnEmbed(Time, EmbedTitle, ++CurrentCount, TotalTypeRaces);

    const Message = await Interaction.editReply({embeds: [Embed], components: []});

    ExecuteCountdown(Time, Interaction, EmbedTitle, CurrentCount, TotalTypeRaces, TyperaceText, WordCount);

    if (NewMessage) {
        await UpdateRecentMessage(Interaction.user.id, Message.id);
    }
};

module.exports = DisplayTyperaceMessage;