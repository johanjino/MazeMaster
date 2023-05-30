const express = require('express');
const app = express();
const server = require('http').createServer(app);
const WebSocket = require('ws');

const wss = new WebSocket.Server({ server });

let botPosition = { x: 150, y: 108 }; // Initial bot position

wss.on('connection', (ws) => {
  // Send the initial bot position to the client
  ws.send(JSON.stringify(botPosition));

  // Listen for messages from the client
  ws.on('message', (message) => {
    const { direction } = JSON.parse(message);
    moveBot(direction); // Call the moveBot function based on the received direction
    wss.clients.forEach((client) => {
      if (client.readyState === WebSocket.OPEN) {
        client.send(JSON.stringify(botPosition)); // Send the updated bot position to all clients
      }
    });
  });
});

function moveBot(direction) {
  // Update the bot position based on the received direction
  switch (direction) {
    case 'forward':
      if (botPosition.y > 1) {
        botPosition.y -= 1;
      }
      break;
    case 'backward':
      if (botPosition.y < 216) {
        botPosition.y += 1;
      }
      break;
    case 'left':
      if (botPosition.x > 1) {
        botPosition.x -= 1;
      }
      break;
    case 'right':
      if (botPosition.x < 300) {
        botPosition.x += 1;
      }
      break;
    default:
      break;
  }
}

server.listen(8080, () => {
  console.log('WebSocket server is running on port 8080.');
});
