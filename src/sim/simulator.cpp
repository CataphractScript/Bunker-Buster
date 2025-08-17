#include "../../include/sim/simulator.hpp"
#include "../../include/domain/city.hpp"
#include "../../include/domain/missile.hpp"
#include "../../include/graph/graph.hpp"

// Constructor initializes total_damage to 0
Simulator::Simulator() : total_damage(0) {}

// Implement getters and setters
Graph Simulator::get_graph() const { return graph; }
void Simulator::set_graph(const Graph& g) { graph = g; }

Missile Simulator::get_missile() const { return missile; }
void Simulator::set_missile(const Missile& m) { missile = m; }

// Run the scenario corresponding to scenario_num
void Simulator::run(int scenario_num) 
{
    switch (scenario_num)
    {
    case 1:
        scenario_1(); 
        break;

    case 2:
        scenario_2();
        break;

    default:
        std::cout << "Invalid scenario number!" << std::endl; 
        break;
    }

    // After running the scenario, display total damage
    std::cout << "Total damage: " << total_damage << std::endl;
}

void Simulator::scenario_1() 
{
    /* code */
}

void Simulator::scenario_2() 
{
    /* code */
}
