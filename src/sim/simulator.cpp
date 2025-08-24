#include "../../include/sim/simulator.hpp"
#include "../../include/domain/city.hpp"
#include "../../include/domain/missile.hpp"
#include "../../include/graph/graph.hpp"
#include "../../include/data/missile_data.hpp"

#include <limits>
#include <algorithm>
#include <utility>

// Constructor initializes total_damage to 0
Simulator::Simulator() : total_damage(0) {}

// Implement getters and setters
Graph Simulator::get_graph() const { return graph; }
void Simulator::set_graph(const Graph &g) { graph = g; }

Missile Simulator::get_missile() const { return missile; }
void Simulator::set_missile(const Missile &m) { missile = m; }

// Run the scenario corresponding to scenario_num
void Simulator::run(int scenario_num)
{
    switch (scenario_num)
    {
    case 1:
        scenario_1();
        break;

    // case 2:
    //     scenario_2();
    //     break;

    case 3:
        scenario_3();
        break;

    // case 4:
    //     scenario_4();
    //     break;

    default:
        std::cout << "Invalid scenario number!" << std::endl;
        break;
    }

    // After running the scenario, display total damage
    std::cout << "Total damage: " << total_damage << std::endl;
}

void Simulator::scenario_1()
{
    std::vector<int> friendly_cities = graph.get_friendly_city_ids();
    std::vector<int> enemy_cities = graph.get_enemy_city_ids();
    std::vector<std::vector<int>> paths;
    paths.reserve(friendly_cities.size());

    for (auto start_city : friendly_cities)
    {
        std::vector<int> path;
        int current_city = start_city;
        bool target_hit = false;

        path.push_back(start_city);

        while (!target_hit)
        {
            int next_city = -1;
            double best_distance = std::numeric_limits<double>::max();

            // Check all cities to find neighbors within ≤ 500 distance
            for (size_t i = 0; i < graph.city_count(); i++)
            {
                if (i == current_city)
                    continue;

                double dis = graph.distance(current_city, i);
                if (dis <= 500)
                {
                    // If this city is an enemy → missile hits the target
                    if (std::find(enemy_cities.begin(), enemy_cities.end(), i) != enemy_cities.end())
                    {
                        path.push_back(i);
                        target_hit = true;
                        break;
                    }

                    // Compute the distance of this candidate city to the closest enemy
                    double min_dis_to_enemy = std::numeric_limits<double>::max();
                    for (auto enemy_city : enemy_cities)
                    {
                        double dis_to_enemy = graph.distance(i, enemy_city);
                        if (dis_to_enemy < min_dis_to_enemy)
                            min_dis_to_enemy = dis_to_enemy;
                    }

                    // Select the best candidate (the one closer to the enemy)
                    // Tie-breaker: prefer city with no spies
                    if (min_dis_to_enemy < best_distance ||
                        (min_dis_to_enemy == best_distance && !graph.get_city(i).get_has_spy()))
                    {
                        best_distance = min_dis_to_enemy;
                        next_city = i;
                    }
                }
            }

            if (target_hit)
                break;

            if (next_city == -1)
            {
                // Stuck → no valid path found
                break;
            }

            current_city = next_city;
            path.push_back(current_city);
        }

        paths.push_back(path);
    }

    /*
        TODO: یه مشکلی داره ممکنه اصلا به هدفی نرسه
        اگر یه مسیری فقط ابتداش کمی دور تر بشیم از دشمن ولی در انتها بتونیم بهش اصابت کنیم ممکنه در رقابت با مسیری که ابتدا سریع تر به دشمن نزدیک میشه ولی در اخر هیچ راهی برای رسیدن به دشمن نمیزاره ببازه!
        از سری مشکلات الگوریتم های گریدی 
    */
}

