const FirstVillage = {
    Name: "First Village",
    Value: "first-village",
    Description: "This is the village that all beginners start.",
    Coordinate: {X: 0, Y: 0},
    Establishments: {
        "Greenleaf River": {
            Name: "Greenleaf River",
            Value: "greenleaf-river",
            Description: "This is the river that all mother fuckers fish and fight.",
            Coordinate: {X: 1, Y: 1},
            Activities: ["Fishing", "Combat"]
        },

        "Emerald Forest": {
            Name: "Emerald Forest",
            Value: "emerald-forest",
            Description: "Kill them bitch ass slimes fr.",
            Coordinate: {X: -1, Y: -1},
            Activities: ["Combat"]
        },

        "Leafcrest Mountain": {
            Name: "Leafcrest Mountain",
            Value: "leafcrest-mountain",
            Description: "For mining and killing golems and shit.",
            Coordinate: {X: 2, Y: 1},
            Activities: ["Mining", "Combat"]
        },

        "Harvest Hollow": {
            Name: "Harvest Hollow",
            Value: "harvest-hollow",
            Description: "Harvest Hollow like the hollows in bleach hollows return.",
            Coordinate: {X: -2, Y: -1},
            Activities: ["Farming", "Combat", ["Collect Chicken Eggs", "Milk Cows"]]
        }
    }
};

module.exports = FirstVillage;