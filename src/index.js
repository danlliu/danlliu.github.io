import React from 'react';
import ReactDOM from 'react-dom';

import HeaderBar from "./HeaderBar";
import Education from "./Education";
import Transition from "./Transition";
import Coursework from "./Coursework";
import WorkExperience from "./WorkExperience";
import PersonalProjects from "./PersonalProjects";

import './index.css';
import reportWebVitals from './reportWebVitals';


ReactDOM.render(<HeaderBar/>, document.getElementById('header'));

ReactDOM.render(<Education/>, document.getElementById('education'));

ReactDOM.render(<Coursework/>, document.getElementById('coursework'));

ReactDOM.render(<Transition top={"var(--light-cyan)"} bottom={"var(--cosmic-latte)"}/>,
    document.getElementById('about-exp-transition'));

ReactDOM.render(<WorkExperience/>, document.getElementById('workexperience'));

ReactDOM.render(<Transition top={"var(--cosmic-latte)"} bottom={"var(--pale-purple)"}/>,
    document.getElementById('exp-project-transition'));

ReactDOM.render(<PersonalProjects/>, document.getElementById('personalprojects'));

// If you want to start measuring performance in your app, pass a function
// to log results (for example: reportWebVitals(console.log))
// or send to an analytics endpoint. Learn more: https://bit.ly/CRA-vitals
reportWebVitals();
