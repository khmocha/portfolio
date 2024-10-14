const Express = require("express");
const Mongoose = require("mongoose");
const Cors = require("cors");
const BodyParser = require("body-parser");
const Session = require("express-session");
const MongoStore = require("connect-mongo");
const CookieParser = require("cookie-parser");

const AuthenticationRoute = require("./routes/authentication.js");
const ProjectsRoute = require("./routes/projects.js");

const Server = Express();
const Port = 3001;
const Domain = "localhost";

const DatabaseURI = "mongodb+srv://Khang:Khang4321@taskifycluster.ulfozmt.mongodb.net/TaskifyDB";

const SessionOptions =  {
    mongoUrl: DatabaseURI,
    collectionName: "Sessions",
    ttl: 60 * 60 * 24,
};

Server.use(Cors({
    origin: "http://localhost:3000",
    credentials: true
}));

Server.use(BodyParser.json());
Server.use(CookieParser());

Server.use(Session({
    secret: "082r3no23rowqddinqdurg9320qwwdk",
    resave: false,
    saveUninitialized: false,
    store: MongoStore.create(SessionOptions),

    cookie: {
        maxAge: 86400000,
        httpOnly: false,
        secure: false,
    }
}));

Server.use((_, Response, Next) => {
    Response.header("Access-Control-Allow-Credentials", true);
    Next();
});

Server.use(AuthenticationRoute);
Server.use(ProjectsRoute);

Mongoose.connect(DatabaseURI).then(() => {
    Server.listen(Port, Domain, () => {
        console.log(`Connected to MongoDB. Server is now listening on port ${Port}`);
    })
}).catch(Error => {
    console.log(`An error occurred while connecting to MongoDB: ${Error}`);
})