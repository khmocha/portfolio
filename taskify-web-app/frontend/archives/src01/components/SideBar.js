import { useState, useRef } from "react";
import { Link } from "react-router-dom"

import "../styles/SideBar.css";

const ClearSession = () => {
    fetch("http://localhost:3001/clear-session", {
            credentials: "include"
    })
    .then(() => {
        console.log("User session cleared");
    })
    .catch(Error => {
        console.log(`An error occurred while trying to clear session during sign out: ${Error}`)
    });
}

export default function SideBar() {
    const [ProjectForm, SetProjectForm] = useState(false);

    const [ProjectsList, SetProjectsList] = useState({});
    
    const ProjectName = useRef(null);

    const ToggleProjectForm = () => {
        SetProjectForm(!ProjectForm);
    }

    const CreateProject = async () => {
        try {
            const RequestOptions = {
                method: "POST",
                
                headers: {
                    "Content-Type": "application/json"
                },

                credentials: "include",

                body: JSON.stringify({
                    ProjectName: ProjectName.current.value
                })
            }

            const Response = await fetch("http://localhost:3001/create-project", RequestOptions);
            const ResponseText = await Response.text();

            console.log(ResponseText);

            if (Response.status === 200) {
                SetProjectsList({...ProjectsList, [ProjectName.current.value]: ProjectName.current.value});
            } 
        } catch (Error) {
            console.log(`An error occurred while trying to create project: ${Error}`);
        }
    }

    return (
        <div id="SideBar">
            <div className="Header">
                <span className="Logo"> Logo </span>
                <button className="Toggle"></button>
            </div>

            <div className="Navigation">
                <Link to="/signup" onClick={ClearSession}> Sign out </Link>
                <div className="NavigationRow">
                    <img src="" alt=""></img>
                    <button> Home </button>
                </div>

                <div className="NavigationRow">
                    <img src="" alt=""></img>
                    <button> Test </button>
                </div>

                <div className="NavigationRow">
                    <img src="" alt=""></img>
                    <button> Test2 </button>
                </div>
            </div>

            <div className="ProjectsList">
                <div className="Header">
                    <span className="ProjectTitle"> Project </span>
                    <button onClick={ToggleProjectForm}> + </button>
                    <button> v </button>
                </div>

                <input className="ProjectSearchBar" placeholder="Search project"></input>

                {ProjectForm && 
                    <>
                        <input placeholder="Enter project name" ref={ProjectName}></input>
                        <button onClick={CreateProject}> Create </button>
                    </>
                }

                {Object.keys(ProjectsList).map((ProjectKey, Index) => {
                    return (
                        <div key={Index} className="Project"> {ProjectKey} </div>
                    )
                })}
            </div>
        </div>
    )
}