import React from "../node_modules/react";

let education = [
    {school: "University of Michigan", degree: "Dual Degree, B.S.Chem + B.S.E. Computer Science", start: "Sep. 2019"},
    {school: "The University of Toledo", degree: "Dual Enrollment", start: "May 2016", end: "May 2019"}
];

class Education extends React.Component {
    render() {
        return (<div className={"flexbox"}>
            {education.map(x => <div className={"card"}>
                <h3>{x.school}</h3>
                <p>{x.degree}</p>
                <p>{x.start} – {x.end ? x.end : "present"}</p>
            </div>)}
        </div>)
    }
}

export default Education;
