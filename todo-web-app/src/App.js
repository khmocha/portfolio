import {useRef} from "react";

import {BrowserRouter as Router, Routes, Route, Link} from "react-router-dom";

import NavBarCSS from "./css_modules/NavBar.module.css";

import Home from "./components/Home.js";
import Learn from "./components/Learn.js";
import About from "./components/About.js";

var UnderlineRef = null;

const UnderlinePage = (Event, UnderlineObj) => {
  let TargetObj = Event.target;

  UnderlineObj.style.opacity = 1;
  UnderlineObj.style.width = `${TargetObj.offsetWidth}px`;
  UnderlineObj.style.left = `${TargetObj.getBoundingClientRect().x}px`;
}

const RemoveUnderline = (UnderlineObj) => {
  UnderlineObj.style.opacity = 0;
}

export default function App() {
  const LeftNavPages = [
    <Link to="/" key="home" 
      onMouseEnter={(Event) => {UnderlinePage(Event, UnderlineRef.current)}}
      onMouseLeave={() => {RemoveUnderline(UnderlineRef.current)}}> 
      Home 
    </Link>,
  
    <Link to="/learn" key="learn"
      onMouseEnter={(Event) => {UnderlinePage(Event, UnderlineRef.current)}}
      onMouseLeave={() => {RemoveUnderline(UnderlineRef.current)}}>
      Learn 
    </Link>,
  
    <Link to="/about" key="about"
      onMouseEnter={(Event) => {UnderlinePage(Event, UnderlineRef.current)}}
      onMouseLeave={() => {RemoveUnderline(UnderlineRef.current)}}> 
      About 
    </Link>,
  ];
  
  const RightNavPages = [
    <Link to="/signin" key="signin" 
      onMouseEnter={(Event) => {UnderlinePage(Event, UnderlineRef.current)}}
      onMouseLeave={() => {RemoveUnderline(UnderlineRef.current)}}> 
      Sign In 
    </Link>,
  
    <Link to="/createaccount" key="createaccount" 
      onMouseEnter={(Event) => {UnderlinePage(Event, UnderlineRef.current)}}
      onMouseLeave={() => {RemoveUnderline(UnderlineRef.current)}}> 
      Create Account 
    </Link>,
  
    <Link id={NavBarCSS.CreateTasks} to="/createtasks" key="createtasks">
        Create Tasks 
        <div className={NavBarCSS.GraySquare}></div>
    </Link>
  ]
  
  UnderlineRef = useRef();

  return (
    <Router>
      <Routes>
        <Route exact path="/" element={<Home LeftPages={LeftNavPages} RightPages={RightNavPages} UnderlineRef={UnderlineRef}/>}/>
        <Route exact path="/learn" element={<Learn LeftPages={LeftNavPages} RightPages={RightNavPages} UnderlineRef={UnderlineRef}/>}/>
        <Route exact path="/about" element={<About LeftPages={LeftNavPages} RightPages={RightNavPages} UnderlineRef={UnderlineRef}/>}/>
      </Routes>
    </Router>
  );
}
