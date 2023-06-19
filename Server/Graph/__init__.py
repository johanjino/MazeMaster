import numpy as np
from Graph.graph_class import Graph
import sys

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
    print(visited_edges, file=sys.stderr)
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
    if sum(list1)==0 or sum(list2)==0:
        return 0
    distance = weighted_euclidean_distance(list1, list2, weights)
    tuneable_parameter = 30
    confidence = np.exp(((-distance)/tuneable_parameter)) * 100
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
                conf = calculate_confidence(image, property, [0.25,0.25,0.25,0.25])
                top_4 = calc_top_4(top_4, conf)

        final_conf = sum(top_4)/4
        print(final_conf, file=sys.stderr)
        if final_conf>best_conf:
            best_conf = final_conf
            best_match = node
    
    if best_conf<50:
        return -1
    return visited_nodes.index(best_match)

def check_finish():
    #ToDo
    """
    Function to run every loop to identify if finished mapping,
    Not complete how to implement. 
    Ideas: use determine direction, if no more direction left and no parent node present
    """
    
