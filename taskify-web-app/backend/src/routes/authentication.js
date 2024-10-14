const Express = require("Express");
const Bcrypt = require("bcrypt");

const SaltRounds = 10;

const Router = Express.Router();

const UserCredentials = require("../models/UserCredentials.js");
const UserProjects = require("../models/UserProjects.js");

Router.post("/sign-up", async (Request, Response) => {
    try {
        const { username, password } = Request.body;

        const User = await UserCredentials.findOne({Username: username});

        if (!User) {
            const HashedPassword = await Bcrypt.hash(password, SaltRounds);

            const NewAccount = new UserCredentials({
                Username: username,
                Password: HashedPassword
            });
    
            await NewAccount.save();

            const NewProjects = new UserProjects({
                _id: NewAccount._id,
                ProjectsList: null,
                ProjectsContent: null
            });

            await NewProjects.save();
        
            return Response.status(200).send("Account successfully created!");
        } else {
            return Response.status(403).send("Username already exists");
        }
    } catch (Error) {
        console.log(Error);

        return Response.status(500).send("An unexpected error occurred on the server");
    }
})

Router.post("/sign-in", async (Request, Response) => {
    try {
        const { username, password } = Request.body;

        const User = await UserCredentials.findOne({Username: username});

        if (User) {
            const PasswordMatches = await Bcrypt.compare(password, User.Password);

            if (PasswordMatches) {
                Request.session.UserID = User._id;

                Response.cookie("SessionID", Request.sessionID);

                return Response.status(200).send("Signed in successfully!");
            } else {
                return Response.status(401).send("Invalid username or password");
            }
        } else {
            return Response.status(401).send("Invalid username or password");
        }
    } catch (Error) {
        console.log(Error);

        return Response.status(500).send("An unexpected error occurred on the server");
    }
})

module.exports = Router;