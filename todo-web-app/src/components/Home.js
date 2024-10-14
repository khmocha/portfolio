import HomeCSS from "../css_modules/Home.module.css"

import NavBar from "./NavBar.js";

import Notes1 from "../images/Notes1.png";
import Notes2 from "../images/Notes2.png";
import Notes3 from "../images/Notes3.png";

export default function Home(Props) {
    return (
        <>
            <div id={HomeCSS.VerticalContainer}>
                <NavBar LeftPages={Props.LeftPages} RightPages={Props.RightPages} UnderlineRef={Props.UnderlineRef}/>
                <div id={HomeCSS.IntroductionContainer}>
                    <h1 id={HomeCSS.IntroductionTitle}> Streamline Your Tasks </h1>

                    <p id={HomeCSS.IntroductionContext}> 
                        Organizing tasks can be a difficult process. With my built-in features,
                        ToDo makes it easy to efficiently organize and manage your tasks digitally.
                    </p>

                    <button id={HomeCSS.GetStartedFree} onClick={() => {console.log("Hello")}}> 
                        Get Started Free 
                        <div className={HomeCSS.GreySquare}></div>
                    </button>

                    <div id={HomeCSS.Circle}></div>

                    <img id={HomeCSS.Notes1} className={HomeCSS.Images} src={Notes1} alt=""/>
                    <img id={HomeCSS.Notes2} className={HomeCSS.Images} src={Notes2} alt=""/>
                    <img id={HomeCSS.Notes3} className={HomeCSS.Images} src={Notes3} alt=""/>
                </div>
            </div>
        </>
    );
}