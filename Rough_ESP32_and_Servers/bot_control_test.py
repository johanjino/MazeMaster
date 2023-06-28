from flask import Flask, request, jsonify
import sys

app = Flask(__name__)

@app.route('/process', methods=['POST'])
def process():
    data = request.get_json()

    processed_data = process_data(data)

    response = processed_data


    print(processed_data, file=sys.stderr)

    return jsonify(response)



def process_data(data):        
    print("Data recieved: {}".format(data), file=sys.stderr)
    processed_data = int(input("Enter Direction:\n1) Forward\n2) Right\n3) Left\n4) Backward\n"))
    return processed_data

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080)