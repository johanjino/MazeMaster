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
    print("Recieved: {}".format(data), file=sys.stderr)
    return 1

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080) 



# R_area, Y_area, B_area, offset, R_turn, L_turn, F_turn