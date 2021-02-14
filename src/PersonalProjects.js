import React, {Fragment} from "react";

import html5 from './html5.svg';
import css from './css.svg';
import react from './react.svg';
import js from './js.svg';
import boot from './bootstrap.svg';
import swift from './swift.svg';
import socket from './socket.svg';

// Turret Wars images

import turret1 from './img/turret1.png';
import turret2 from './img/turret2.png';
import turret3 from './img/turret3.png';

// chatroom images

import chatroom1 from './img/chatroom1.png';

import ReactCSSTransitionGroup from 'react-transition-group/CSSTransitionGroup';

let project_list = [
    {name: "danlliu.github.io", icons: ["html5", "css", "react", "js"], type: "personal website", description: `
        You're here right now! This is my personal website, designed with HTML, CSS, Javascript, and React.js. It showcases key parts of my resume and the projects that I've worked on. If you're clever, you might be able to find an easter egg or two :)
    `},
    {name: "Turret Wars", icons: ["swift"], type: "macOS Game", description: `
        Over the course of approximately a week, I designed a space-themed shooter game. In this game, your aim is to take out turrets before they take you out. After a few levels, you're able to use shields to take damage, and later on use an EMP to stop turrets from shooting temporarily. The project as a whole was over 3000 lines of Swift code, and was coded using Apple's SpriteKit framework for the physics and animation.
    `, images: [{src: turret1, caption: "A Sniper Turret firing a fast bullet."},
            {src: turret2, caption: "Barriers can spawn in the randomly generated maps, giving you cover but also acting as obstacles."},
            {src: turret3, caption: "After every 10 levels, you can purchase an upgrade, which gives you a permanent" +
                    " boost for the duration of that run."}]},
    {name: "chatroom", icons: ["html5", "css", "bootstrap", "js", "socket"], type: "chat application", description: `
        I created a chat application that allows users to create and join rooms. Each user is uniquely identified by a random string of four hex digits. Users can tag each other using their identifier. Using socket.io, multiple computers on the same network can join the same rooms, and different rooms will not intefere with each other.
    `, images: [{src: chatroom1, caption: "The in-room interface of chatroom."}], link: "https://github.com/danlliu/chatroom"},
    {name: "chem illustrated", icons: ["html5", "css", "bootstrap"], type: "illustrated chemistry textbook", description: `
        Together with fellow computer science/chemistry major Abigail Fox, I started working on a free-to-use, online, and illustrated chemistry textbook, with a content level suitable for those interested in learning chemistry but not wanting to get into the fine details.
    `},
    {name: "beep boop", icons: ["html5", "css", "bootstrap", "js"], type: "programming language", description: `
        This is the first programming language I designed, and it was the start of a series of programming languages all based on ideas from friends and group chats. beep boop was inspired by the esoteric language "chicken". In beep boop, there are two keywords: beep and boop. Using these, along with a stack and two registers, it's possible to write programs such as Hello World, Fibonacci, and a recursive factorial algorithm.
    `, link: "https://danlliu.github.io/beepboop"},
    {name: "shift", icons: ["html5", "css", "bootstrap", "js"], type: "programming language", description: `
        Second of four in the programming languages series of projects, shift is a return to a more traditional syntax. Using only characters that can be accessed when the Shift key is held down on a U.S. layout keyboard, and taking inspiration from Bash syntax, shift provides 26 registers and 4096 words of memory for the program. Although stack frames are a bit trickier to work with, the readability is very much improved over beep boop.
    `, link: `https://danlliu.github.io/shift/`},
    {name: "this is all made up", icons: ["html5", "css", "bootstrap", "js"], type: "programming language", description: `
        The third programming language, "this is all made up" combines elements of assembly and two-dimensional languages such as Befunge to create one of the strangest and most challenging programming languages. The interface may seem overwhelming, but is almost essential in debugging programs. "this is all made up" was made to be a braintwister, and even a simple operation as addition can take nearly 30 lines of code and multiple hours of planning to implement correctly.
    `, link: "https://danlliu.github.io/thisisallmadeup"},
    {name: "creative writing", icons: ["html5", "css", "bootstrap", "js"], type: "programming language", description: `
        The most recent programming language design project, creative writing uses keywords chosen from the most common English words. It takes inspiration from the concept of polymorphic code, where the same program can be called in multiple different languages without modification. The choice of keywords allows creative writing programs to be disguised as other programming languages, notes, or short stories. Words with extremely high frequencies were also avoided to make it easier for programmers to develop their program in their format of choice. This is also the first language where the documentation can be found on the same page as the program input, thus removing the need for new programmers to flip between tabs to check instructions.
    `, link: "https://danlliu.github.io/creativewriting"},
    {name: "LC2K01", icons: ["html5", "css", "bootstrap", "js"], type: "assembly language simulator", description: `
        Learning assembly language is almost a rite of passage for programmers. You no longer have the comforts of the compiler and programming language managing some aspects of memory for you, but instead you have full control over the contents of memory. The number of variables that can be quickly accessed is limited by your registers. I wanted to create a simulator for those learning assembly to try out short segments without worrying about setting up an entire program. I chose to use the LEGv8 ISA, which is a subset of the ARMv8 ISA. To make writing assembly a bit simpler, I also included preprocessor directives such as %, FILL, and ALIGN, as well as a HLT instruction.
    `, link: "https://danlliu.github.io/lc2k01"},
    {name: "Maze Maker", icons: ["html5", "css", "js"], type: "maze generation program", description: `
        One of my earliest HTML projects, I implemented the Aldous-Broder algorithm to randomly generate mazes of an arbitrary size. The mazes are displayed using HTML canvas. Due to the algorithm used to generate the maze, every cell is reachable from the beginning, and there is a unique solution from beginning to end.
    `, link: "https://danlliu.github.io/Maze-Maker/"}
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
                return (<div className={"card-wide"} style={{height: 384, width: "auto", overflowY: "auto"}}>
                    <h3>{project_list[s].name}</h3>
                    {project_list[s].description && (() => {
                        if (project_list[s].name === "chem illustrated") {
                            let des = project_list[s].description;
                            let spl = des.split("Abigail Fox");
                            return <p>{spl[0]}<span className={"sneaky"} onClick={() => (document.getElementById("jinx").classList.add("found"))}>Abigail Fox</span>{spl[1]}</p>
                        } else {
                            return project_list[s].description.split("\n").map((text, idx) => <p tag={idx}>{text}</p>);
                        }
                    })()}
                    {project_list[s].images && (<div><h4>image gallery</h4>
                        <div className={"flexbox"} style={{maxHeight: "80%"}}>
                            {project_list[s].images.map((x, i) => {
                                return (<div className={"card"} style={{maxWidth: 384}} key={i}>
                                        <img src={x.src} alt={s.caption} key={i}
                                             style={{width: 384, marginBottom: 0}}/>
                                        <p style={{marginTop: 0}}>{x.caption}</p>
                                </div>);
                                })
                            }
                        </div>
                    </div>)}
                    {project_list[s].link && <h4>You can find {project_list[s].name} at <a className={"nonexpanding"} target={"_blank"} href={project_list[s].link}>{project_list[s].link}</a></h4>}
                </div>)
            })(this.state.selected)}
        </div>);
    }

}

export default PersonalProjects;
