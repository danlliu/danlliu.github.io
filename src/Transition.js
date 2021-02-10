import React from 'react';

class Transition extends React.Component {

    render() {
        return <div className={"transition"}
                    style={{backgroundImage: `linear-gradient(${this.props.top}, ${this.props.bottom})`}}> </div>;
    }

}

export default Transition;
