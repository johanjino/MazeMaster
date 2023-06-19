from flask import Flask, request, jsonify
import sys
import json
from Graph import *

start = True
count = 0
visited_nodes = []
path_stack = []


app = Flask(__name__)

@app.route('/process', methods=['POST'])
def process():
    input_data = json.loads(request.get_json())['data']

    data = {'property': input_data, 'edges' : [input_data[i][3] for i in range(4) if sum(input_data[i])!=0]}

    print(data, file=sys.stderr)

    # Process the data as needed
    processed_data = process_data(data)

    # Create the response
    response = {
        'status': 'success',
        'message': 'Data processed successfully',
        'direction': processed_data
    }

    print(processed_data, file=sys.stderr)
    
    return jsonify(response)


# Function to process the data
def process_data(data):
    # Perform processing on the received data
    output = "Why"
    global start
    global count
    global visited_nodes
    global path_stack

    if start:
        start = False
        print("Found Starting Node", file=sys.stderr)
        #initilize start node
        node = Graph(count, data["property"])
        node.add_edges(data["edges"])
        direction = determine_direction(node, path_stack, visited_nodes)
        visited_nodes.append(node)
        path_stack.append((count,direction))

        output = direction

    else:

        #at each node
        id = check_node(data["property"], visited_nodes)
        
        if id == -1:
            print("Found New Node", file=sys.stderr)
            count += 1

            #Create Node
            node = Graph(count, data["property"])
            node.add_edges(data["edges"])

            #Update Paths
            visited_nodes[path_stack[-1][0]].update_map(path_stack[-1][1],count)
            angle = find_angle(abs(180-path_stack[-1][1]), node)
            node.update_map(angle, path_stack[-1][0])

            #Find direction to take
            direction = determine_direction(node, path_stack, visited_nodes)

            #Update stack and visited nodes
            visited_nodes.append(node)
            path_stack.append((count,direction))

            output = direction

        else:
            
            print("Found Visited Node with ID = {}".format(id), file=sys.stderr)
            #Get Node
            node = visited_nodes[id]

            if id == path_stack[-1][0]:
                #Rover on way back
                print("On way back", file=sys.stderr)
                path_stack.pop()

                #Find direction to take
                direction = determine_direction(node, path_stack, visited_nodes)

                #update stack
                path_stack.append((id,direction))

                output = direction
            
            else:
                #Update map
                print("Loop found", file=sys.stderr)
                visited_nodes[path_stack[-1][0]].update_map(path_stack[-1][1],id)
                angle = find_angle(abs(180-path_stack[-1][1]), node)
                print("Reached here with angle = {}".format(angle), file=sys.stderr)
                #Find direction to take
                direction = angle   #need to go back since already visited
                
                output = direction
        
    check_finish()
    return output
    

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080)
    
