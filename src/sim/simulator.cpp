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

    struct Result
    {
        int missile_id;
        int start_city;
        int target_city = -1;
        std::vector<int> path;
        bool hit_target = false;
        bool detected = false;
        double total_distance = 0;
        double expected_damage = 0;
    };

    std::vector<Result> results;

    for (auto start_city : friendly_cities)
    {
        const City &city = graph.get_city(start_city);
        std::vector<Missile> missiles = city.get_missiles();

        // In scenario 1: fire all missiles of this city (guaranteed 2 of type D)
        for (int shot = 0; shot < (int)missiles.size(); shot++)
        {
            const Missile &m = missiles[shot];
            if (m.get_class_id() != "D")
                throw std::runtime_error("Scenario 1 expects only D-class missiles!");

            Result res;
            res.missile_id = shot;
            res.start_city = start_city;

            std::vector<int> path;
            int current_city = start_city;
            bool target_hit = false;
            double total_distance = 0;

            path.push_back(start_city);

            while (!target_hit)
            {
                int next_city = -1;
                double best_distance = std::numeric_limits<double>::max();

                // Check all cities as possible next steps
                for (size_t i = 0; i < graph.city_count(); i++)
                {
                    if (i == current_city)
                        continue;

                    double dis = graph.distance(current_city, i);

                    // Constraint: must be within missile's uncontrolled range
                    if (dis <= m.get_uncontrolled_range())
                    {
                        // If this city is an enemy → missile hits the target
                        if (std::find(enemy_cities.begin(), enemy_cities.end(), i) != enemy_cities.end())
                        {
                            path.push_back(i);
                            total_distance += dis;
                            res.target_city = i;
                            res.hit_target = true;
                            res.expected_damage = m.get_damage();
                            target_hit = true;
                            break;
                        }

                        // Compute distance to the closest enemy from this candidate
                        double min_dis_to_enemy = std::numeric_limits<double>::max();
                        for (auto enemy_city : enemy_cities)
                        {
                            double dis_to_enemy = graph.distance(i, enemy_city);
                            if (dis_to_enemy < min_dis_to_enemy)
                                min_dis_to_enemy = dis_to_enemy;
                        }

                        // Select best candidate (closer to enemy, tie-breaker = no spies)
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
                    // No valid path found
                    break;
                }

                total_distance += graph.distance(current_city, next_city);
                current_city = next_city;
                path.push_back(current_city);
            }

            res.path = path;
            res.total_distance = total_distance;

            // Detection check: if there is a spy in any city along the path
            for (int c : path)
                if (graph.get_city(c).get_has_spy())
                    res.detected = true;

            results.push_back(res);
        }
    }
    /*
        TODO: یه مشکلی داره ممکنه اصلا به هدفی نرسه
        اگر یه مسیری فقط ابتداش کمی دور تر بشیم از دشمن ولی در انتها بتونیم بهش اصابت کنیم ممکنه در رقابت با مسیری که ابتدا سریع تر به دشمن نزدیک میشه ولی در اخر هیچ راهی برای رسیدن به دشمن نمیزاره ببازه!
        از سری مشکلات الگوریتم های گریدی
    */
}

