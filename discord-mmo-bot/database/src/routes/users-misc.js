const Express = require("Express");

const Router = Express.Router();

const UserMiscData = require("../models/user-misc-data.js");

Router.get("/get-recent-message", async (Request, Response) => {
    try {
        const UserID = Request.query.userid;

        if (!UserID) {
            return Response.status(400).send("UserID is required.");
        };

        const User = await UserMiscData.findById(UserID);

        if (!User) {
            const NewUserMisc = new UserMiscData({
                _id: UserID,
                MostRecentMessageID: ""
            });
    
            await NewUserMisc.save();

            return Response.status(201).json({ MessageID: NewUserMisc.MostRecentMessageID });
        };

        return Response.status(200).json({ MessageID: User.MostRecentMessageID });
    } catch (Error) {
        console.error("An error occurred while getting the recent message:", Error);

        return Response.status(500).send("An unexpected error occurred.");
    }
});

Router.put("/update-recent-message", async (Request, Response) => {
    try {
        const { UserID, MessageID } = Request.body;

        if (!UserID || !MessageID) {
            return Response.status(400).send("UserID and MessageID are required.");
        }

        const User = await UserMiscData.findById(UserID);

        if (!User) {
            const NewUserMisc = new UserMiscData({
                _id: UserID,
                MostRecentMessageID: MessageID
            });
    
            await NewUserMisc.save();

            return Response.status(201).send("Successfully created recent-message data.");
        }

        User.MostRecentMessageID = MessageID;

        await User.save();

        return Response.status(200).send("Successfully updated recent-message data.");
    } catch (Error) {
        console.error("An error occurred while updating the recent message:", Error);

        return Response.status(500).send("An unexpected error occurred.");
    }
});

module.exports = Router;