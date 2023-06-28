from flask_socketio import SocketIO
from flask import Flask, render_template, request
from flask_cors import CORS

app = Flask(__name__)
CORS(app)
socketio = SocketIO(app, cors_allowed_origins='*')

@socketio.on('connect')
def handle_connect():
    print("Connected")
    socketio.emit("Connected", "Connected")

@socketio.on('start')
def handle_stream_start():

    for i in range(100):

        message = input("Enter map direction: ")

        socketio.emit('message', message)
        socketio.sleep(0.25)  

if __name__ == '__main__':
    socketio.run(app)
