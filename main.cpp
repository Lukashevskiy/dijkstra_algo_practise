#include <cstdlib>
#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>
#include <tuple>
#include <vector>
#include <format>
#include <queue>
#include <iterator>

constexpr size_t INF = std::numeric_limits<size_t>::max();
constexpr short VISITED = 1;
constexpr short NOT_VISITED = 0;
using edge_t = std::pair<size_t, size_t>;
using adjacently_list_t = std::vector<std::vector<edge_t>>;
/* TODO */
// add require for typename //
template<typename C>
void out_collection(const C &col){
    std::copy(std::begin(col), std::end(col), std::ostream_iterator<short>(std::cout, " "));
    std::cout << "\n";
}


namespace detail{
    
    template <typename T>
    concept Stream = std::is_convertible_v<T, std::istream &>;

    template <typename T>
    concept ConvertableFromStream =
        requires(std::istream &istr, T value) {
            { istr >> value } -> Stream;
    };


    class from_line_to_tuple_of_variadic{
    public:
        template <ConvertableFromStream T>
        static T read(std::istream& istr){
            T item; 
            istr >> item;
            return item;
        }
        
        template <typename... Args>
        static std::tuple<Args...> parse(std::istream& istr){
            return std::make_tuple(read<Args>(istr)...);
        }

        template <typename... Args>
        static std::tuple<Args...> parse(const std::string& str){
            std::istringstream istr(str);
            return parse<Args...>(istr);
        }

    };
}

void out_adjacency_list(adjacently_list_t &list){
    size_t from{0};
    for(auto &&edge: list){
        for(auto [to, weight]: edge){
            std::cout << std::format("({} -> {}) - {}\n", from, to, weight);
        }
        ++from;
    }
}

int main(int args, char* argv[]){
    std::ios_base::sync_with_stdio(false);

    if(args < 2){
        std::cerr << "Input file not inserted.\nUse program like: './a.out {filename}'\n";
        return EXIT_FAILURE;
    }
    
    std::ifstream fin{argv[1]};

    if(!fin){
        std::cerr << std::format("File '{}' can't be opened.\n", argv[1]);
        return EXIT_FAILURE;
    }

    auto [n, start, end] = detail::from_line_to_tuple_of_variadic::parse<size_t, size_t, size_t>(fin);
    --start;
    --end;
    
    std::cout << std::format("n\t= {}\nstart\t= {}\nstop\t= {}\n", n, start, end);
    
    adjacently_list_t edges(n);
    
    for(std::string line; getline(fin, line);){
        if(line.empty()) { 
            continue;
        }

        auto [weight, to, from] = detail::from_line_to_tuple_of_variadic::parse<size_t, size_t, size_t>(line);
        --from; --to;

        edges[from].emplace_back(weight, to);
    }
    std::vector<size_t> weighted_path(n, INF);
    std::vector<char> visited_markers(n, NOT_VISITED);
    std::vector<size_t> predcessors(n, 0);
    std::priority_queue<edge_t, std::vector<edge_t>, std::greater<>> lightlest_nodes;

    lightlest_nodes.emplace(0, start);

    weighted_path[start] = 0;

    while(!lightlest_nodes.empty()){
        auto [_, current_node] = lightlest_nodes.top();
        lightlest_nodes.pop();
        visited_markers[current_node] = VISITED;
        
        for(auto &[weight, v]: edges[current_node]){
            
            if(weighted_path[v] > weighted_path[current_node] + weight){
                weighted_path[v] = weighted_path[current_node] + weight;
                lightlest_nodes.emplace(weighted_path[v], v);
                predcessors[v] = current_node;
            }
        }
/*
        out_collection(visited_markers);
        out_collection(predcessors);
*/
    }

    out_collection(weighted_path);
    std::stringstream out_path{};
    while(end != start){
        out_path << (end+1);
        out_path << " <- ";
        end = predcessors[end];
    }
    out_path << (start+1) << '\n';
    std::cout << weighted_path[end] << "\n";
    std::cout << out_path.str();

    return EXIT_SUCCESS;
}
