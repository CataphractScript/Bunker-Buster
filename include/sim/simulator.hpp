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
    Graph graph;
    Missile missile;
    load_missiles missile_data;

public:
    // Constructor initializes total_damage to zero
    Simulator();

    // Getters and setters
    Graph get_graph() const;
    void set_graph(const Graph& g);

    Missile get_missile() const;
    void set_missile(const Missile& m);

    // Run a scenario based on the scenario number
    void run(int scenario_num);

    // Different scenario functions
    void scenario_1();
    void scenario_2(std::vector<int>& a_cities);
    void scenario_3();
    void scenario_4(std::vector<int>& abc_cities); // abc_cities: vector of city IDs containing missiles of Class A, B, or C
    // Add more scenarios as needed
};

#endif // SIMULATION_HPP
