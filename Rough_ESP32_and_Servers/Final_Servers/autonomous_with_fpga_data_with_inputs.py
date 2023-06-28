from flask import Flask, request, jsonify, render_template
from flask_socketio import SocketIO
from flask_cors import CORS
import sys

app = Flask(__name__)
CORS(app)
socketio = SocketIO(app, cors_allowed_origins='*')

curr_dir = "UP"


def decide_map_dir(processed_data):
    global curr_dir
    if (curr_dir == "UP"):
        if (processed_data == 1):
            return "1"
        elif (processed_data == 2):
            curr_dir = "RIGHT"
            return "2"
        elif (processed_data == 3):
            curr_dir = "LEFT"
            return "3"
        elif (processed_data == 4):
            curr_dir = "DOWN"
            return "4"
        
    elif(curr_dir == "DOWN"):
        if (processed_data == 1):
            return "4"
        elif (processed_data == 2):
            curr_dir = "LEFT"
            return "3"
        elif (processed_data == 3):
            curr_dir = "RIGHT"
            return "2"
        elif (processed_data == 4):
            curr_dir = "UP"
            return "1"
        
    elif(curr_dir == "RIGHT"):
        if (processed_data == 1):
            return "2"
        elif (processed_data == 2):
            curr_dir = "DOWN"
            return "4"
        elif (processed_data == 3):
            curr_dir = "UP"
            return "1"
        elif (processed_data == 4):
            curr_dir = "LEFT"
            return "3"
        
    elif(curr_dir == "LEFT"):
        if (processed_data == 1):
            return "3"
        elif (processed_data == 2):
            curr_dir = "UP"
            return "1"
        elif (processed_data == 3):
            curr_dir = "DOWN"
            return "4"
        elif (processed_data == 4):
            curr_dir = "RIGHT"
            return "2"

@socketio.on('connect')
def handle_connect():
    print("Connected")
    socketio.emit("Connected", "Connected")

@app.route('/process', methods=['POST'])
def process():
    data = request.get_json()
    response = process_data(data)
    return jsonify(response)

def process_data(data):
    print("Received: {}".format(data), file=sys.stderr)
    processed_data = int(data[7])
    if(processed_data == 2):
        socketio.emit('message', str(5))
    print("Direction: ", processed_data)
    dir_to_emit = decide_map_dir(processed_data)
    socketio.emit('message', str(dir_to_emit))
    
    input_value = int(input("Enter direction:\n2Right\n3Left\n"))
    return input_value

if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0', port=5000)