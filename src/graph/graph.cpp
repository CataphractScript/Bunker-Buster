#include "graph.hpp"

void Graph::add_city(const City &c)
{
    // Assign an internal ID to the city and store it in the map
    cities[next_id] = c;
    next_id++;
}

void Graph::compute_adjacency_matrix()
{
    size_t n = cities.size();
    // Initialize the adjacency matrix with zeros
    adj_matrix.assign(n, std::vector<double>(n, 0.0));

    // Compute Euclidean distances between all pairs of cities
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = i + 1; j < n; ++j)
        {
            auto coordA = cities.at(i).get_coordinates();
            auto coordB = cities.at(j).get_coordinates();

            double dx = static_cast<double>(coordA.first - coordB.first);
            double dy = static_cast<double>(coordA.second - coordB.second);
            double dist = std::sqrt(dx * dx + dy * dy);

            // Since the graph is undirected, distances are symmetric
            adj_matrix[i][j] = dist;
            adj_matrix[j][i] = dist;
        }
    }
}

double Graph::distance(int cityA_id, int cityB_id) const
{
    // Check if city IDs are within bounds
    if (cityA_id < 0 || cityA_id >= static_cast<int>(adj_matrix.size()) ||
        cityB_id < 0 || cityB_id >= static_cast<int>(adj_matrix.size()))
    {
        throw std::out_of_range("City index out of range in distance()");
    }
    // Return precomputed distance from adjacency matrix
    return adj_matrix[cityA_id][cityB_id];
}

const City &Graph::get_city(int id) const
{
    auto it = cities.find(id);
    if (it == cities.end())
    {
        throw std::out_of_range("City ID not found");
    }
    // Return a constant reference to the city object
    return it->second;
}