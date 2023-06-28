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
    # for i in range(len(data[0])):
    #     if i==0:
    #         print("Area of Red: {}".format(data[0][i]), file=sys.stderr)
    #     if i==1:
    #         print("Area of Yellow: {}".format(data[0][i]), file=sys.stderr)
    #     if i==2:
    #         print("Area of Blue: {}".format(data[0][i]), file=sys.stderr)
    #     if i==3:
    #         print("Offset to lane: {}".format(data[0][i]), file=sys.stderr)
    #     if i==4 and data[0][i]==1:
    #         print("Right Turn Found", file=sys.stderr)
    #     if i==5 and data[0][i]==1:
    #         print("Left Turn Found", file=sys.stderr)
    #     if i==6 and data[0][i]==1:
    #         print("End of road ahead!!", file=sys.stderr)
    #     if i==6 and data[0][i]==0:
    #         print("Forward road available", file=sys.stderr)
        
    print("Data recieved: {}".format(data), file=sys.stderr)
    processed_data = int(input("Enter Direction:\n1) Forward\n2) Right\n3) Left\n4) Backward\n"))
    return processed_data

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8000)