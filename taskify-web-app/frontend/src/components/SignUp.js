import { useRef, useState } from "react";
import { Navigate } from "react-router-dom"

export default function SignUp() {
    const UsernameInput = useRef(null);
    const PasswordInput = useRef(null);
    const [SignedUp, SetSignedUp] = useState(false);

    const CreateAccount = async () => {
        try {
            const RequestOptions = {
                method: "POST",
                
                headers: {
                    "Content-Type": "application/json"
                },

                body: JSON.stringify({
                    username: UsernameInput.current.value,
                    password: PasswordInput.current.value
                })
            }

            const Response = await fetch("http://localhost:3001/sign-up", RequestOptions);
            const ResponseText = await Response.text();

            console.log(ResponseText);

            if (Response.status === 200) {
                SetSignedUp(true);
            } else {
                SetSignedUp(false);
            }
        } catch (Error) {
            console.log(`An error occurred while attempting to create an account: ${Error}`);
        }
    }

    return (
        <>
            {SignedUp && <Navigate to="/signin"/>}
            <span> Sign Up </span>
            <input type="text" placeholder="Enter your username" ref={UsernameInput}/>
            <input type="password" placeholder="Enter your password" ref={PasswordInput}/>
            <button onClick={CreateAccount}> Submit </button>
        </>
    );
}