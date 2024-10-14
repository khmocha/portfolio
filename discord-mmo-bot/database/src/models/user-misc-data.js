const Mongoose = require("mongoose");
const Schema = Mongoose.Schema;

const UserMiscData = new Schema({
    _id: {
        type: String,
        required: true
    }, 

    MostRecentMessageID: {
        type: String,
        required: true
    }
});

const UserMiscModel = Mongoose.model("UsersMisc", UserMiscData, "UsersMisc");

module.exports = UserMiscModel;