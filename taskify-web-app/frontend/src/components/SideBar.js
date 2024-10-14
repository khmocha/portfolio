import "../styles/SideBar.css";

import Navigation from "./Navigation.js";
import ProjectList from "./ProjectList.js";

export default function SideBar() {
    return (
        <div id="SideBar">
            <Navigation/>
            <ProjectList/>
        </div>
    );
}