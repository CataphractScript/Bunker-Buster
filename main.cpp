#include "include/sim/simulator.hpp"
#include "include/data/graph_data.hpp"
#include "include/graph/graph.hpp"
#include "include/domain/city.hpp"

#include <vector>

int main() {
    Simulator s_1;
    s_1.set_graph(load_graph_for_scenario2());
    s_1.run(2);
    std::vector<std::vector<int>> paths = s_1.get_paths();

    for (const std::vector<int> &path : paths) {
        for (const int &c : path) {
            std::cout << c << "/t";
        }
    }
    return 0;
}