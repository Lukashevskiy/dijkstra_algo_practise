#include <boost/graph/adjacency_list.hpp>
#include <iostream>

int main(int args, char *argv[]){
    using EdgeWeightProperty = boost::property<boost::edge_weight_t, int>;
    using DirectedGraph = boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, boost::no_property, EdgeWeightProperty>;
    using edge_iterator = boost::graph_traits<DirectedGraph>::edge_iterator;


    DirectedGraph g;

    boost::add_edge (0, 1, 3, g);
    boost::add_edge (0, 2, 1, g);
    boost::add_edge (0, 3, 7, g);
    boost::add_edge (1, 3, 6, g);
    boost::add_edge (2, 3, 9, g);


    std::pair<edge_iterator, edge_iterator> ei = edges(g);

    std::cout << "Количество ребер = " << num_edges(g) << "\n";
    std::cout << "Список ребер:\n";

    std::copy( ei.first, ei.second,
              std::ostream_iterator<boost::adjacency_list<>::edge_descriptor>{
                  std::cout, "\n"});

    std::cout << std::endl;
    
    
    
    return 0;
}