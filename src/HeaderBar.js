import React from 'react';

let links = [
    {section: "about-me", text: "about me"},
    {section: "work-exp", text: "work experience"},
    {section: "more-hre", text: "some really long text"},
    {section: "more-hre", text: "you must construct additional pylons"},
    {section: "more-hre", text: "run"}
];

class HeaderBar extends React.Component {
    render() {
        return (<div className="header-bar">
            <a href="#" className={"textLink"} style={{marginLeft: "2%"}}>Daniel Liu</a>
            {links.map(x => <a href={"#" + x.section}>{x.text}</a>)}
        </div>);
    }
}

export default HeaderBar;
