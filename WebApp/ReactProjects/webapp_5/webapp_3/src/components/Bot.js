import React from 'react';
import '../styles/Bot.css';

const Bot = ({ position }) => {
  return (
    <div
      className="bot"
      style={{
        gridRowStart: position.y,
        gridColumnStart: position.x,
        transform: 'translate(-35%, -35%)', // Adjust position to center the dot
      }}
    ></div>
  );
};

export default Bot;
