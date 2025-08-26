// simulation.hpp
#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "../graph/graph.hpp"
#include "../domain/missile.hpp"
#include "../../include/data/missile_data.hpp"

#include <iostream>

class Simulator
{
private:
    long long total_damage; // Stores total damage calculated in scenarios
    std::vector<std::vector<int>> paths;
    Graph graph;
    load_missiles missile_data;

public:
    // Constructor initializes total_damage to zero
    Simulator();

    // Getters and setters
    Graph get_graph() const;
    void set_graph(const Graph& g);

    std::vector<std::vector<int>> get_paths() const;
    
    // Run a scenario based on the scenario number
    void run(int scenario_num);

    // Different scenario functions
    void scenario_1();
    void scenario_2();
    void scenario_3(std::unordered_map<std::string, int>);
    void scenario_4(); // abc_cities: vector of city IDs containing missiles of Class A, B, or C
    // Add more scenarios as needed
};

#endif // SIMULATION_HPP
