import "../styles/Navigation.css";

import ActionBar from "./ActionBar.js";

export default function Navigation() {
    return (
        <div id="Navigation">
            <ActionBar StartIcon="bi bi-hypnotize" StartText="Taskify" EndButtons={["bi bi-text-right"]}/>
            <ActionBar StartIcon="bi bi-house-door" StartText="Home"/>
            <ActionBar StartIcon="bi bi-person" StartText="Profile"/>
            <ActionBar StartIcon="bi bi-layout-text-window-reverse" StartText="Dashboard"/>
            <ActionBar StartIcon="bi bi-check2-square" StartText="Upcoming"/>
            <ActionBar StartIcon="bi bi-exclamation-triangle" StartText="Overdue"/>
            <ActionBar StartIcon="bi bi-sliders" StartText="Settings"/>
        </div>
    )
}