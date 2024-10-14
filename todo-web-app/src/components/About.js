import NavBar from "./NavBar.js";

export default function About(Props) {
    return (
        <NavBar LeftPages={Props.LeftPages} RightPages={Props.RightPages} UnderlineRef={Props.UnderlineRef}/>
    );
}