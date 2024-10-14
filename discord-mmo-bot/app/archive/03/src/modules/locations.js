const Settlements = {
    "New Leaf": {
        Name: "New Leaf",
        Value: "new-leaf",
        Description: " - This is the village that all beginners start.",
        Coordinate: {X: 0, Y: 0},
        Establishments: {
            "Greenleaf River": {
                Name: "Greenleaf River",
                Value: "greenleaf-river",
                Description: " - This is the river that all mother fuckers fish and fight.",
                Coordinate: {X: 1, Y: 1},
                Activities: ["Fishing", "Combat"]
            },

            "Emerald Forest": {
                Name: "Emerald Forest",
                Value: "emerald-forest",
                Description: " - Kill them bitch ass slimes fr.",
                Coordinate: {X: -1, Y: -1},
                Activities: ["Combat"]
            },

            "Leafcrest Mountain": {
                Name: "Leafcrest Mountain",
                Value: "leafcrest-mountain",
                Description: " - For mining and killing golems and shit.",
                Coordinate: {X: 2, Y: 1},
                Activities: ["Mining", "Combat"]
            },

            "Harvest Hollow": {
                Name: "Harvest Hollow",
                Value: "harvest-hollow",
                Description: " - Harvest Hollow like the hollows in bleach hollows return.",
                Coordinate: {X: -2, Y: -1},
                Activities: ["Farming", "Combat", ["Collect Chicken Eggs", "Milk Cows"]]
            }
        }
    },

    "Kid": {
        Name: "Kid",
        Value: "kid",
        Description: " - Fuck yo mom",
        Coordinate: {X: 3, Y: -3},
        Establishments: {
            "Hey": {
                Name: "Hey",
                Value: "hey",
                Description: " - Ok",
                Coordinate: {X: -2, Y: -10},
                Activities: ["Farming", "Combat", ["Collect Chicken Eggs", "Milk Cows"]]
            }
        }
    }
};

const ReturnDistance = (CurrentLocation, Destination) => {
    const YDifference = Destination.Y - CurrentLocation.Y;
    const XDifference = Destination.X - CurrentLocation.X;

    return Math.floor(Math.sqrt(Math.pow(YDifference, 2) + Math.pow(XDifference, 2)));
};

const ReturnCurrentLocationObject = async (UserID) => {
    try {
        const Response = await fetch(`http://localhost:3000/get-current-location?userid=${UserID}`);
        const ResponseObject = await Response.json();

        return ResponseObject;
    } catch (Error) {
        console.error("An error occurred while fetching current location:", Error);

        return "An unexpected error occurred";
    }
}

const UpdateSettlement = async (UserID, NewSettlement) => {
    const UserData = {UserID, NewSettlement}

    try {
        await fetch(`http://localhost:3000/update-settlement`, {
            method: "PUT",
            headers: {"Content-Type": "application/json"},
            body: JSON.stringify(UserData)
        });
    } catch (Error) {
        console.error("An error occurred while fetching current location:", Error);

        return "An unexpected error occurred";
    }
}

module.exports = {
    Settlements,

    ReturnDistance,

    ReturnCurrentLocationObject,

    UpdateSettlement
    
};