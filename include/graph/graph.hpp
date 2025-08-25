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
    std::unordered_map<int, City> friendly_cities;
    std::unordered_map<int, City> enemy_cities;
    std::unordered_map<int, City> neutral_cities;

    std::vector<std::vector<double>> adj_matrix; // distance matrix
    int next_id = 0;

public:
    // Add a city with a unique ID (classification based on status)
    void add_city(const City &c);

    // Build adjacency matrix (after all cities are added)
    void compute_adjacency_matrix();

    // Get distance by city ID
    double distance(int cityA_id, int cityB_id) const;

    // Get total city count
    size_t city_count() const { return friendly_cities.size() + enemy_cities.size() + neutral_cities.size(); }

    // Access city by ID
    City &get_city(int id);

    // Check if city exists
    bool has_city(int id) const;

    // Access category maps
    std::vector<int> get_friendly_city_ids() const;
    std::vector<int> get_enemy_city_ids() const;
    std::vector<int> get_neutral_city_ids() const;

    void Graph::set_missile_count(int id, std::string class_id, int number);
};

#endif // GRAPH_HPP