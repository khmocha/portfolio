const GetRecentMessageID = async (UserID) => {
    try {
        const Response = await fetch(`http://localhost:3000/get-recent-message?userid=${UserID}`);

        if (!Response.ok) {
            throw new Error("An error occurred on the server while getting recent message: " + Response.status);
        };

        const { MessageID } = await Response.json();

        return MessageID;
    } catch (Error) {
        console.error("An error occurred while fetching request:", Error);

        return "An unexpected error occurred";
    }
}

const UpdateRecentMessage = async (UserID, MessageID) => {
    try {
        const Response = await fetch("http://localhost:3000/update-recent-message", {
            method: "PUT",
            headers: {
                "Content-Type": "application/json",
            },
            body: JSON.stringify({ UserID, MessageID }),
        });

        if (!Response.ok) {
            throw new Error("An error occurred on the server while updating recent message: " + Response.status);
        };
    } catch (Error) {
        console.error("An error occurred while fetching request:", Error);

        return "An unexpected error occurred";
    };
};

module.exports = { UpdateRecentMessage, GetRecentMessageID };