void Simulator::scenario_2(std::vector<int> &a_cities)
{
    std::vector<int> enemy_cities = graph.get_enemy_city_ids();
    std::vector<std::vector<int>> paths;

    for (const int &a : a_cities)
    {
        if (graph.get_city(a).get_missile_count() > 0)
        {
            // The shortest distance to one of the enemy cities
            double short_d = std::numeric_limits<double>::max();

            // The closest enemy city ID
            int closest_ec_id;
            for (const int &ec : enemy_cities)
            {
                if (graph.distance(a, ec) < short_d)
                {
                    short_d = graph.distance(a, ec);
                    closest_ec_id = ec;
                }
            }
            // Class A missile range: 2500
            if (short_d < 2500)
            {
                int current_city = a;
                std::vector<int> path;

                // Add the starting city to the path
                path.push_back(a);

                // Number of spies encountered along the path
                int spies_count = 0;

                while (true)
                {
                    // Check if the current city is not an enemy city
                    if (graph.get_city(current_city).get_city_status_int() != 3)
                    {
                        // Candidate cities for the missile's next move (Cities that don't have spies(ID, distance), Cities that have spies(ID, distance))
                        std::pair<std::vector<std::pair<int, double>>, std::vector<std::pair<int, double>>> candidates;
                        for (size_t i = 0; i < graph.city_count(); i++)
                        {
                            // Enemy city located west of the current city, within the uncontrolled range of Class A missiles (main conditions)
                            if (graph.get_city(i).get_coordinates().first <= graph.get_city(current_city).get_coordinates().first && graph.distance(current_city, i) < 500)
                            {
                                if (!graph.get_city(i).get_has_spy())
                                {
                                    candidates.first.push_back({i, graph.distance(current_city, i)});
                                }
                                else
                                {
                                    candidates.second.push_back({i, graph.distance(current_city, i)});
                                }
                            }
                            else
                            {
                                continue;
                            }
                        }
                        // Sort candidate cities in ascending order of distance
                        std::sort(candidates.first.begin(), candidates.first.end(), [](const std::pair<int, double> &a, const std::pair<int, double> &b)
                                  { return a.second < b.second; });
                        std::sort(candidates.second.begin(), candidates.second.end(), [](const std::pair<int, double> &a, const std::pair<int, double> &b)
                                  { return a.second < b.second; });

                        // Check if a city without any spies exists
                        if (!candidates.first.empty())
                        {
                            current_city = candidates.first.front().first;
                            path.push_back(candidates.first.front().first);
                        }
                        else if (!candidates.second.empty())
                        {
                            spies_count++;
                            path.push_back(candidates.second.front().first);
                        }
                    }
                    else if (graph.get_city(closest_ec_id).get_defense_count() > 0)
                    {
                        if (spies_count >= 4)
                        {
                            graph.set_missile_count(a, "A1", 0);
                            graph.set_missile_count(a, "A2", 0);
                            ;
                            graph.set_missile_count(a, "A3", 0);
                            ;
                        }
                        else if (spies_count == 3)
                        {
                            graph.set_missile_count(a, "A1", 0);
                            ;
                            graph.set_missile_count(a, "A2", 0);
                            ;
                        }
                        else if (spies_count == 2)
                        {
                            graph.set_missile_count(a, "A2", 0);
                            ;
                        }
                        if ((graph.get_city(a).get_missile_stock().at("A1") * 100) + (graph.get_city(a).get_missile_stock().at("A2") * 130) + (graph.get_city(a).get_missile_stock().at("A3") * 25) != 0)
                        {
                            paths.push_back(path);
                        }
                        total_damage += (graph.get_city(a).get_missile_stock().at("A1") * 100) + (graph.get_city(a).get_missile_stock().at("A2") * 130) + (graph.get_city(a).get_missile_stock().at("A3") * 25);
                        break;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                continue;
            }
        }
    }
}

void Simulator::scenario_3() {}

void Simulator::scenario_4(std::vector<int> &abc_cities)
{
    std::vector<int> enemy_cities = graph.get_enemy_city_ids();
    std::vector<std::vector<int>> paths;

    for (const int &abc : abc_cities)
    {
        if (graph.get_city(abc).get_missile_count() > 0)
        {
            // Vector of enemy cities with their distances: (city_id, distance)
            std::vector<std::pair<int, double>> enemy_cities_with_distances;

            for (const int &ec : enemy_cities)
            {
                enemy_cities_with_distances.push_back({ec, graph.distance(abc, ec)});
            }

            // Sort ascending by distance
            std::sort(enemy_cities_with_distances.begin(), enemy_cities_with_distances.end(),
                      [](const std::pair<int, double> &a, const std::pair<int, double> &b)
                      {
                          return a.second < b.second; // compare by distance
                      });

            // Minimum missile range in the set
            int missile_min_range = 0;
            // A1 range = A2 range = A3 range / B1 range = B2 range / C range + 100 = C1 rang
            if (graph.get_city(abc).get_missile_stock().at("A1") > 0 ||
                graph.get_city(abc).get_missile_stock().at("A2") > 0 ||
                graph.get_city(abc).get_missile_stock().at("A3") > 0)
            {
                missile_min_range = missile_data.get_shahab7().get_range();
            }
            else if (graph.get_city(abc).get_missile_stock().at("C") > 0)
            {
                missile_min_range = missile_data.get_tondar85().get_range();
            }
            else if (graph.get_city(abc).get_missile_stock().at("C1") > 0)
            {
                missile_min_range = missile_data.get_said1().get_range();
            }
            else if (graph.get_city(abc).get_missile_stock().at("B1") > 0 ||
                     graph.get_city(abc).get_missile_stock().at("B2") > 0)
            {
                missile_min_range = missile_data.get_ghadr313().get_range();
            }

            // Closest enemy city: (city_id, distance)
            std::pair<int, double> closest_enemy_city;

            for (const auto &d : enemy_cities_with_distances)
            {
                if (d.second <= missile_min_range)
                {
                    closest_enemy_city = d;
                    break;
                }
                else
                {
                    continue;
                }
            }
        }
    }
}
