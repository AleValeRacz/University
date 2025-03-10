from graph import Graph
from external import ManageFiles
from Ui import UI
graph = Graph()
external = ManageFiles()
ui = UI(graph, external)

#g = external.read_graph("testing.txt")
#copy = g.get_copy_graph()
#assert(g.get_nr_vertices()==copy.get_nr_vertices())
#g.add_vertex(11)
#assert(g.get_nr_vertices()>copy.get_nr_vertices())

ui.start()

