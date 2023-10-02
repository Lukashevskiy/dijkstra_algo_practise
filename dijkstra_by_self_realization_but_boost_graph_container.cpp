#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <string>
#include <boost/graph/directed_graph.hpp>
#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graphviz.hpp>

//using boost container to representive graph
//not algos only graph container
using edge_weight_property = boost::property<boost::edge_weight_t, size_t>;
using directed_graph = boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, boost::property< boost::vertex_name_t, size_t >, edge_weight_property>;
using vertex_descriptor = boost::graph_traits<directed_graph>::vertex_descriptor;

namespace detail{
    class from_line_to_tuple_of_variadic{
    public:
        template <typename T> T read(std::istream& is){
            T t; 
            is >> t;
            return t;
        }
        
        template <typename... Args>
        std::tuple<Args...> parse(std::istream& is){
            return std::make_tuple(read<Args>(is)...);
        }

        template <typename... Args>
        std::tuple<Args...> parse(const std::string& str){
            std::istringstream is(str);
            return parse<Args...>(is);
        }

    };
}

void fill_graph(std::ifstream &fin, directed_graph &graph){
    std::string line;
    detail::from_line_to_tuple_of_variadic parser;

    std::getline(fin, line);
    auto [g, f, _] = parser.parse<int,int,int>(line);


    while(std::getline(fin, line)){
        auto [weight, to, from] = parser.parse<int, int, int>(line);
        boost::add_edge(from, to, weight, graph);
    }   
}


int main(int args, char* argv[]){

    std::ifstream fin(argv[1]);

    directed_graph graph;

    fill_graph(fin, graph);


#ifdef DEBUG
    auto [g_begin, g_end] = edges(graph);
    std::copy(g_begin, g_end, std::ostream_iterator<directed_graph::edge_descriptor>(std::cout, "\n"));
#endif

#ifdef print_graph
    boost::dynamic_properties dp;
    dp.property("id", get(boost::vertex_index, graph));
    dp.property("label", get(boost::edge_weight, graph));
    dp.property("weight", get(boost::edge_weight, graph));
    std::ofstream fout("graph.dot");
    boost::write_graphviz_dp(fout, graph, dp, std::string{"id"});
#endif
    return 0;
}