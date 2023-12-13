#include <iostream>
#include <fstream>
#include <iterator>
#include <limits>
#include <sstream>
#include <tuple>

constexpr size_t INF = std::numeric_limits<size_t>::max();
constexpr short VISITED = 1;
constexpr short NOT_VISITED = 0;


template<typename C>
void out_collection(C &col){
    std::copy(std::begin(col), std::end(col), std::ostream_iterator<typename C::value_type>(std::cout, " "));
    std::cout << "\n";
}

namespace detail{
    
    template <typename T>
    concept Stream = std::is_convertible_v<T, std::istream &>;

    template <typename T>
    concept ConvertableFromStream =
        requires(std::istream &is, T value) {
            { is >> value } -> Stream;
    };


    class from_line_to_tuple_of_variadic{
    public:
        template <ConvertableFromStream T>
        static T read(std::istream& is){
            T t; 
            is >> t;
            return t;
        }
        
        template <typename... Args>
        static std::tuple<Args...> parse(std::istream& is){
            return std::make_tuple(read<Args>(is)...);
        }

        template <typename... Args>
        static std::tuple<Args...> parse(const std::string& str){
            std::istringstream is(str);
            return parse<Args...>(is);
        }

    };
}


int main(int args, char **argv){

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
    
    std::vector<std::vector<std::pair<size_t, size_t>>> adjacency_list(n+1);
    
    for(std::string line; getline(fin, line);){
        if(line.empty()) continue;

        auto [weight, to, from] = detail::from_line_to_tuple_of_variadic::parse<size_t, size_t, size_t>(line);
        --from; --to;
        
        // std::cout << "----------------------------\n";
        // std::cout << std::format("from\t= {}\nto\t= {}\nweight\t= {}\n", from, to, weight);
        // std::cout << "----------------------------\n";
        
        adjacency_list[from].emplace_back(to, weight);
    }

    std::vector<size_t> weighted_path(n, INF);
    std::vector<short> visited_markers(n, NOT_VISITED);
    std::queue<size_t> lightlest_nodes;

    lightlest_nodes.push(start);
    weighted_path[start] = 0;

    while(!lightlest_nodes.empty()){
        size_t current_node = lightlest_nodes.front();
        lightlest_nodes.pop();

        visited_markers[current_node] = VISITED;


    }

    size_t from{0};
    for(auto &&edge: adjacency_list){
        for(auto [to, weight]: edge){
            std::cout << std::format("({} -> {}) - {}\n", from, to, weight);
        }
        ++from;
    }


    return EXIT_SUCCESS;
}