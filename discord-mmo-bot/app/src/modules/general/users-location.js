const ReturnCurrentLocationObject = async (UserID) => {
    try {
        const Response = await fetch(`http://localhost:3000/get-current-location?userid=${UserID}`);

        if (!Response.ok) {
            throw new Error("An error occurred on the server: " + Response.status);
        }

        const LocationObject = await Response.json();

        return LocationObject;
    } catch (Error) {
        console.error("An error occurred while returning current location object:", Error);

        return "An unexpected error occurred";
    }
};

const UpdateSettlement = async (UserID, NewSettlement) => {
    try {
        const Response = await fetch("http://localhost:3000/update-settlement", {
            method: "PUT",
            headers: {"Content-Type": "application/json"},
            body: JSON.stringify({ UserID, NewSettlement })
        });

        if (!Response.ok) {
            throw new Error("An error occurred on the server: " + Response.status);
        }
    } catch (Error) {
        console.error("An error occurred while updating settlement location:", Error);

        return "An unexpected error occurred";
    }
};

const UpdateEstablishment = async (UserID, NewEstablishment) => {
    try {
        const Response = await fetch("http://localhost:3000/update-establishment", {
            method: "PUT",
            headers: {"Content-Type": "application/json"},
            body: JSON.stringify({ UserID, NewEstablishment })
        });

        if (!Response.ok) {
            throw new Error("An error occurred on the server: " + Response.status);
        }
    } catch (Error) {
        console.error("An error occurred while updating establishment location:", Error);

        return "An unexpected error occurred";
    }
};

module.exports = { ReturnCurrentLocationObject, UpdateSettlement, UpdateEstablishment };