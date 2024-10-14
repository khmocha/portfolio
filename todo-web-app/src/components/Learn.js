import {useEffect} from "react";

import Home from "./Home.js";

export default function Learn(Props) {
    useEffect(() => {
        window.scrollTo({top: 750, behavior: "smooth"});
    }, []);

    return (
        <Home LeftPages={Props.LeftPages} RightPages={Props.RightPages} UnderlineRef={Props.UnderlineRef}/>
    );
}