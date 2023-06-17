import React, { useState, useEffect } from 'react';
import Bot from './Bot';
import '../styles/GridMap.css';
import io from 'socket.io-client'; // Import the socket.io-client library

const socket = io('http://localhost:5000'); // Replace with your server URL

const GridMap = () => {
  const gridSize = { x: 600, y: 432 };
  const initialPosition = {
    x: Math.ceil(gridSize.x / 2),
    y: Math.ceil(gridSize.y / 2),
  };

  const [visitedPositions, setVisitedPositions] = useState([initialPosition]);
  const [visitedNodes, setVisitedNodes] = useState([]);
  const currentPosition = visitedPositions[visitedPositions.length - 1] 


  useEffect(() => {
    console.log("Setting up socket")
    const handleNewMessage = (message) => {
      console.log(message)
        switch (message) {
        case '1':
          moveBot('forward');
          break;
        case '2':
          moveBot('backward');
          break;
        case '3':
          moveBot('left');
          break;
        case '4':
          moveBot('right');
          break;
        case 's':
          setVisitedNodes((prevNodes) => [...prevNodes, currentPosition]);
          break;
        default:
          break;
      }
    }

    socket.on('message', handleNewMessage);

    return () => {
      socket.off('turn socketg off', handleNewMessage); // Disconnect the socket when the component is unmounted
    };
  }, []);

  // useEffect(() => {
  //   const handleKeyDown = (event) => {
  //     const input = event.key;

  //     switch (input) {
  //       case 'ArrowUp':
  //         moveBot('forward');
  //         break;
  //       case 'ArrowDown':
  //         moveBot('backward');
  //         break;
  //       case 'ArrowLeft':
  //         moveBot('left');
  //         break;
  //       case 'ArrowRight':
  //         moveBot('right');
  //         break;
  //       case 's':
  //         setVisitedNodes((prevNodes) => [...prevNodes, currentPosition]);
  //         break;
  //       default:
  //         break;
  //     }
  //   };

  //   window.addEventListener('keydown', handleKeyDown);
  //   return () => {
  //     window.removeEventListener('keydown', handleKeyDown);
  //   };
  // }, []);

  const moveBot = (direction) => {
    setVisitedPositions((prevPositions) => {
      const previousPosition = prevPositions[prevPositions.length - 1]
      let newPosition
      switch (direction) {
          case 'forward':
            if (previousPosition.y > 1) {
              newPosition = { ...previousPosition, y: previousPosition.y - 1 }
            }
            break;
          case 'backward':
            if (previousPosition.y < gridSize.y) {
              newPosition = { ...previousPosition, y: previousPosition.y + 1 }
            }
            break;
          case 'left':
            if (previousPosition.x > 1) {
              newPosition = { ...previousPosition, x: previousPosition.x - 1 }
            }
            break;
          case 'right':
            if (previousPosition.x < gridSize.x) {
              newPosition = { ...previousPosition, x: previousPosition.x + 1 }
            }
            break;
          default:
            newPosition = previousPosition
            break;
        }
      return [...prevPositions, newPosition]
    });
  };

  return (
    <div className="gridMap">
      <div className="grid">
        <Bot position={currentPosition} />
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
            style={{ gridRowStart: node.y, gridColumnStart: node.x, transform: 'translate(-35%, -35%)' }}
          />
        ))}
      </div>
      <div className="controls">{/* Remove the button elements */}</div>
    </div>
  );
};

export default GridMap;

