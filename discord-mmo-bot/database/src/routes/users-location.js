const Express = require("Express");

const Router = Express.Router();

const CurrentLocation = require("../models/current-location.js");

Router.get("/get-current-location", async (Request, Response) => {
    try {
        const UserID = Request.query.userid;

        const User = await CurrentLocation.findById(UserID);

        if (!User) {
            const NewUserLocation = new CurrentLocation({
                _id: UserID,
                Settlement: "New Leaf",
                Establishment: "Unselected"
            });
    
            await NewUserLocation.save();

            return Response.status(200).json({Settlement: NewUserLocation.Settlement, Establishment: NewUserLocation.Establishment});
        }

        return Response.status(200).json({Settlement: User.Settlement, Establishment: User.Establishment});
    } catch (Error) {
        console.error("An error occurred while retrieving the current location:", Error);

        return Response.status(500).send("An unexpected error occurred.");
    }
});

Router.put("/update-settlement", async (Request, Response) => {
    try {
        const { UserID, NewSettlement } = Request.body;

        const User = await CurrentLocation.findById(UserID);

        if (!User) {
            return Response.status(400).send("Cannot update settlement if the user ID does not exist.");
        }

        User.Settlement = NewSettlement;

        await User.save();

        return Response.status(200).send("Successfully updated settlement.");
    } catch (Error) {
        console.error("An error occurred while updating the current settlement:", Error);

        return Response.status(500).send("An unexpected error occurred.");
    }
});

Router.put("/update-establishment", async (Request, Response) => {
    try {
        const { UserID, NewEstablishment } = Request.body;

        const User = await CurrentLocation.findById(UserID);

        if (!User) {
            return Response.status(400).send("Cannot update establishment if the user ID does not exist.");
        }

        User.Establishment = NewEstablishment;

        await User.save();

        return Response.status(200).send("Successfully updated establishment.");
    } catch (Error) {
        console.error("An error occurred while updating the current establishment:", Error);

        return Response.status(500).send("An unexpected error occurred.");
    }
});

module.exports = Router;

