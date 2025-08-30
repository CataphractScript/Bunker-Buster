#include "include/sim/simulator.hpp"
#include "include/data/graph_data.hpp"

#include <vector>

int main() {
    Simulator s_1;
    s_1.set_graph(load_graph_for_scenario4());
    s_1.run(4);

    return 0;
}