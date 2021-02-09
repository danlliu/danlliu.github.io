import React from 'react';
import ReactDOM from 'react-dom';

import HeaderBar from "./HeaderBar";
import Education from "./Education";

import './index.css';
import reportWebVitals from './reportWebVitals';


ReactDOM.render(<HeaderBar/>, document.getElementById('header'));

ReactDOM.render(<Education/>, document.getElementById('education'));

// If you want to start measuring performance in your app, pass a function
// to log results (for example: reportWebVitals(console.log))
// or send to an analytics endpoint. Learn more: https://bit.ly/CRA-vitals
reportWebVitals();
