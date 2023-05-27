import React from 'react';
import '../styles/Bot.css';

const Bot = ({ position }) => {
  return (
    <div 
      className="bot" 
      style={{ gridRowStart: position.y, gridColumnStart: position.x }}
    >
    </div>
  );
};

export default Bot;
