import React from 'react';

let work_experience = [
    {employer1: "University of Michigan", employer2: "College of Engineering", role: "Instructional Aide",
        subtitles: [
            "EECS281 (September - December 2020)",
            "EECS370 (January 2021 - present)"
        ],
        description: [
            "Collaborated with the teaching staff of EECS281, a gateway algorithms course, and EECS370, a computer" +
            " organization course (both 600+ students).",
            "Assisted course instructors with grading exams, answering student questions on a class Q&A forum, and" +
            " helping answer questions during lectures.",
            "Led weekly discussion sections to reinforce student knowledge of course material, and conducted office" +
            " hours during the week to help students with conceptual questions or with class coding projects.",
            "Designed exam and homework questions to test student comprehension, and incorporated student feedback" +
            " into modifications to course logistics needed to navigate the COVID-19 pandemic.",
            "Helped make modifications to the course website to improve ease of access to course resources and general usability."
        ]},
    {employer1: "University of Michigan", employer2: "Comprehensive Studies Program", role: "Mathematics Tutor",
        subtitles: [
            "September 2019 - present"
        ],
        description: [
        "did more stuff"
        ]},
    {employer1: "University of Michigan", employer2: "Department of Chemistry", role: "Student Researcher",
        subtitles: [
            "September 2019 - present"
        ],
        description: [
        "yay research"
        ]}
];

class WorkExperience extends React.Component {
    render() {
        return (<div className={"flexbox"}>
            {work_experience.map((x, i) => (<div className={"card-3"} key={i}>
                <h3 style={{marginBottom: 0}}>{x.employer1}</h3>
                <h3 style={{marginBottom: 0}}>{x.employer2}</h3>
                <h4 style={{marginBottom: 16}}>{x.role}</h4>
                <div style={{height: "3em"}}>{x.subtitles.map((e) => <p style={{margin: "auto 0"}}>{e}</p>)}</div>
                <details>
                    <summary>Responsibilities:</summary>
                    <ul>
                        {x.description.map((y, j) => <li key={j}>{y}</li>)}
                    </ul>
                </details>
            </div>))}
            <div className={"card-3"}>
                <h3>You could be here!</h3>
                <p>Contact me at <a href={"mailto:danlliu@umich.edu"}>danlliu@umich.edu</a></p>
            </div>
        </div>);
    }
}

export default WorkExperience;
