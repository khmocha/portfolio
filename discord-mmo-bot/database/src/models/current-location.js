const Mongoose = require("mongoose");
const Schema = Mongoose.Schema;

const CurrentLocationSchema = new Schema({
    _id: {
        type: String,
        required: true
    }, 

    Settlement: { 
        type: String, 
        required: true 
    },

    Establishment: {
        type: String,
        required: true
    }
});

const CurrentLocationModel = Mongoose.model("UsersLocation", CurrentLocationSchema, "UsersLocation");

module.exports = CurrentLocationModel;