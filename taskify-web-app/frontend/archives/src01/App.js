import {BrowserRouter as Router, Routes, Route } from "react-router-dom";

import SignUp from "./components/SignUp.js";
import SignIn from "./components/SignIn.js";
import Projects from "./components/Projects.js";

function App() {
  return (
    <Router>
      <Routes>
        <Route exact path="/signup" element={<SignUp/>}></Route>
        <Route exact path="/signin" element={<SignIn/>}></Route>
        <Route exact path="/projects" element={<Projects/>}></Route>
      </Routes>
    </Router>
  );
}

export default App;