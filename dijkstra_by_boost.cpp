#include <boost/graph/adjacency_list.hpp>
#include <iostream>

int main(int args, char *argv[]){
    using EdgeWeightProperty = boost::property<boost::edge_weight_t, int>;
    using DirectedGraph = boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, boost::no_property, EdgeWeightProperty>;
    using edge_iterator = boost::graph_traits<DirectedGraph>::edge_iterator;
    using EdgeMapProperty = boost::property_map<DirectedGraph, boost::edge_weight_t>::type;

    DirectedGraph g;

    boost::add_edge (0, 1, 3, g);
    boost::add_edge (0, 2, 1, g);
    boost::add_edge (0, 3, 7, g);
    boost::add_edge (1, 3, 6, g);
    boost::add_edge (2, 3, 9, g);


    EdgeMapProperty edgeWeightMap = get(boost::edge_weight_t(), g);

    std::pair<edge_iterator, edge_iterator> ei = edges(g);

    std::cout << "Количество ребер = " << num_edges(g) << "\n";
    std::cout << "Список ребер:\n";

    std::for_each(ei.first, ei.second, [&](auto edge){
        std::cout << edge << " " << edgeWeightMap[edge] << std:: endl;
    });
    std::cout << std::endl;
    
    
    
    return 0;
}