//require("dotenv").config();

const { Client, IntentsBitField, EmbedBuilder, ActionRowBuilder, ButtonBuilder, ButtonStyle, 
    StringSelectMenuBuilder, StringSelectMenuOptionBuilder, ComponentType, SelectMenuBuilder } = require("discord.js");
const StringSimilarity = require('string-similarity');

const UserClient = new Client({
    intents: [
        IntentsBitField.Flags.Guilds,
        IntentsBitField.Flags.GuildMembers,
        IntentsBitField.Flags.GuildMessages,
        IntentsBitField.Flags.GuildMessageTyping,
        IntentsBitField.Flags.MessageContent,
        IntentsBitField.Flags.GuildMessageReactions
    ]
});

let CurrentButtonMessageID;
let CommandCallerID;

const Roles = [
    {
        id: "1247047161900695552",
        label: "Blue"
    },

    {
        id: "1247047279907700807",
        label: "Red"
    },

    {
        id: "1247047324228649071",
        label: "Green"
    }
]

const Words = [
    "khang", "fuck", "shoe", "dog", "hair", "ball", "mom", "dad", "him", "her", "purse", "cloth", "sew", "blow", "house",
    "mouse", "cloud", "stare", "dark", "think", "is", "he", "she", "deed", "beat", "feet", "happy", "sad", "mad", "fan",
    "band", "game", "sport", "lord", "court", "port", "dock", "block", "smelt", "sword", "tour", "horde", "clover", "bowel",
    "zeus", "tooth", "eye", "nose", "mole", "lip", "hip", "fit", "work", "sleep", "rest", "mess", "test", "toe", "dough",
    "glow", "me", "it", "is", "kiss", "this", "of", "for", "but", "because", "cause", "yet", "there", "their", "air", "fair",
    "flow", "rot", "rock", "dream", "acid", "water", "fire", "hire", "admire", "corpse", "contest", "desk", "glass", "task",
    "fast", "slow", "steady", "head", "ball", "stall", "mall", "raw", "ok", "okay", "stay", "day", "night", "sight", "height",
    "ground", "above", "below", "infant", "baby", "kid", "child", "father", "mother", "sibling", "children", "shark", "whale",
    "black", "brown", "red", "blue", "green", "yellow", "purple", "orange", "cat", "ear", "fear", "top", "stop", "grin",
    "smile", "root", "tree", "bark", "logs", "exam", "pencil", "eraser", "book", "cook", "grill", "peel", "meal", "steal",
    "greet", "moss", "vine", "lime", "grape", "apple", "tap", "crab", "fish", "mark", "lazy", "huge", "giant", "tiny",
    "fame", "hero", "mean", "rude", "rant", "men", "women", "queer", "dear", "deer", "steer", "homeless", "money", "cash",
    "ash", "shield", "sword", "weapon", "graze", "mace", "hate", "love", "quack", "duck", "bird", "spider", "cow", "pig",
    "chicken", "wheat", "sheep", "goat", "float", "boat", "ship", "gun", "glock", "dime", "coin", "drink", "juice", "stool",
    "sun", "moon", "earth", "mars", "wind", "rain", "storm", "thunder", "light", "shadow", "flight", "swim", "dive", "sky",
    "skirt", "shirt", "pants", "boots", "socks", "cord", "music", "song", "bong", "ping", "china", "korea", "us", "we", "see"
]

const Pets = [
    {
        label: "Dog",
        description: "a dog",
        value: "dog"
    },

    {
        label: "Cat",
        description: "a cat",
        value: "cat"
    },

    {
        label: "eat",
        description: "a dog",
        value: "eat"
    },

    {
        label: "fat",
        description: "a cat",
        value: "fat"
    },

    {
        label: "dick",
        description: "a dog",
        value: "dick"
    },

    {
        label: "meat",
        description: "a dog",
        value: "meat"
    },

    {
        label: "e",
        description: "a dog",
        value: "e"
    },

    {
        label: "a",
        description: "a cat",
        value: "a"
    },

    {
        label: "b",
        description: "a dog",
        value: "b"
    },

    {
        label: "z",
        description: "a cat",
        value: "z"
    },

    {
        label: "ee",
        description: "a dog",
        value: "ee"
    },

    {
        label: "ss",
        description: "a dog",
        value: "ss"
    },
]

