import React from "react";

import NavBarCSS from "../css_modules/NavBar.module.css";

import TODOLogo from "../images/TODOLogo.png";

export default function NavBar(Props) {
    return (
        <div id={NavBarCSS.NavBar}>
            <img id={NavBarCSS.Logo} src={TODOLogo} alt=""/>

            <div id={NavBarCSS.LeftPages}>
                {Props.LeftPages.map(Page => {
                    return <React.Fragment key={Page.key}>
                        {Page}
                    </React.Fragment>
                })}
            </div>

            <div id={NavBarCSS.RightPages}>
                {Props.RightPages.map(Page => {
                    return <React.Fragment key={Page.key}>
                        {Page}
                    </React.Fragment>
                })}
            </div>

            <div id={NavBarCSS.Strip}>
                <div className={NavBarCSS.GreySquare}></div>
            </div>

            <div id={NavBarCSS.Underline} ref={Props.UnderlineRef}>
                <div className={NavBarCSS.GreySquare}></div>
            </div>
        </div>
    );
}