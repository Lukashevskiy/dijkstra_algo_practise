#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>
int main(int args, char *argv[]){
    using edge_weight_property = boost::property<boost::edge_weight_t, size_t>;
    using directed_graph = boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, boost::no_property, edge_weight_property>;
    using edge_iterator = boost::graph_traits<directed_graph>::edge_iterator;
    using weight_of_edges_map_property = boost::property_map<directed_graph, boost::edge_weight_t>::type;
    using vertex_descriptor = boost::graph_traits<directed_graph>::vertex_descriptor;


    directed_graph graph;

    int f, g;
    std::ifstream fin(argv[1]);
    fin >> f;
    fin >> f;
    fin >> g;
    
    --f;
    --g;
    
    std::string line;
    std::stringstream buf;

    std::getline(fin, line);
    
    int from, to, weight;
    
    while(std::getline(fin, line)){
        buf << line;
        
        buf >> from >> to >> weight;
        --from;
        --to;
        
        boost::add_edge(from, to, weight, graph);

        buf.clear();
    }   



    vertex_descriptor start = vertex(f, graph);
    vertex_descriptor end = vertex(g, graph);

    std::vector<vertex_descriptor> predecessors(num_vertices(graph));
    std::vector<int> distances(num_vertices(graph));
    
    boost::dijkstra_shortest_paths(graph, start, boost::predecessor_map(&predecessors[0]).distance_map(&distances[0]));



    std::vector<vertex_descriptor> path; 
    auto current = end;
    do{
        path.push_back(current);
        current = predecessors[current];
    }while(current != start);


    std::cout << "Path from " << start + 1 << " to " << end + 1 << " = " << distances[end] << '\n';
    std::copy(path.begin(), path.end(), std::ostream_iterator<vertex_descriptor>(std::cout, " -> "));
    std::cout << ++start << std::endl;
    
    
    return 0;
}