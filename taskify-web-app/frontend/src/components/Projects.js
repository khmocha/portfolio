import { useEffect, useState } from "react";
import { Navigate } from "react-router-dom"

import "../styles/Projects.css";

import SideBar from "./SideBar.js";
import Project from "./Project.js";

export default function Projects() {
    const [SessionExists, SetSessionExists] = useState(null);

    useEffect(() => {
        (async () => {
            try {
                const Response = await fetch("http://localhost:3001/load-projects", {
                    credentials: "include"
                });

                const ResponseText = await Response.text();

                console.log(ResponseText);

                if (Response.status === 200) {
                    SetSessionExists(true);
                } else {
                    SetSessionExists(false);
                }
                
            } catch (Error) {
                console.log(`An error occurred while trying to load data: ${Error}`);
            }
        })();
    }, []);

    return (
        <>  
            {SessionExists !== null && (
                SessionExists ? (
                    <div id="ProjectsPage">
                        <SideBar/>
                        <Project/>
                    </div>
                ) : (
                    <Navigate to="/signin"/> 
                )
            )}
        </>
    );
}