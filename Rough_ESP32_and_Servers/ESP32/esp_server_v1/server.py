from flask import Flask, request, jsonify
import sys

req_count = 0

app = Flask(__name__)

@app.route('/process', methods=['POST'])
def process():
    global req_count
    data = request.get_json()
    
    processed_data = process_data(data)

    response = req_count
    req_count+=1

    print(processed_data, file=sys.stderr)
    return jsonify(response)

def process_data(data):
    if not type(data) == list:
        processed_data = None
        raise TypeError("Data not a list")
    else:
        processed_data = data
    return processed_data

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080)