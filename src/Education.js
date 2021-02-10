import React from "react";

let education = [
    {school: "University of Michigan", degree: "Dual Degree, B.S.Chem + B.S.E. Computer Science", start: "Sep. 2019", gpa: "3.9 / 4.0"},
    {school: "The University of Toledo", degree: "Dual Enrollment", start: "May 2016", end: "May 2019"}
];

class Education extends React.Component {
    render() {
        return (<div className={"flexbox"}>
            {education.map((x, i) => <div className={"card-3"} key={i}>
                <h3>{x.school}</h3>
                <p>{x.degree}</p>
                <p>{x.start} – {x.end ? x.end : "present"}</p>
                {x.gpa && <p>Weighted GPA: <b>{x.gpa}</b></p>}
            </div>)}
        </div>)
    }
}

export default Education;
