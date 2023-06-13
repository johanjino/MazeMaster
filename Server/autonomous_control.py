import numpy as np

# Graph representing the map
class Graph:
    def __init__(self, id, property):
        self.id = id
        self.property = property  # Node property (image data of node)
        self.edge_list = []  # Edges list (angles of each edge)
        self.edge_map = {}  # Edge mappings (maps where each angle leads to)

    # Function to add an edge to the graph
    def add_edges(self, edge_list):
        self.edge_list = edge_list

    # Function to map each edge to node
    def update_map(self, angle, id):
        self.edge_map[angle] = id


def find_angle(angle, node: Graph):
    #ToDo
    """
    Use Error Probabilty and Approximations to match a given 
    angle to the angle stored within node class
    """
    all_angles = node.edge_list
    nearest_angle = None
    min_difference = float('inf')

    for i in all_angles:
        difference = abs(angle - i)
        if difference < min_difference:
            min_difference = difference
            nearest_angle = i
    return nearest_angle

def determine_direction(node: Graph, stack: list, visited: list):
    #ToDo
    """
    Given current node, path stack and visited nodes, determine
    the path (i.e. angle) to be taken from current node
    """
    edges = node.edge_list
    visited_edges = node.edge_map.keys()

    # if node in visited and node != visited[stack[-1][0]] : This case will not be entered in this function

    angle = -1

    for i in edges:
        if i not in visited_edges:
            angle = i
            break
    else:
        try:
            for key, val in node.edge_map.items():
                if val == stack[-1][0]:
                    angle = key
        except KeyError:
            raise Exception("Path Stack Empty")
    
    if angle == -1:
        raise Exception("Direction calculation error")
    return angle


def weighted_euclidean_distance(list1, list2, weights):
    if len(list1) != len(list2) or len(list1) != len(weights):
        raise ValueError("Input lists and weights must have the same length")

    squared_distances = [(list1[i] - list2[i])**2 * weights[i] for i in range(len(list1))]
    return np.sqrt(sum(squared_distances))

def calculate_confidence(list1, list2, weights):
    distance = weighted_euclidean_distance(list1, list2, weights)
    max_distance = np.sqrt(sum([(w * max(list1[i], list2[i]))**2 for i, w in enumerate(weights)]))
    confidence = 100 - (distance / max_distance) * 100
    return confidence

def calc_top_4(top_4, value):
    if len(top_4) < 4:
            top_4.append(value)
            top_4.sort(reverse=True)
    else:
        for i, top_value in enumerate(top_4):
            if value > top_value:
                top_4.insert(i, value)
                top_4.pop()
                break

    return top_4

def check_node(data, visited_nodes: list[Graph]):
    #ToDo
    """
    Using data, return id of node if present in visited_nodes,
    if not return -1
    """
    best_conf = 0
    best_match = None
    
    for node in visited_nodes:
        top_4 = []
        for property in node.property:
            for image in data:
                conf = calculate_confidence(image, property, [0.5,0.5,0.5,0.5])
                top_4 = calc_top_4(top_4, conf)

        final_conf = sum(top_4)/4
        if final_conf>best_conf:
            best_conf = final_conf
            best_match = node
    
    if best_conf<70:
        return -1
    return visited_nodes.index(best_match)

def check_finish():
    #ToDo
    """
    Function to run every loop to identify if finished mapping,
    Not complete how to implement. 
    Ideas: use determine direction, if no more direction left and no parent node present
    """
    return

def recieve_data():
    # temporary needs to be updated
    data = None
    return data

def send(data):
    # temporary needs to be updated
    return

recieve = True #when data recieved

if __name__ == '__main__':

    #initilize start node
    count = 0
    data = recieve_data()
    node = Graph(count, data["property"])
    node.add_edges(data["edges"])
    visited_nodes = []
    path_stack = []
    direction = determine_direction(node, path_stack, visited_nodes)
    send(direction)
    visited_nodes = [node]
    path_stack = [(count,direction)]

    while (recieve):
        #at each node
        data = recieve_data()
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
            send(direction)
            
            #Update stack and visited nodes
            visited_nodes.append(node)
            path_stack.append((count,direction))

        else:
            
            #Get Node
            node = visited_nodes[id]

            if id == path_stack[-1][0]:
                #Rover on way back
                path_stack.pop()

                #Find direction to take
                direction = determine_direction(node, path_stack, visited_nodes)
                send(direction)

                #update stack
                path_stack.append((id,direction))
            
            else:
                #Update map
                visited_nodes[path_stack[-1][0]].update_map(path_stack[-1][1],id)
                angle = find_angle(abs(180-path_stack[-1][1]), node)

                #Find direction to take
                direction = angle   #need to go back since already visited
                send(direction)
        
        check_finish()

        


            
            

