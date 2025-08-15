#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_map>
#include <vector>
#include <cmath>
#include <stdexcept>
#include "../../include/domain/city.hpp"

class Graph
{
private:
    std::unordered_map<int, City> cities;        // city_id → city object
    std::vector<std::vector<double>> adj_matrix; // distance matrix
    int next_id = 0;

public:
    // Add a city with a unique ID
    void add_city(const City &c);

    // Build adjacency matrix (after all cities are added)
    void compute_adjacency_matrix();

    // Get distance by city ID
    double distance(int cityA_id, int cityB_id) const;

    // Get city count
    size_t city_count() const { return cities.size(); }

    // Access city by ID
    const City &get_city(int id) const;

    // Check if city exists
    bool has_city(int id) const { return cities.find(id) != cities.end(); }
};

#endif // GRAPH_HPP