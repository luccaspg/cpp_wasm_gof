import React from 'react';

export default function Cell(props) {
    const {index, grid, setGrid} = props;
    // const index = indexX * grid.size + indexY;
    // const [isAlive, setIsAlive] = React.useState(false);
    const toggleAlive = () => {
        let ret = [];
        grid.map(a => {ret.push(a)});
        console.log(index);
        ret[index] = !grid[index];
        // console.log(ret);
        setGrid(ret);
    }
    return(
        <div style={{
            height: '12.5px',
            width: '12.5px',
            backgroundColor: grid[index] ? 'black' : 'white',
            border: '0.75px solid #000000',
        }}
        onClick={toggleAlive}
        ></div>
    );
}