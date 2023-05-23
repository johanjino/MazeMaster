var http = require('http');
let htmlContent = `
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>MazeMaster Rover</title>

    <!-- Bootstrap CSS -->
    <link href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css" rel="stylesheet">

    <style>
        body {
            background-color: #f8f9fa;
        }
        .jumbotron {
            background-image: url('https://source.unsplash.com/1200x300/?maze,robot');
            background-size: cover;
            height: 300px;
        }
        .jumbotron .container {
            background-color: rgba(255, 255, 255, 0.7);
            padding: 20px;
        }
        .jumbotron h1 {
            color: black;
            font-weight: bold;
        }
        .jumbotron p {
            color: black;
        }
        .card {
            margin: 10px 0;
        }
    </style>
</head>

<body>
    <div class="jumbotron text-center">
        <div class="container">
            <h1 class="display-4">Welcome to the EEEBalanceBot Project!</h1>
            <p class="lead">Meet MazeMaster, our autonomous balancing rover.</p>
        </div>
    </div>

    <div class="container">
        <div class="card">
            <img src="https://source.unsplash.com/600x400/?maze" class="card-img-top" alt="Maze Image">
            <div class="card-body">
                <h5 class="card-title">The Maze Challenge</h5>
                <p class="card-text">Our MazeMaster rover is designed to travel through complex mazes, mapping its route as it goes.</p>
            </div>
        </div>

        <div class="card">
            <img src="https://source.unsplash.com/600x400/?robot" class="card-img-top" alt="Robot Image">
            <div class="card-body">
                <h5 class="card-title">MazeMaster Capabilities</h5>
                <p class="card-text">With advanced autonomous balancing and navigation abilities, MazeMaster is able to reach the endpoint of any maze.</p>
            </div>
        </div>

    </div>

    <!-- Bootstrap JS and dependencies -->
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js"></script>

</body>

</html>

`;
var server = http.createServer(function(req, res){
 res.writeHead(200, {'Content-Type':'text/html'})
 res.end(htmlContent);
});
console.log('Server is running on port 3000');
server.listen(3000,'0.0.0.0');