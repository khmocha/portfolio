import { useRef, useState } from "react";
import { Navigate } from "react-router-dom";

export default function SignIn() {
    const UsernameInput = useRef(null);
    const PasswordInput = useRef(null);
    const [SignedIn, SetSignedIn] = useState(false);

    const SignIn = async () => {
        try {
            const RequestOptions = {
                method: "POST",
                
                headers: {
                    "Content-Type": "application/json"
                },

                credentials: "include",

                body: JSON.stringify({
                    username: UsernameInput.current.value,
                    password: PasswordInput.current.value
                })
            }

            const Response = await fetch("http://localhost:3001/sign-in", RequestOptions);
            const ResponseText = await Response.text();

            console.log(ResponseText);

            if (Response.status === 200) {
                SetSignedIn(true);
            } else {
                SetSignedIn(false);
            }
        } catch (Error) {
            console.log(`An error occurred while attempting to sign in: ${Error}`);
        }
    }

    return (
        <>
            {SignedIn && <Navigate to="/projects"/>}
            <span> Sign In </span>
            <input type="text" placeholder="Enter your username" ref={UsernameInput}/>
            <input type="password" placeholder="Enter your password" ref={PasswordInput}/>
            <button onClick={SignIn}> Submit </button>
        </>
    );
}