from flask_socketio import SocketIO
from flask import Flask, render_template, request
from flask_cors import CORS

app = Flask(__name__)
CORS(app)
app.config['SECRET_KEY'] = 'your-secret-key'
socketio = SocketIO(app, cors_allowed_origins='*')

@socketio.on('connect')
def handle_connect():
    print("Connected")
    socketio.emit("Connected", "Connected")

    #socketio.server.disconnect(request.sid)

@socketio.on('start')
def handle_stream_start():

    for i in range(100):

        message = input("Enter map direction: ")

        socketio.emit('message', message)
        socketio.sleep(0.25)  # Wait for 1 second before sending the next message

if __name__ == '__main__':
    socketio.run(app)

#/usr/local/opt/python@3.10/bin/python3.10 /Users/anadimoska/Desktop/mazemaster/python_server/server_app8.py
