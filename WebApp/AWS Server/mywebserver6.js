const path_html = 'H:/EIE2_Projects/MazeMaster/Application-Server Tutorials/2 - Node.js on AWS/test_page3.html'
const path_program = 'H:/EIE2_Projects/MazeMaster/Application-Server Tutorials/2 - Node.js on AWS/primeOrNot.js'

var express = require('express');
var server = express();
server.get('/', function(req, res) {
 res.sendFile(path_html);
});
server.get('/primeOrNot.js', function(req, res) {
 res.sendFile(path_program);
});
console.log('Server is running on port 3000');
server.listen(3000,'0.0.0.0');