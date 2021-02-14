import React from 'react';

import cpp from './cpp.svg';
import clang from './clang.svg';

let courses = [
    {course: "EECS 280", title: "Programming and Introductory Data Structures", projects: [
            {name: "Euchre", description: "Implemented a functioning game of Euchre, where the user can choose to" +
                    " play with three other players or AIs. The settings for each game can be set using command line" +
                    " arguments."},
            {name: "Web Server", description: "Implemented a REST API backend for an office hours queue using C++," +
                    " and implemented a linked list to serve as the primary data structure for the queue."},
            {name: "Machine Learning", description: "Implemented the functionality of a binary search tree, and used" +
                    " std::map to create a Naive Bayes machine learning algorithm for classifying posts from the" +
                    " class Q&A forum into different categories."}
        ], language: "cpp"},
    {course: "EECS 281", title: "Data Structures and Algorithms", projects: [
            {name: "Puzzle", description: "Used DFS and BFS algorithms to solve a puzzle-style game, where walking" +
                    " on certain tiles opens up or closes other paths."},
            {name: "SillyQL", description: "Used the functionality of hash maps to implement a subset of SQL" +
                    " instructions, including the database."},
            {name: "Drones", description: "Implemented Prim's algorithm for minimum spanning trees and a traveling" +
                    " salesperson heuristic-based approximation and branch and bound algorithm to find the" +
                    " minimum-cost tour of all points."}
        ], language: "cpp"},
    {course: "EECS 370", title: "Introduction to Computer Organization", projects: [
            {name: "Assembler/Linker", description: "Used C to simulate the creation of object files from assembly" +
                    " code and the subsequent linking to form a final machine code executable."},
            {name: "Combinatorics", description: "Used a simple ISA (LC2K) to implement a recursive algorithm to" +
                    " compute binomial coefficients. The algorithm includes functionality for creating and removing stack" +
                    " frames, and uses callee-saved registers."},
            {name: "Cache Simulator", description: "Used C to simulate the execution of a LC2K processor which used" +
                    " a cache. The simulator supports direct-mapped, set-associative, and fully associative caches" +
                    " of various sizes, and indicates each transfer of memory between main memory, the cache, and" +
                    " the processor."}
        ], language: "c"},
    {course: "EECS 482", title: "Introduction to Operating Systems", projects: [
            {name: "Disk Scheduler", description: "Used the functionality of threads, mutexes, and condition" +
                    " variables to simulate a disk access scheduler, where requests for tracks come in from multiple" +
                    " threads and are serviced based on the shortest seek time."},
            {name: "Thread Library", description: "Implemented a thread library, including thread functionality," +
                    " mutexes, condition variables, and handling of multiple threads on one CPU core."}
        ], language: "cpp"}
];

class Coursework extends React.Component {

    render() {
        return (<div className={"flexbox"}>
            {courses.map((x, i) => (<div className={"card-3"} key={i}>
                <div style={{float: "left"}}>
                    <h3 style={{marginBottom: 0}}>{x.course}</h3>
                    <h4>{x.title}</h4>
                </div>
                <img src={x.language === "cpp" ? cpp : clang} height={40} width={40} alt={x.language === "cpp" ? "C++" : "C"}
                     title={x.language === "cpp" ? "C++" : "C"} style={{float: "right"}}/>
                {x.projects && (<details style={{clear: "both"}}>
                    <summary>Course Projects</summary>
                    {x.projects.map((p, j) => <p className={"project"} key={j}><b>{p.name}</b>: {p.description}</p>)}
                </details>)}
            </div>))}
        </div>)
    }

}

export default Coursework;
