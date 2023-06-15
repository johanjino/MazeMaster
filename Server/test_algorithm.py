import requests
import json

# Set the URL of the server
url = "http://192.168.43.45:8080/process"

while True:
    # Get the list input from the user
    input_list = eval(input("Enter Data: \n"))

    # Create a dictionary payload with the list
    payload = {"data": input_list}

    # Convert the payload dictionary to JSON
    json_payload = json.dumps(payload)

    # Send a POST request to the server
    response = requests.post(url, data=json_payload)

    # Check the response status code
    if response.status_code == 200:
        # Get the response data
        response_data = response.json()
        print("Data sent successfully to the server!")

        # Print the received data
        print("Received data from the server:", response_data)
    else:
        print("Failed to send data to the server. Error:", response.status_code)
