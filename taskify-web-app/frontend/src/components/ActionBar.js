import { Link } from "react-router-dom";

import ButtonFunctions from "./SideBarFunctions";

const ActionBar = ({ StartIcon, StartText, EndButtons }) => {
    return (
        <div className="ActionBar">
            {(StartIcon || StartText) && <div className="FlexStartRow">
                {StartIcon && <Link to="/"> <i className={StartIcon}></i> </Link>}
                {StartText && <Link to="/"> {StartText} </Link>}
            </div>}
            
            {EndButtons && <div className="FlexEndRow">
                {EndButtons.map((EndButton, Index) => {
                    return (<button key={Index} className="Button"> <i className={EndButton} onClick=
                    {() => {ButtonFunctions["bi bi-plus-lg"]()}}/> </button>);
                })}
            </div>}
        </div>
    );
}

export default ActionBar;