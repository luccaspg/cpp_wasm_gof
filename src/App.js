import React from 'react';
import logo from './logo.svg';
import './App.css';
import Cell from './components/Cell';

function App() {
  const [size, setSize] = React.useState({
    height: 60,
    width: 120,
    hText: '60',
    wText: '120'
  });
  const [speed, setSpeed] = React.useState(500);

  const [grid, setGrid] = React.useState(new Array(size.height * size.width).fill(false));

  const handleChangeGrid = (newValue) => {
    setGrid(newValue);
  }

  const handleChangeSpeed = (event) => {
    setSpeed(parseInt(event.target.value));
  }

  const handleChangeHeight = (event) => {
    setSize({...size, ['height']: parseInt(event.target.value), ['hText']: event.target.value});
  }

  const handleChangeWidth = (event) => {
    setSize({...size, ['width']: parseInt(event.target.value), ['wText']: event.target.value});
  }
  let c_universe;

  let universe = [];
  for (let i = 0; i < size.height; i++) {
    universe.push(<Row width={size.width} height={i} grid={grid} setGrid={handleChangeGrid} />);
  }
  
  console.log(window.Module);
  const play = () => {
    c_universe = new window.Module.Universe(size.width, size.height);
    console.log(c_universe);
    window.Module._myFunction();
    for (let i = 0; i < size.width; i++) {
      for (let j = 0; j < size.height; j++) {
        if (grid[size.height * j + i]) {
          c_universe.setCell(j, i);
        }
      }
    }
    let k = 0;
    setInterval(() => {
      c_universe.setNextState();
      c_universe.advanceState();
      let newState = [];
      for (let i = 0; i < size.width; i++) {
        for (let j = 0; j < size.height; j++) {
          newState.push(c_universe.getIndex(j, i));
        }
      }
      setGrid(newState);
      console.log('next state');
    }, speed );
  }
  

  return (
    <div className="App">
      <div>
        <input value={size.hText} onChange={handleChangeHeight} ></input>
        x
        <input value={size.wText} onChange={handleChangeWidth}></input>
        Delay in MS:
        <input value={speed} onChange={handleChangeSpeed}></input>
        <button onClick={play}>PLAY!</button>
      </div>
      <div id='row' >
      </div>
      {universe}
    </div>
  );
}

function Row(props) {
  const {width, height, grid, setGrid} = props; //120, 0
  let row = [];
  for (let i = 0; i < width; i++) {
    row.push(<Cell index={i + height * width} grid={grid} setGrid={setGrid} />)
  }
  return (
    <div style={{display:'flex'}}>
      {row}
    </div>
  )
}

export default App;
