from external import ManageFiles
from graph import Graph
class UI:
    def __init__(self, graph: Graph, manage: ManageFiles):
        self.__graph = graph
        self.__manage = manage

    def print_menu(self):
        print("""Menu
            1.Print the number of vertices.
            2.Print the set of vertices.
            3.Find if there's an edge between two vertices.
            4.Get the in degree and out degree of a vertex.
            5.Print the set of outbound edges of a vertex.
            6.Print the set of inbound edges of a vertex.
            7.Print the cost of an edge.
            8.Set the cost of an edge.
            9.Add a vertex.
            10.Remove a vertex.
            11.Add an edge.
            12.Remove an edge.
            13.Copy the graph.
            14.Read graph from file.
            15.Write graph to file.
            16.Generate a random graph.
            17.Find connected components.
            
            0.Exit.
        """)

    def print_nr_vertices_ui(self):
        nr_vertices = self.__graph.get_nr_vertices()
        print(f"the number of vertices is: {nr_vertices}")


    def print_set_vertices(self):
        vertices = self.__graph.get_all_vertices()
        for vertex in vertices:
            print(vertex, end=" ")
        print()

    def find_edge_ui(self):
        try:
            vertex_1 = int(input("enter source vertex: "))
            vertex_2 = int(input("enter target vertex: "))
        except ValueError:
            print("Invalid input!")
            return
        if (vertex_1 in self.__graph.get_all_vertices()):
            result = self.__graph.is_edge(vertex_1, vertex_2)
            if result:
                print("Yes!")
            else:
                print("No!")
        else:
            print("At least one of the vertices is not in the graph!")

    def get_in_out_degrees_ui(self):
        try:
            vertex = int(input("enter vertex: "))
        except ValueError:
            print("Invalid input!")
            return
        if vertex in self.__graph.get_all_vertices():
            in_degree = self.__graph.get_in_degree(vertex)
            out_degree = self.__graph.get_out_degree(vertex)
            print(f"The in degree is {in_degree} and the out degree is {out_degree}")
        else:
            print("The vertex is not in the graph!")

    def print_outbound_ui(self):
        try:
            vertex = int(input("enter vertex: "))
        except ValueError:
            print("Invalid input")
            return
        if vertex in self.__graph.get_all_vertices():
            for edge in self.__graph.get_outbound_edges(vertex):
                print(edge)
        else:
            print("The vertex is not in the graph!")

    def print_inbound_ui(self):
        try:
            vertex = int(input("enter vertex: "))
        except ValueError:
            print("Invalid input")
            return
        if vertex in self.__graph.get_all_vertices():
            for edge in self.__graph.get_inbound_edges(vertex):
                print(edge)
        else:
            print("The vertex is not in the graph!")

    def print_cost_ui(self):
        try:
            x = int(input("enter source: "))
            y = int(input("enter target: "))
        except ValueError:
            print("Invalid input")
            return
        if (x in self.__graph.get_all_vertices() and y in self.__graph.get_all_vertices()):
            if(self.__graph.is_edge(x,y)):
                cost = self.__graph.get_cost(x,y)
                print(cost)
            else:
                print("Edge doesn't exist!")
        else:
            print("At least one of the vertices is not in the graph!")


    def set_cost_ui(self):
        try:
            x = int(input("enter source: "))
            y = int(input("enter target: "))
            cost = int(input("enter cost: "))
        except ValueError:
            print("Invalid input")
            return
        if (x in self.__graph.get_all_vertices() and y in self.__graph.get_all_vertices()):
            if (self.__graph.is_edge(x, y)):
                self.__graph.set_cost(x,y,cost)
                print("Set successfully!")
            else:
                print("Edge doesn't exist!")
        else:
            print("At least one of the verteces is not in the graph")

    def add_vertex_ui(self):
        try:
            vertex = int(input("enter vertex: "))
        except ValueError:
            print("Invalid input")
            return

        if self.__graph.add_vertex(vertex) == 1:
                print("Added successfully!")
        else:
            print("The vertex is already in the graph!")

    def remove_vertex_ui(self):
        try:
            vertex = int(input("enter vertex: "))
        except ValueError:
            print("Invalid input")
            return
        if (vertex in self.__graph.get_all_vertices()):
             self.__graph.remove_vertex(vertex)
             print("Removed successfully")
        else:
            print("The vertex is not in the graph!")

    def add_edge_ui(self):
        try:
            source = int(input("enter source vertex: "))
            target = int(input("enter the target vertex: "))
            cost = int(input("enter cost: "))
        except ValueError:
            print("Invalid input")
            return
        if source in self.__graph.get_all_vertices() and target in self.__graph.get_all_vertices():
            if self.__graph.add_edge(source, target, cost) == False:
                print("Edge already exists!")
            else:
                print("Added successfully")
        else:
            print("At least one of the vertices is not in the graph")

    def remove_edge_ui(self):
        try:
            source = int(input("enter source vertex: "))
            target = int(input("enter the target vertex: "))
        except ValueError:
            print("Invalid input")
            return
        if self.__graph.remove_edge(source, target) == True:
            print("Removed successfully")
        else:
            print("No edge with the input data found!")

    def copy_graph_ui(self):
        graph = self.__graph.get_copy_graph()
        print("Copied successfully!")
        file = input("enter file name for writing the copied graph: ")
        self.__manage.write_graph(file, graph)

    def read_graph_ui(self):
        file_name = input("enter file_name: ")
        #try:
        self.__graph = self.__manage.read_graph(file_name)
        print("Read successfully")
        #except Exception as e:
            #print(e)
    def write_graph_ui(self):
        file_name = input("enter file_name: ")
        try:
            self.__manage.write_graph(file_name,self.__graph)
            print("Written successfully")
        except Exception as e:
            print(e)

    def generate_graph_ui(self):
        try:
            nr_vertices = int(input("Enter nr of vertices: "))
            nr_edges = int(input("Enter nr of edges: "))
        except ValueError:
            print("Invalid input!")
            return

        file = input("Enter name of file where to write the graph: ")
        if nr_edges > nr_vertices * nr_vertices or nr_edges < 0 or nr_vertices < 0:
            print("Nr of edges or vertices is unachievable!")
            return
        gr = self.__manage.generate_graph(nr_vertices, nr_edges)
        print("Generated successfully")
        try:
            self.__manage.write_graph(file, gr)
        except Exception as e:
            print(e)

    def dijkstra_ui(self):
        try:
            source = int(input("enter source vertex: "))
            target = int(input("enter the target vertex: "))
        except ValueError:
            print("Invalid input")
            return
        if source in self.__graph.get_all_vertices() and target in self.__graph.get_all_vertices():
            distance, path = self.__graph.dijkstra(source,target)
            if distance != float('inf'):
                print(path)
                print(distance)
            else:
                print("there's no path!")
        else:
            print("At least one of the vertices is not in the graph")
    def start(self):

        while True:
            self.print_menu()
            choice = input("enter choice: ")

            if choice == '1':
                self.print_nr_vertices_ui()
            elif choice == '2':
                self.print_set_vertices()
            elif choice == '3':
                self.find_edge_ui()
            elif choice == '4':
                self.get_in_out_degrees_ui()
            elif choice == '5':
                self.print_outbound_ui()
            elif choice == '6':
                self.print_inbound_ui()
            elif choice == '7':
                self.print_cost_ui()
            elif choice == '8':
                self.set_cost_ui()
            elif choice == '9':
                self.add_vertex_ui()
            elif choice == '10':
                self.remove_vertex_ui()
            elif choice == '11':
                self.add_edge_ui()
            elif choice == '12':
                self.remove_edge_ui()
            elif choice == '13':
                self.copy_graph_ui()
            elif choice == '14':
                self.read_graph_ui()
            elif choice == '15':
                self.write_graph_ui()
            elif choice == '16':
                self.generate_graph_ui()
            elif choice == '17':
                components = self.__graph.find_connected_components()
                for comp in components:
                    print(comp)
            elif choice == '18':
                self.dijkstra_ui()
            elif choice == '19':
                vertex = int(input("enter starting vertex: "))
                self.__graph.make_undirected()
                mst, sum = self.__graph.prim(vertex)
                print(mst)
                print(sum)
            elif choice == '20':
                cost, cycle = self.__graph.TSP()
                if cost != float('inf'):
                    print(cycle)
                    print(cost)
                else:
                    print("There's no solution!")

            elif choice == '0':
                break
            else:
                print("Invalid choice!")
