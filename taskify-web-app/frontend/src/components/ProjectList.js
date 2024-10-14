import "../styles/ProjectList.css";

import { Link } from "react-router-dom";

import ActionBar from "./ActionBar.js";

const SearchBar = ({ StartIcon }) => {
    return (
        <div className="ActionBar">
            <div className="SearchBarContainer">
                {StartIcon&& <div className="FlexStartRow">
                    <Link to="/"> <i className={StartIcon}></i> </Link>
                </div>}

                <input className="SearchBar FlexEndRow" placeholder="Search projects"></input>
            </div>
        </div>
    );
}

export default function ProjectList() {
    return (
        <div id="ProjectList">
            <ActionBar StartText="Projects" EndButtons={["bi bi-plus-lg", "bi bi-chevron-up"]}/>     
            <SearchBar StartIcon="bi bi-search"/>

            <div id="ProjectForm">
            </div>
        </div>
    )
}