import React from 'react';

let work_experience = [
    {employer1: "University of Michigan", employer2: "College of Engineering", role: "Instructional Aide", description: [
        "did stuff i guess"
        ]},
    {employer1: "University of Michigan", employer2: "Comprehensive Studies Program", role: "Mathematics Tutor", description: [
        "did more stuff"
        ]},
    {employer1: "University of Michigan", employer2: "Department of Chemistry", role: "Student Researcher", description: [
        "yay research"
        ]}
];

class WorkExperience extends React.Component {
    render() {
        return (<div className={"flexbox"}>
            {work_experience.map((x, i) => (<div className={"card-4"} key={i}>
                <h3 style={{marginBottom: 0}}>{x.employer1}</h3>
                <h3 style={{marginBottom: 0}}>{x.employer2}</h3>
                <h4>{x.role}</h4>
                <ul>
                    {x.description.map((y, j) => <li key={j}>{y}</li>)}
                </ul>
            </div>))}
            <div className={"card-4"}>
                <h3>You could be here!</h3>
                <p>Contact me at <a href={"mailto:danlliu@umich.edu"}>danlliu@umich.edu</a></p>
            </div>
        </div>);
    }
}

export default WorkExperience;
