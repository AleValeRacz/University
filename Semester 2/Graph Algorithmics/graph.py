import copy
import heapq


class Graph:
    def __init__(self, n=0):
        """
        Creates an object of the class Graph, initialises the 3 dictionaries for the inbound, outbound edges and the cost of the edges
        :param n: nr of vertices, the default is 0
        """
        self.__nr_vertices = n
        self.__nr_edges = 0
        self.__in_edges = {}
        self.__out_edges = {}
        self.__costs = {}
        for i in range(self.__nr_vertices):
            self.__in_edges[i] = []
            self.__out_edges[i] = []



    def get_all_vertices(self):
        """
        Parses the set of vertices
        :return: the list of all vertices
        """
        return list(self.__in_edges.keys())

    def get_nr_vertices(self):
        """
        Gets the nr of vertices in the graph
        :return: the nr of vertices
        """
        return self.__nr_vertices

    def get_nr_edges(self):
        """
        Gets the nr of edges in the graph
        :return: the nr of edges
        """
        return self.__nr_edges

    def get_in_edges(self):
        """
        Gets all the keys out of the inbound edges dictionary
        :return: the inbound edges
        """
        return list(self.__in_edges.keys())

    def get_out_edges(self):
        """
        Gets all the keys out of the outbound edges dictionary
        :return: the outbound edges
        """

        return list(self.__out_edges.keys())
    def is_edge(self, vertex_1, vertex_2):
        """
        Checks if there's an edge from vertex 1 to vertex 2
        Precondition: both parameters are valid vertices in the graph
        :param vertex_1: source vertex
        :param vertex_2: target vertex
        :return: True if the vertices form an edge, False otherwise

        """
        if vertex_2 in self.__out_edges[vertex_1]:
            return True
        return False
    def get_in_degree(self, vertex):
        """
        Gets the in degree of a vertex
        Precondition: Parameter is a valid vertex in the graph
        :param vertex: the vertex we want to find the degree of
        :return: the in degree of a vertex
        """
        if vertex in self.__in_edges:
            return len(self.__in_edges[vertex])

    def get_out_degree(self, vertex):
        """
        Gets the out degree of a vertex
        Precondition: Parameter is a valid vertex in the graph
        :param vertex: the vertex we want to find the degree of
        :return: the out degree of a vertex
        """
        if vertex in self.__out_edges:
            return len(self.__out_edges[vertex])

    def get_inbound_edges(self, vertex):
        """
        Gets all the sources of the edges whose target is the param "vertex"
        Precondition: Param is a valid vertex in the Graph
        :param vertex: target vertex
        :return: the list of inbound edges
        """
        return list(self.__in_edges[vertex])

    def get_outbound_edges(self, vertex):
        """
        Gets all the targets of the edges whose source is the param "vertex"
        Precondition: Param is a valid vertex in the Graph
        :param vertex: source vertex
        :return: the list of outbound edges
        """
        return list(self.__out_edges[vertex])

    def get_cost(self,v1,v2):
        """
        Gets the cost of an edge
        :param v1: the source vertex
        :param v2: the target vertex
        Precondition: v1 and v2 are valid vertices in the Graph
        :return: the element in the cost dictionary coresponding to the 2 given vertices
        """

        return self.__costs[(v1,v2)]

    def set_cost(self,source,target, new_cost):
        """
        Sets the cost of an edge
        :param source: the source vertex
        :param target: the target vertex
        Precondition: source and target are valid vertices in the Graph
        :param new_cost: the cost we wanna replace the initial cost with
        :return: -
        """
        self.__costs[(source,target)] = new_cost

    def set_nr_vertices(self, nr_vertices):
        """
        Sets the number of vertices
        :param nr_vertices: the new number of vertices
        :return: -
        """
        self.__nr_vertices = nr_vertices

    def set_nr_edges(self, nr_edges):
        """
        Sets the nr of edges
        :param nr_edges: the new number od edges
        :return: -
        """
        self.__nr_edges = nr_edges
    def add_vertex(self, vertex):
        """
        Adds a new vertex in the graph
        Precondition: The param vertex is a valid int value
        :param vertex: the vertex we want to add  to the graph
        :return: 1 if it was added successfully, 0 otherwise
        """

        if vertex not in self.__in_edges:
            self.__in_edges[vertex] = []
            self.__out_edges[vertex] = []
            self.__nr_vertices+=1
            return 1
        else:
            return 0

    def remove_vertex(self, vertex):
        """
        Deletes all the edges (and their costs) that include the vertex we want to remove
        Precondition: Param is a valid vertex in the graph
        :param vertex: the vertex we want to remove
        :return: -
        """

        if vertex in self.get_all_vertices():
            self.__nr_edges -= len(self.__in_edges[vertex]) + len(self.__out_edges[vertex])
            self.get_all_vertices().remove(vertex)
            for other in self.get_all_vertices():
                if vertex in self.__in_edges[other]:
                    self.__in_edges[other].remove(vertex)
                if vertex in self.__out_edges[other]:
                    self.__out_edges[other].remove(vertex)
            del self.__in_edges[vertex]
            del self.__out_edges[vertex]
            self.__nr_vertices -=1


    def add_edge(self, source, target, cost):
        """
        Adds an edge to the graph, if the given vertices don't already form an edge
        Precondition: source and target are valid vertices in the graph
        :param source: source vertex
        :param target: target vertex
        :param cost: cost of the new edge
        :return: True if it was added successfully, False otherwise
        """
        if target not in self.__out_edges[source]:
            self.__out_edges[source].append(target)
            self.__in_edges[target].append(source)
            self.__costs[(source,target)] = cost
            self.__nr_edges +=1
            return True
        else:
            return False


    def remove_edge(self, source, target):
        """
        Removes an edge denoted by 2 vertices, and its cost
        Precondition: Source and target are valid vertices in the graph
        :param source: source vertex
        :param target: target vertex
        :return: True if it was removed successfully, False otherwise
        """

        if self.is_edge(source,target):
            del self.__costs[source,target]
            self.__in_edges[target].remove(source)
            self.__out_edges[source].remove(target)
            self.__nr_edges -=1
            return True
        return False
    def get_copy_graph(self):
        """
        Creates a deep copy of the current graph
        :return: the copied graph
        """

        graph = Graph()
        graph.__nr_vertices = copy.deepcopy(self.__nr_vertices)
        graph.__nr_edges = copy.deepcopy(self.__nr_edges)
        graph.__in_edges = copy.deepcopy(self.__in_edges)
        graph.__out_edges = copy.deepcopy(self.__out_edges)
        graph.__costs = copy.deepcopy(self.__costs)
        return graph


    def make_undirected(self):
        for vertex in self.get_all_vertices():
            for neighbour in self.get_outbound_edges(vertex):
                if not self.is_edge(neighbour,vertex):
                    self.add_edge(neighbour,vertex, self.get_cost(vertex, neighbour))

    def search_connected_components(self, v1):
        visited = set()
        stack = [v1]
        while stack:
            vertex = stack.pop()
            if vertex not in visited:
                visited.add(vertex)
                for neighbour in self.get_outbound_edges(vertex):
                    if neighbour not in visited:
                        stack.append(neighbour)

        return visited


    def find_connected_components(self):
        self.make_undirected()
        visited = set()
        components = []
        for vertex in self.get_all_vertices():
            if vertex not in visited:
                visited.add(vertex)
                comp = self.search_connected_components(vertex)
                visited = visited.union(comp)
                components.append(comp)
        return components

    def dijkstra(self, source, target):
        distances = {node: float('inf') for node in self.__out_edges}
        distances[source] = 0
        predecessors = {node: None for node in self.__out_edges}
        queue = [(0,source)]
        while queue:
            current_dist, current_node = heapq.heappop(queue)
            if current_node == target:
                break
            if current_dist <= distances[current_node]:
                for neigh in self.__out_edges[current_node]:
                    distance = current_dist + self.__costs[(current_node, neigh)]
                    if distance < distances[neigh]:
                        distances[neigh] = distance
                        predecessors[neigh] = current_node
                        heapq.heappush(queue, (distance,neigh))
        path = []
        node = target
        while node is not None:
            path.insert(0, node)
            node = predecessors[node]
        return distances[target], path


    def prim(self,start):
        mst = []
        visited = set()
        pq = []
        sum = 0
        for neigh in self.get_inbound_edges(start):
            heapq.heappush(pq,(self.__costs[start,neigh],start,neigh))
        visited.add(start)
        while pq:
            cost, frm, to = heapq.heappop(pq)
            if to not in visited:
                mst.append((frm,to,cost))
                visited.add(to)
                sum +=cost
                for neigh in self.get_inbound_edges(to):
                    if neigh not in visited:
                        heapq.heappush(pq,(self.__costs[to,neigh],to,neigh))
        return mst, sum

    def TSP_function(self,vertex, visited,memo):

        if len(visited) == self.__nr_vertices:
            if(self.is_edge(vertex,0)):
                #base condition
                return self.__costs[vertex, 0], [vertex, 0]
            else:
                return float('inf'), [0]

        if(vertex, visited) in memo:
            return memo[(vertex, visited)]

        min_cost = float('inf')
        min_cycle = None
        for neigh in self.get_outbound_edges(vertex):
            if neigh not in visited:
                new_visited = visited +(neigh,)
                cost, cycle= self.TSP_function(neigh,new_visited,memo)
                if self.is_edge(vertex, neigh):
                    cost += self.__costs[vertex, neigh]
                if cost < min_cost:
                    min_cost = cost
                    min_cycle = [vertex] + cycle
        memo[(vertex, visited)] = (min_cost, min_cycle)
        return min_cost, min_cycle

    def TSP(self):
        memo = {}
        min_cycle_cost, min_cycle = self.TSP_function(0,(0,),memo)
        return min_cycle_cost, min_cycle



