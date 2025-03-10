from graph import Graph
import random
class ManageFiles:

    def read_graph(self, file_name):
        """
        Reads a graph from a file name
        Precondition: the format of the graph in the given file is valid
        :param file_name: the name of the file
        :return: the read graph
        """

        try:
            with open(file_name, "r") as f:
                lines = f.readlines()
                arg = lines[0].split()
        except FileNotFoundError:
            raise Exception("The file was not found!")
        nr_vertices = int(arg[0])
        nr_edges = int(arg[1])

        graph = Graph()
        for i in range (0, nr_vertices):
            graph.add_vertex(i)

        for i in range(1, len(lines)):
            source, target, cost = lines[i].split()
            source, target, cost = int(source), int(target), int(cost)
            graph.add_edge(source, target, cost)
        return graph

    def write_graph(self,file_name, graph: Graph):
        """
        Writes a given graph in a given file
        Precondition: graph is a valid object of the class Graph; the file exists
        :param file_name: the name of the file
        :param graph: the graph we want to write down
        :return: -
        """

        with open(file_name, "w") as f:
            f.write(str(graph.get_nr_vertices())+ " " + str(graph.get_nr_edges())+ "\n")
            edges = graph.get_out_edges()
            for vertex in edges:
                for v in graph.get_outbound_edges(vertex):
                    f.write(str(vertex)+" "+ str(v)+ " "+ str(graph.get_cost(vertex,v))+ "\n")


    def generate_graph(self, nr_vertices, nr_edges):
        """
        Randomly generates a graph with a given number of vertices and edges
        Precondition: The number of vertices and edges are natural numbers, and the nr of edges is smaller or equal than the square of the number of vertices
        :param nr_vertices: number of vertices
        :param nr_edges: number of edges
        :return: the generated graph
        """

        graph = Graph(nr_vertices)
        for i in range(nr_edges):
            source = random.randint(0, nr_vertices-1)
            target = random.randint(0, nr_vertices-1)
            while graph.is_edge(source, target):
                source = random.randint(0, nr_vertices - 1)
                target = random.randint(0, nr_vertices - 1)
            cost = random.randint(0,100)
            graph.add_edge(source, target,cost)
        return graph




