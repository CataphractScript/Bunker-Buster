// simulation.hpp
#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <iostream>

class Simulator
{
private:
    long long total_damage; // Stores total damage calculated in scenarios
    Graph graph;

public:
    // Constructor initializes total_damage to zero
    Simulator();

    // Getter and setter for the Graph object
    Graph get_graph();
    void set_graph(const Graph& g);
    
    // Run a scenario based on the scenario number
    void run(int scenario_num);

    // Different scenario functions
    void scenario_1();
    void scenario_2();
    // Add more scenarios as needed
};

#endif // SIMULATION_HPP
