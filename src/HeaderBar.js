import React from 'react';

let links = [
    {section: "about-me", text: "about me"},
    {section: "work-exp", text: "work experience"},
    {section: "personal-projects", text: "personal projects"},
    {section: "more-hre", text: "you must construct additional pylons"}
];

class HeaderBar extends React.Component {
    render() {
        return (<div className="header-bar">
            <a href="#" className={"textLink"} style={{marginLeft: "2%"}}>daniel liu</a>
            {links.map((x, i) => <a key={i} href={"#" + x.section}>{x.text}</a>)}
        </div>);
    }
}

export default HeaderBar;
