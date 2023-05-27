import React, { useState } from 'react';
import Bot from './Bot';
import '../styles/GridMap.css';

const GridMap = () => {
    const [botPosition, setBotPosition] = useState({ x: 150, y: 108 }); // initial position
    const [visitedPositions, setVisitedPositions] = useState([]);
    const gridSize = { x: 300, y: 216 };

  const moveBot = (direction) => {
    switch (direction) {
      case 'forward':
        if (botPosition.y > 1) {
          setBotPosition(prevPosition => ({ ...prevPosition, y: prevPosition.y - 1 }));
        }
        break;
      case 'backward':
        if (botPosition.y < gridSize.y) {
          setBotPosition(prevPosition => ({ ...prevPosition, y: prevPosition.y + 1 }));
        }
        break;
      case 'left':
        if (botPosition.x > 1) {
          setBotPosition(prevPosition => ({ ...prevPosition, x: prevPosition.x - 1 }));
        }
        break;
      case 'right':
        if (botPosition.x < gridSize.x) {
          setBotPosition(prevPosition => ({ ...prevPosition, x: prevPosition.x + 1 }));
        }
        break;
      default:
        break;
    }
    setVisitedPositions(prevPositions => [...prevPositions, botPosition]);
  }
  
  return (
    <div className="gridMap">
      <div className="grid">
        <Bot position={botPosition} />
        {visitedPositions.map((position, index) => (
          <div
            key={index}
            className="visitedCell"
            style={{ gridRowStart: position.y, gridColumnStart: position.x }}
          />
        ))}
      </div>
      <div className="controls">
      <button onClick={() => moveBot('forward')}>Move Forward</button>
      <button onClick={() => moveBot('backward')}>Move Backward</button>
      <button onClick={() => moveBot('left')}>Turn Left</button>
      <button onClick={() => moveBot('right')}>Turn Right</button>
      </div>
    </div>
  );
};

export default GridMap;