void Simulator::scenario_2(std::vector<int>& a_cities) {
    std::vector<int> enemy_cities = graph.get_enemy_city_ids();
    std::vector<std::vector<int>> paths;

    for (const int &a : a_cities) {
        if (graph.get_city(a).get_missile_count() > 0) {
            // The shortest distance to one of the enemy cities
            double short_d = std::numeric_limits<double>::max();

            // The closest enemy city ID
            int closest_ec_id;
            for (const int &ec : enemy_cities) {
                if (graph.distance(a, ec) < short_d) {
                    short_d = graph.distance(a, ec);
                    closest_ec_id = ec;
                }
            }
            // Class A missile range: 2500
            if (short_d < 2500) {
                int current_city = a;
                std::vector<int> path;

                // Add the starting city to the path
                path.push_back(a);

                // Number of spies encountered along the path
                int spies_count = 0;

                while (true) {
                    // Check if the current city is not an enemy city
                    if (graph.get_city(current_city).get_city_status_int() != 3) {
                        // Candidate cities for the missile's next move (Cities that don't have spies(ID, distance), Cities that have spies(ID, distance))
                        std::pair<std::vector<std::pair<int, double>>, std::vector<std::pair<int, double>>> candidates;
                        for (size_t i = 0; i < graph.city_count(); i++) {
                            // Enemy city located west of the current city, within the uncontrolled range of Class A missiles (main conditions)
                            if (graph.get_city(i).get_coordinates().first <= graph.get_city(current_city).get_coordinates().first && graph.distance(current_city, i) < 500) {
                                if (!graph.get_city(i).get_has_spy()) {
                                    candidates.first.push_back({i, graph.distance(current_city, i)});
                                } else {
                                    candidates.second.push_back({i, graph.distance(current_city, i)});
                                }
                            } else {
                                continue;
                            }
                        }
                        // Sort candidate cities in ascending order of distance
                        std::sort(candidates.first.begin(), candidates.first.end(), [](const std::pair<int,double> &a, const std::pair<int,double> &b) {
                            return a.second < b.second; 
                        });
                        std::sort(candidates.second.begin(), candidates.second.end(), [](const std::pair<int,double> &a, const std::pair<int,double> &b) {
                            return a.second < b.second;
                        });
                            
                        // Check if a city without any spies exists
                        if (!candidates.first.empty()) {
                            current_city = candidates.first.front().first;
                            path.push_back(candidates.first.front().first);
                        } else if (!candidates.second.empty()) {
                            spies_count++;
                            path.push_back(candidates.second.front().first);
                        }
                    } else if(graph.get_city(closest_ec_id).get_defense_count() > 0) {
                        if (spies_count >= 4) {
                            graph.set_missile_count(a, "A1", 0);
                            graph.set_missile_count(a, "A2", 0);;
                            graph.set_missile_count(a, "A3", 0);;
                        } else if (spies_count == 3) {
                            graph.set_missile_count(a, "A1", 0);;
                            graph.set_missile_count(a, "A2", 0);;
                        } else if (spies_count == 2) {
                            graph.set_missile_count(a, "A2", 0);;
                        }
                        if ((graph.get_city(a).get_missile_stock().at("A1") * 100) + (graph.get_city(a).get_missile_stock().at("A2") * 130) + (graph.get_city(a).get_missile_stock().at("A3") * 25) != 0) {
                            paths.push_back(path);
                        }
                        total_damage += (graph.get_city(a).get_missile_stock().at("A1") * 100) + (graph.get_city(a).get_missile_stock().at("A2") * 130) + (graph.get_city(a).get_missile_stock().at("A3") * 25);
                        break;
                    } else {
                        break;
                    }
                }
            } else {
                continue;
            }
        }
    }
}

void Simulator::scenario_3() {}

void Simulator::scenario_4(std::vector<int>& abc_cities) {
    std::vector<int> enemy_cities = graph.get_enemy_city_ids();
    std::vector<std::vector<int>> paths;

    for (const int &abc : abc_cities) {
        if (graph.get_city(abc).get_missile_count() > 0) {
            // Stores distances to all enemy cities
            std::vector<double> enemy_city_distances;

            for (const int &ec : enemy_cities) {
                enemy_city_distances.push_back(graph.distance(abc, ec));
            }

            // Sort enemy city distances in ascending order
            std::sort(enemy_city_distances.begin(), enemy_city_distances.end());

            // Minimum missile range in the set
            int missile_min_range = 0;
            // A1 range = A2 range = A3 range / B1 range = B2 range / C range + 100 = C1 rang
            if (graph.get_city(abc).get_missile_stock().at("A1") > 0 ||
                graph.get_city(abc).get_missile_stock().at("A2") > 0 ||
                graph.get_city(abc).get_missile_stock().at("A3") > 0)    
            {
                missile_min_range = missile_data.get_shahab7().get_range();
            }
    }
}
