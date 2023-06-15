from flask import Flask, request, jsonify
import sys
from Graph import *

count = 0
visited_nodes = []
path_stack = []


app = Flask(__name__)

@app.route('/process', methods=['POST'])
def process():
    data = request.get_json()
    
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
    # Modify this function to process the data as needed in your application
    if not type(data) == list:
        raise TypeError("Data not a list")
    
    global count
    global visited_nodes
    global path_stack

    if count==0:
        #initilize start node
        node = Graph(count, data["property"])
        node.add_edges(data["edges"])
        direction = determine_direction(node, path_stack, visited_nodes)
        visited_nodes.append(node)
        path_stack.append((count,direction))

        output = direction

    else:

        #at each node
        id = check_node(data, visited_nodes)
        
        if id == -1:
            count += 1

            #Create Node
            node = Graph(count, data["property"])
            node.add_edges([data["edges"]])

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
            
            #Get Node
            node = visited_nodes[id]

            if id == path_stack[-1][0]:
                #Rover on way back
                path_stack.pop()

                #Find direction to take
                direction = determine_direction(node, path_stack, visited_nodes)

                #update stack
                path_stack.append((id,direction))

                output = direction
            
            else:
                #Update map
                visited_nodes[path_stack[-1][0]].update_map(path_stack[-1][1],id)
                angle = find_angle(abs(180-path_stack[-1][1]), node)

                #Find direction to take
                direction = angle   #need to go back since already visited
                
                output = direction
        
        check_finish()

        return output
    

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080)
    
