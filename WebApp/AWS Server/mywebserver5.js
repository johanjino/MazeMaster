const html_path = 'H:/EIE2_Projects/MazeMaster/Application-Server Tutorials/2 - Node.js on AWS/test_page4.html'; 

var express = require('express');
var server = express();
server.get('/', function(req, res) {
 res.sendFile(html_path);
});
console.log('Server is running on port 3000');
server.listen(3000,'0.0.0.0');