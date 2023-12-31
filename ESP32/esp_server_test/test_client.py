from flask import Flask, request, jsonify
import sys

app = Flask(__name__)

@app.route('/process', methods=['POST'])
def process():
    data = request.get_json()
    
    processed_data = process_data(data)

    response = {
        'status': 'success',
        'message': 'Data processed successfully',
        'result': processed_data
    }

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