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

  const [botPosition, setBotPosition] = useState(initialPosition);
  const [visitedPositions, setVisitedPositions] = useState([]);
  const [visitedNodes, setVisitedNodes] = useState([]);
  const [messages, setMessages] = useState([]); // State to store the received messages

  useEffect(() => {
    socket.on('message', (message) => {
      setMessages((prevMessages) => [...prevMessages, message]); // Update the messages state with received message
    });

    return () => {
      socket.disconnect(); // Disconnect the socket when the component is unmounted
    };
  }, []);

  useEffect(() => {
    const handleKeyDown = (event) => {
      const input = event.key;

      switch (input) {
        case 'ArrowUp':
          moveBot('forward');
          break;
        case 'ArrowDown':
          moveBot('backward');
          break;
        case 'ArrowLeft':
          moveBot('left');
          break;
        case 'ArrowRight':
          moveBot('right');
          break;
        case 's':
          setVisitedNodes((prevNodes) => [...prevNodes, botPosition]);
          break;
        default:
          break;
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
          setBotPosition((prevPosition) => ({ ...prevPosition, y: prevPosition.y - 1 }));
        }
        break;
      case 'backward':
        if (botPosition.y < gridSize.y) {
          setBotPosition((prevPosition) => ({ ...prevPosition, y: prevPosition.y + 1 }));
        }
        break;
      case 'left':
        if (botPosition.x > 1) {
          setBotPosition((prevPosition) => ({ ...prevPosition, x: prevPosition.x - 1 }));
        }
        break;
      case 'right':
        if (botPosition.x < gridSize.x) {
          setBotPosition((prevPosition) => ({ ...prevPosition, x: prevPosition.x + 1 }));
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
            style={{ gridRowStart: node.y, gridColumnStart: node.x, transform: 'translate(-35%, -35%)' }}
          />
        ))}
        {messages.map((message, index) => (
          <div key={index} className="message">
            {message}
          </div>
        ))}
      </div>
      <div className="controls">{/* Remove the button elements */}</div>
    </div>
  );
};

export default GridMap;



