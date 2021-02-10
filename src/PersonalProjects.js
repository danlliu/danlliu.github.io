import React from "react";

import html5 from './html5.svg';
import css from './css.svg';
import react from './react.svg';
import js from './js.svg';
import boot from './bootstrap.svg';
import swift from './swift.svg';

import ReactCSSTransitionGroup from 'react-transition-group/CSSTransitionGroup';

let project_list = [
    {name: "danlliu.github.io", icons: ["html5", "css", "react"], type: "personal website"},
    {name: "Turret Wars", icons: ["swift"], type: "macOS Game"},
    {name: "beep boop", icons: ["html5", "css", "bootstrap", "js"], type: "programming language"},
    {name: "shift", icons: ["html5", "css", "bootstrap", "js"], type: "programming language"},
    {name: "this is all made up", icons: ["html5", "css", "bootstrap", "js"], type: "programming language"},
    {name: "creative writing", icons: ["html5", "css", "bootstrap", "js"], type: "programming language"},
    {name: "LC2K01", icons: ["html5", "css", "bootstrap", "js"], type: "assembly language simulator"}
];

const img_lookup = {
    "html5": html5,
    "css": css,
    "react": react,
    "bootstrap": boot,
    "js": js,
    "swift": swift
};

const alt_text = {
    "html5": "HTML 5",
    "css": "CSS 3",
    "react": "React.js",
    "bootstrap": "Bootstrap",
    "js": "Javascript",
    "swift": "Swift"
};

class ProjectList extends React.Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <ReactCSSTransitionGroup transitionName="projectcard" transitionEnterTimeout={500} component={"div"}
                                     transitionLeaveTimeout={500} className={"flexbox wide-scroll"} style={{flexWrap: "none"}}>
            {project_list.map((x, i) => {
                let select = (i === this.props.selected) ? "card-selected" : "";
                let classes = `card ${select}`;
                if (this.props.filter !== "none") {
                    if (!x.icons.includes(this.props.filter)) {
                        return <div key={i}/>
                    }
                }
                return (<div className={classes} key={i} onClick={() => this.select(i)}>
                    {x.icons.map(y => <img src={img_lookup[y]} alt={alt_text[y]} title={alt_text[y]} height={36} width={36} style={{margin: 4}} key={y}/>)}
                    <h3 style={{marginBottom: 0}}>{x.name}</h3>
                    <h4 style={{marginBottom: 0}}>{x.type}</h4>
                </div>)
            })}
            </ReactCSSTransitionGroup>
        );
    }

    select(key) {
        this.props.selectFunc(key);
        console.log("hello");
    }

}

class PersonalProjects extends React.Component {

    constructor(props) {
        super(props);
        this.state = {selected: 0, filter: "none"};
        this.select = this.select.bind(this);
    }

    select(key) {
        this.setState({selected: key, filter: this.state.filter});
    }

    filter(key) {
        this.setState({selected: this.state.selected, filter: key});
    }

    render() {
        return (<div>
            <div className={"flexbox"} style={{margin: 8, alignItems: "center"}}>
                <h4 style={{margin: 0}}>filter by:</h4>
                {["html5", "css", "react", "bootstrap", "js", "swift"].map((x) => {
                    return <img src={img_lookup[x]} key={x} alt={alt_text[x]} title={alt_text[x]} width={36} height={36}
                                style={{margin: "0 8px"}} onClick={() => this.filter(x)}/>
                })}
            </div>
            <div className={"flexbox"} style={{alignContent: "spaceBetween"}}>
                <button style={{width: "2%"}}>&lt;</button>
                <ProjectList selected={this.state.selected} selectFunc={this.select} filter={this.state.filter}/>
                <button style={{width: "2%"}}>&gt;</button>
            </div>
        </div>);
    }

}

export default PersonalProjects;
