#include "../../include/graph/graph.hpp"

void Graph::add_city(const City &c)
{
    // Assign an internal ID to the city
    switch (c.get_city_status_int())
    {
    case 1: // Friendly
        friendly_cities[next_id] = c;
        break;
    case 2: // Neutral
        neutral_cities[next_id] = c;
        break;
    case 3: // Enemy
        enemy_cities[next_id] = c;
        break;
    default:
        throw std::invalid_argument("Invalid city status");
    }
    next_id++;
}

void Graph::compute_adjacency_matrix()
{
    size_t n = city_count();
    // Initialize the adjacency matrix with zeros
    adj_matrix.assign(n, std::vector<double>(n, 0.0));

    // Combine all maps into one temp lookup for indexing
    std::unordered_map<int, City> all_cities;
    all_cities.insert(friendly_cities.begin(), friendly_cities.end());
    all_cities.insert(enemy_cities.begin(), enemy_cities.end());
    all_cities.insert(neutral_cities.begin(), neutral_cities.end());

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = i + 1; j < n; ++j)
        {
            auto coordA = all_cities.at(i).get_coordinates();
            auto coordB = all_cities.at(j).get_coordinates();

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
    if (cityA_id < 0 || cityA_id >= static_cast<int>(adj_matrix.size()) ||
        cityB_id < 0 || cityB_id >= static_cast<int>(adj_matrix.size()))
    {
        throw std::out_of_range("City index out of range in distance()");
    }
    return adj_matrix[cityA_id][cityB_id];
}

const City &Graph::get_city(int id) const
{
    if (friendly_cities.count(id))
        return friendly_cities.at(id);
    if (enemy_cities.count(id))
        return enemy_cities.at(id);
    if (neutral_cities.count(id))
        return neutral_cities.at(id);
    throw std::out_of_range("City ID not found");
}

bool Graph::has_city(int id) const
{
    return friendly_cities.count(id) || enemy_cities.count(id) || neutral_cities.count(id);
}