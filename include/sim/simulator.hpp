// simulation.hpp
#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "../graph/graph.hpp"
#include "../domain/missile.hpp"

#include <iostream>

class Simulator
{
private:
    long long total_damage; // Stores total damage calculated in scenarios
    Graph graph;
    Missile missile;

public:
    // Constructor initializes total_damage to zero
    Simulator();

    // Getter and setter
    Graph get_graph() const;
    void set_graph(const Graph& g);

    Missile get_missile() const;
    void set_missile(const Missile& m);

    // Run a scenario based on the scenario number
    void run(int scenario_num);

    // Different scenario functions
    void scenario_1();
    void scenario_2();
    // Add more scenarios as needed
};

#endif // SIMULATION_HPP
