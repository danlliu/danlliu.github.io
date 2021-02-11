import React from "react";

import html5 from './html5.svg';
import css from './css.svg';
import react from './react.svg';
import js from './js.svg';
import boot from './bootstrap.svg';
import swift from './swift.svg';
import socket from './socket.svg';

import ReactCSSTransitionGroup from 'react-transition-group/CSSTransitionGroup';

let project_list = [
    {name: "danlliu.github.io", icons: ["html5", "css", "react"], type: "personal website"},
    {name: "Turret Wars", icons: ["swift"], type: "macOS Game"},
    {name: "chatroom", icons: ["html5", "css", "bootstrap", "js", "socket"], type: "chat application"},
    {name: "beep boop", icons: ["html5", "css", "bootstrap", "js"], type: "programming language"},
    {name: "shift", icons: ["html5", "css", "bootstrap", "js"], type: "programming language"},
    {name: "this is all made up", icons: ["html5", "css", "bootstrap", "js"], type: "programming language"},
    {name: "creative writing", icons: ["html5", "css", "bootstrap", "js"], type: "programming language"},
    {name: "LC2K01", icons: ["html5", "css", "bootstrap", "js"], type: "assembly language simulator"}
];

let indices = project_list.map((_,i)=>i);

const img_lookup = {
    "html5": html5,
    "css": css,
    "react": react,
    "bootstrap": boot,
    "js": js,
    "swift": swift,
    "socket": socket
};

const alt_text = {
    "html5": "HTML 5",
    "css": "CSS 3",
    "react": "React.js",
    "bootstrap": "Bootstrap",
    "js": "Javascript",
    "swift": "Swift",
    "socket": "socket.io"
};

const description_files = ["projects/danlliugithubio.html"];

class ProjectList extends React.Component {
    constructor(props) {
        super(props);
    }


    // .filter(x => {
    //                 if (this.props.filter === "none") {return true;}
    //                 return x.icons.includes(this.props.filter);
    //             })
    render() {
        return (
            <ReactCSSTransitionGroup transitionName="projectcard" transitionEnterTimeout={0} component={"div"}
                                     transitionLeaveTimeout={0} className={"flexbox wide-scroll"} id={"projectlist"}>
            {project_list.map((x, i) => {
                let select = (i === this.props.selected) ? "card-selected" : "";
                let classes = `card ${select}`;
                if (this.props.filter !== "none" && !x.icons.includes(this.props.filter)) {
                    return <div></div>
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
        this.left = this.left.bind(this);
        this.right = this.right.bind(this);
    }

    select(key) {
        this.setState({selected: key, filter: this.state.filter});
        document.getElementById("projectlist").children[key].scrollIntoView({behavior: "smooth"});
    }

    filter(key) {
        if (this.state.filter === key) {
            this.setState({selected: this.state.selected, filter: "none"});
        } else {
            this.setState({selected: this.state.selected, filter: key});
        }
    }

    left() {
        let new_selected = this.state.selected;
        do {
            console.log(new_selected);
            new_selected = (new_selected + project_list.length - 1) % project_list.length;
        } while (this.state.filter !== "none" && !project_list[new_selected].icons.includes(this.state.filter));
        this.setState({selected: new_selected, filter: this.state.filter});
        document.getElementById("projectlist").children[new_selected].scrollIntoView({behavior: "smooth"});
    }

    right() {
        let new_selected = this.state.selected;
        do {
            console.log(new_selected);
            new_selected = (new_selected + 1) % project_list.length;
        } while (this.state.filter !== "none" && !project_list[new_selected].icons.includes(this.state.filter));
        this.setState({selected: new_selected, filter: this.state.filter});
        document.getElementById("projectlist").children[new_selected].scrollIntoView({behavior: "smooth"});
    }

    render() {
        return (<div>
            <div className={"flexbox"} style={{margin: 8, alignItems: "center"}}>
                <h4 style={{margin: 0}}>filter by:</h4>
                {["html5", "css", "react", "bootstrap", "js", "swift", "socket"].map((x) => {
                    return <img src={img_lookup[x]} key={x} alt={alt_text[x]} title={alt_text[x]} width={this.state.filter === x ? 40 : 36}
                                height={this.state.filter === x ? 40 : 36} style={{margin: "0 8px", opacity: this.state.filter === x ? 1.0 : 0.4}} onClick={() => this.filter(x)}/>
                })}
            </div>
            <div className={"flexbox"} style={{alignContent: "spaceBetween"}}>
                <button style={{width: "2%"}} onClick={this.left}>&lt;</button>
                <ProjectList selected={this.state.selected} selectFunc={this.select} filter={this.state.filter}/>
                <button style={{width: "2%"}} onClick={this.right}>&gt;</button>
            </div>
            {((s) => {
                return (<div className={"card-wide"}>
                    <h3>{project_list[s].name}</h3>
                </div>)
            })(this.state.selected)}
        </div>);
    }

}

export default PersonalProjects;
