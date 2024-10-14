const Express = require("Express");

const Router = Express.Router();

const UserProjects = require("../models/UserProjects.js");

Router.get("/load-projects", async (Request, Response) => {
    try {
        if (Request.session.UserID === undefined) {
            return Response.status(401).send("User session not found");
        }

        const User = await UserProjects.findById(Request.session.UserID);

        if (User) {
            return Response.status(200).send("User session found");
        } else {
            return Response.status(401).send("User does not exist");
        }
    } catch (Error) {
        console.log(Error);

        return Response.status(500).send("An unexpected error occurred on the server");
    }
})

Router.post("/create-project", async (Request, Response) => {
    try {
        if (Request.session.UserID === undefined) {
            return Response.status(401).send("User session not found");
        }

        const Projects = await UserProjects.findById(Request.session.UserID);

        if (Projects) {
            const { ProjectName } = Request.body;

            if (Projects.ProjectsList === null) {
                await Projects.updateOne({
                    $set: {
                        ProjectsList: {},
                        ProjectsContent: {} 
                    }
                });
            }

            await Projects.updateOne({
                $set: {
                    [`ProjectsList.${ProjectName}`]: ProjectName,
                    [`ProjectsContent.${ProjectName}`]: {
                      Name: ProjectName,
                      Boards: null
                    }
                }
            });
            
            return Response.status(200).send("Created project successfully!");
        } else {
            return Response.status(401).send("User does not exist");
        }
    } catch (Error) {
        console.log(Error);

        return Response.status(500).send("An unexpected error occurred on the server");
    }
})

Router.get("/clear-session", (Request, Response) => {
    try {
        Response.clearCookie("SessionID");
        Request.session.destroy();

        return Response.status(200).send("Session and cookies cleared successfully!");
    } catch (Error) {
        console.log(Error);

        return Response.status(500).send("An unexpected error occurred on the server");
    }
})

module.exports = Router;