import { Link } from "react-router-dom";

import "../styles/SideBar.css";

export default function SideBar() {
    return (
        <div id="SideBar">
            <div id="Navigation">
                <div className="LogoHeader">
                    <Link className="LogoLink" to="/"> 
                        <i className="bi bi-hypnotize"></i>
                    </Link>

                    <Link className="LogoName" to="/"> Taskify </Link>
                    
                    <div className="FlexEndItems">
                        <button className="ToggleButton"> 
                            <i className="bi bi-text-right"></i>
                        </button>
                    </div>
                </div>

                <div className="NavigationRow">
                    <Link to="/">
                        <i className="bi bi-house-door"></i>
                    </Link>

                    <Link to="/"> Home </Link>
                </div>

                <div className="NavigationRow">
                    <Link to="/">
                        <i className="bi bi-person"></i>
                    </Link>

                    <Link to="/"> Profile </Link>
                </div>

                <div className="NavigationRow">
                    <Link to="/">
                        <i className="bi bi-layout-text-window-reverse"></i>
                    </Link>

                    <Link to="/"> Dashboard </Link>
                </div>

                <div className="NavigationRow">
                    <Link to="/">
                        <i className="bi bi-check2-square"></i>
                    </Link>

                    <Link to="/"> Upcoming </Link>
                </div>

                <div className="NavigationRow">
                    <Link to="/">
                        <i className="bi bi-exclamation-triangle"></i>
                    </Link>

                    <Link to="/"> Overdue </Link>
                </div>

                <div className="NavigationRow">
                    <Link to="/">
                        <i className="bi bi-sliders"></i>
                    </Link>

                    <Link to="/"> Settings </Link>
                </div>
            </div>

            <div id="ProjectsList"> 
                <div className="ProjectsHeader">
                    <span> Projects </span>

                    <div className="FlexEndItems">
                        <button className="ToggleButton"> 
                            <i className="bi bi-plus-lg"></i>
                        </button>

                        <button className="ToggleButton"> 
                            <i className="bi bi-chevron-up"></i>
                        </button>
                    </div>
                </div>

                <div className="SearchBarContainer"> 
                    <input className="ProjectSearchBar" placeholder="Search Projects"></input>
                    <i className="bi bi-search"></i>
                </div>
            </div>
        </div>
    );
}