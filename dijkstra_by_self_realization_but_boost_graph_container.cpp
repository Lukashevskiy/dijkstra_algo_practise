#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <string>
#include <sstream>
#include <boost/graph/directed_graph.hpp>
#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>


//using boost container to representive graph
//not algos only graph container
using edge_weight_property = boost::property<boost::edge_weight_t, size_t>;
using directed_graph = boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, boost::no_property, edge_weight_property>;
using vertex_descriptor = boost::graph_traits<directed_graph>::vertex_descriptor;


void fill_graph(const std::ifstream &fin, const directed_graph &graph){
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
}


int main(int args, char* argv[]){

    int f, g;
    std::ifstream fin(argv[1]);
    fin >> f;
    fin >> f;
    fin >> g;
    
    --f;
    --g;
    


    return 0;
}