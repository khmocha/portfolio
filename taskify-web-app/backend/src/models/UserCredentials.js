const Mongoose = require("mongoose");
const Schema = Mongoose.Schema;

const UserCredentialsSchema = new Schema({
    Username: { 
        type: String, 
        required: true 
    },

    Password: {
        type: String,
        required: true
    }
})

const UserCredentialsModel = Mongoose.model("UserCredentials", UserCredentialsSchema, "UserCredentials");

module.exports = UserCredentialsModel;