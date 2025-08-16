#include "simulation.hpp"

// Constructor initializes total_damage to 0
simulation::simulation() : total_damage(0) {}

// Run the scenario corresponding to scenario_num
void simulation::run(int scenario_num) 
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

void simulation::scenario_1() 
{
    /* code */
}

void simulation::scenario_2() 
{
    /* code */
}
