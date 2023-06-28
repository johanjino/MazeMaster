import requests
import json
import time
from flask import Flask

app = Flask(__name__)

def send_data():
    data = {
        'name': 'John Doe',
        'age': 30,
        'city': 'New York'
    }

    json_data = json.dumps(data)

    # Send the JSON data to the other server
    url = 'http://other-server-url.com:8080/endpoint'
    headers = {'Content-Type': 'application/json'}
    response = requests.post(url, data=json_data, headers=headers)

    if response.status_code == 200:
        print('JSON data sent successfully to the other server.')
    else:
        print('Error sending JSON data to the other server.')

@app.route('/')
def start_sending():
    # Start sending data every q seconds
    q = 5  # Change this to your desired interval in seconds
    while True:
        send_data()
        time.sleep(q)

if __name__ == '__main__':
    app.run()