const Delay = (ms => {
    return new Promise(Resolve => setTimeout(Resolve, ms));
});

UserClient.on("ready", (ClientInfo) => {
    console.log(ClientInfo.user.tag, "is now online.");
});

UserClient.on("typingStart", (_, User) => {
    console.log(Date.now());
});

UserClient.on("interactionCreate", async (Interaction) => {
    if (Interaction.isButton()) {
        if (CommandCallerID === Interaction.user.id && CurrentButtonMessageID === Interaction.message.id) {
            await Interaction.deferReply({ ephemeral: true });

            const Role = Interaction.guild.roles.cache.get(Interaction.customId);

            if (!Role) {
                Interaction.editReply({
                    content: "The role no longer exists",
                    ephemeral: true
                })
            }

            const UserHasRole = Interaction.member.roles.cache.has(Role.id)

            if (UserHasRole) {
                await Interaction.member.roles.remove(Role);
                await Interaction.editReply(`The role ${Role} has been removed.`);
            } else {
                await Interaction.member.roles.add(Role);
                await Interaction.editReply(`The role ${Role} has been added.`);
            }

        } else if (CurrentButtonMessageID !== Interaction.message.id) {
            Interaction.reply({ content: "Please work with the latest interaction or call a new interaction", ephemeral: true });
        } else {
            Interaction.reply("This button is not for you", Interaction.user.displayName);
        }
    }
    
    if (!Interaction.isChatInputCommand()) {
        return;
    }

    if (Interaction.commandName === "hey") {
        Interaction.reply("Hi!");

    } else if (Interaction.commandName === "add") {
        let Sum = Interaction.options.get("first-number").value + Interaction.options.get("second-number").value;

        Interaction.reply(Sum.toString());
    } else if (Interaction.commandName === "embed") {
        let Username = Interaction.user.username;

        let Embed = new EmbedBuilder()
        .setTitle(`${Username}'s Title`)
        .setDescription("This is an embed description")
        .setColor("Random")
        .addFields(
            { name: "Field Title", value: "Some random value", inline: true },
            { name: "Field Title 2", value: "Some random value 2", inline: true },
            { name: "Field Title 3", value: "Some random value 3", inline: true }
        )
        .setTimestamp(Date.now());

        Interaction.reply({ embeds: [Embed] });
    } else if (Interaction.commandName === "add-role") {
        CommandCallerID = Interaction.user.id;

        let Channel = Interaction.client.channels.cache.get("1247051134867341385"); 

        if (!Channel) { 
            return;
        };

        const ButtonsRow = new ActionRowBuilder();

        Roles.forEach(Role => {
            ButtonsRow.components.push(
                new ButtonBuilder().setCustomId(Role.id).setLabel(Role.label).setStyle(ButtonStyle.Primary)
            );
        });

        Channel.send({
            content: "Add or remove a role",
            components: [ButtonsRow]
        })

        let Message = await Interaction.reply({
            content: "Add or remove a role",
            components: [ButtonsRow],
            fetchReply: true
        });

        CurrentButtonMessageID = Message.id;
    } else if (Interaction.commandName === "typerace") {
        let Time = 10;
        let Description = `\`\`\`Time: ${Time}\n\nHey mother fucker!\`\`\``;
        let TypeRacerEmbed = new EmbedBuilder()
        .setDescription(Description)
        .setColor("Red");

        Interaction.reply({ embeds: [TypeRacerEmbed]});

        for (var i = --Time; i >= 0; i--) {
            await Delay(1000);

            Description = `\`\`\`Time: ${i}\n\nHey mother fucker!\`\`\``;

            TypeRacerEmbed = new EmbedBuilder()
            .setDescription(Description)
            .setColor("Red");
    
            Interaction.editReply({ embeds: [TypeRacerEmbed]});
        }
    } else if (Interaction.commandName === "send") {
        let Filter = (Response) => {
            return Response.author.id === Interaction.user.id;
        }

        let Collector = Interaction.channel.createMessageCollector({filter: Filter, time: 5000});
        let Answered = false;

        await Interaction.reply("Please send a message");

        Collector.on("end", () => {
            if (!Answered) {
                Interaction.followUp("Time ran out");
            }
        })

        Collector.on("collect", async (Message) => {
            await Interaction.editReply(Message.content);
            Answered = true;
            Collector.stop();
        })
    } else if (Interaction.commandName === "typerace2") {
        let Time = 10;
        let Start = `\`\`\`Time: ${Time}\n\n`;

        let Body = "";
        let RandomIndex;

        await Interaction.deferReply();

        for (var i = 0; i < 40; i++) {
            RandomIndex = Math.floor(Math.random() * Words.length);

            Body += Words[RandomIndex] + " ";
        }

        Body = Body.substring(0, Body.length - 1);

        let Description = Start + `${Body}\`\`\``;

        let TypeRacerEmbed = new EmbedBuilder()
        .setDescription(Description)
        .setColor("Red");

        Interaction.editReply({ embeds: [TypeRacerEmbed] });

        let Answered = false;

        (async () => {
            for (var i = --Time; i >= 0; i--) {
                if (Answered === true) {
                    return;
                }

                await Delay(1000);

                if (Answered === true) {
                    return;
                }
    
                Start = `\`\`\`Time: ${i}\n\n`;
                Description = Start + `${Body}\`\`\``;
    
                TypeRacerEmbed = new EmbedBuilder()
                .setDescription(Description)
                .setColor("Red");
        
                Interaction.editReply({ embeds: [TypeRacerEmbed] });
            }
        })();

        let Filter = (Response) => {
            return Response.author.id === Interaction.user.id;
        }

        let Collector = Interaction.channel.createMessageCollector({filter: Filter, time: 10000 + 1000});

        //await Interaction.reply("Please send a message");

        Collector.on("end", () => {
            if (!Answered) {
                Interaction.followUp("You ran out of time");
            }
        })

        Collector.on("collect", async (Message) => {
            //console.log(Message.content);
            Answered = true;

            const Similarity = StringSimilarity.compareTwoStrings(Body, Message.content);
            const Accuracy = (Similarity * 100).toFixed(2);

            await Interaction.followUp(`${Accuracy}`);
            Collector.stop();
        })
    } else if (Interaction.commandName === "show-pets") {
        let SelectMenu = new StringSelectMenuBuilder()
        .setCustomId(Interaction.id)
        .setPlaceholder("Select something")
        .setMinValues(0)
        .setMaxValues(Pets.length)
        .addOptions(
            Pets.map(Pet => {
                return new StringSelectMenuOptionBuilder()
                .setLabel(Pet.label)
                .setDescription(Pet.description)
                .setValue(Pet.value)
            })
        )

        let ActionRow = new ActionRowBuilder().addComponents(SelectMenu);

        await Interaction.reply({ components: [ActionRow] });

        let Collector = Interaction.channel.createMessageComponentCollector({
            componentType: ComponentType.StringSelect,
            filter: (Message) => {return Message.user.id === Interaction.user.id && Message.customId === Interaction.id},
            time: 25000
        });

        Collector.on("collect", Interaction => {
            if (Interaction.values.length === 0) {
                Interaction.reply("gay");
                return;
            }

            Interaction.reply(`${Interaction.values}`);
        })
    } else if (Interaction.commandName === "react") {
        const Message = await Interaction.reply({
            content: "React here bitch",
            fetchReply: true
        })

        await Message.react("🥰");
        await Message.react("🤬");

        const Filter = (Reaction, User) => {
            return (Reaction.emoji.name === "🥰" || Reaction.emoji.name === "🤬") && User.id === Interaction.user.id;
        }

        const Collector = Message.createReactionCollector({ filter: Filter, time: 10000 });

        Collector.on("collect", (Reaction, User) => {
            Interaction.channel.send(`${User.tag} reacted to ${Reaction.emoji.name}`);
        })
    }
});
 
UserClient.on("messageCreate", (Message) => {
    if (Message.author.bot) {
        return;
    };
    
    //console.log(Message.author.username, "typed", Message.content);

    if (Message.content === "Hi") {
        Message.reply("Fuck you!");
    };
});

//UserClient.login(process.env.private);