import React, { useState, useEffect } from 'react';
import Bot from './Bot';
import '../styles/GridMap.css';

const GridMap = () => {
  const gridSize = { x: 600, y: 432 };
  const initialPosition = {
    x: Math.ceil(gridSize.x / 2),
    y: Math.ceil(gridSize.y / 2),
  };

  const [botPosition, setBotPosition] = useState(initialPosition);
  const [visitedPositions, setVisitedPositions] = useState([]);
  const [visitedNodes, setVisitedNodes] = useState([]);
  
  useEffect(() => {
    const handleKeyDown = (event) => {
      if (event.key === 's') {
        setVisitedNodes((prevNodes) => [...prevNodes, botPosition]);
      }
    };

    window.addEventListener('keydown', handleKeyDown);
    return () => {
      window.removeEventListener('keydown', handleKeyDown);
    };
  }, [botPosition]);

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
    setVisitedPositions((prevPositions) => [...prevPositions, botPosition]);
  };

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
        {visitedNodes.map((node, index) => (
          <div
            key={index}
            className="visitedNode"
            style={{ gridRowStart: node.y, gridColumnStart: node.x }}
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