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