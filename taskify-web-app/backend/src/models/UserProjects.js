const Mongoose = require("mongoose");
const Schema = Mongoose.Schema;

const UserProjectsSchema = new Schema({
    ProjectsList: {
        type: Object,
        required: false
    },

    ProjectsContent: {
        type: Object,
        required: false
    }
})

const UserProjectsModel = Mongoose.model("UserProjects", UserProjectsSchema, "UserProjects");

module.exports = UserProjectsModel;