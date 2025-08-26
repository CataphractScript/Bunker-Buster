#include "../../include/sim/simulator.hpp"
#include "../../include/domain/city.hpp"
#include "../../include/domain/missile.hpp"
#include "../../include/graph/graph.hpp"
#include "../../include/data/missile_data.hpp"

#include <tuple>
#include <limits>
#include <algorithm>
#include <utility>

// Constructor initializes total_damage to 0
Simulator::Simulator() : total_damage(0) {}

// Implement getters and setters
Graph Simulator::get_graph() const { return graph; }
void Simulator::set_graph(const Graph &g) { graph = g; }

std::vector<std::vector<int>> Simulator::get_paths() const { return paths; }

// Run the scenario corresponding to scenario_num
void Simulator::run(int scenario_num)
{
    switch (scenario_num)
    {
    case 1:
        paths = {};
        scenario_1();
        break;

    case 2:
        paths = {};
        scenario_2();
        break;

    // case 3:
    //     paths = {};
    //     scenario_3();
    //     break;

    case 4:
        paths = {};
        scenario_4();
        break;

    default:
        std::cout << "Invalid scenario number!" << std::endl;
        for (const std::vector<int> &path : paths) {
            for (const int &c : path) {
                std::cout << "{" << Simulator::graph.get_city(c).get_city_status_str() << ", "
                                 << Simulator::graph.get_city(c).get_country() << ", "
                                 << "(" << Simulator::graph.get_city(c).get_coordinates().first << "," << Simulator::graph.get_city(c).get_coordinates().second
                                 << "}";
            }
        }
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
}

void Simulator::scenario_2()
{
    std::vector<int> friendly_cities = graph.get_friendly_city_ids();
    std::vector<int> enemy_cities = graph.get_enemy_city_ids();
    std::vector<std::vector<int>> paths;

    for (const int &a : /*a_cities*/friendly_cities)
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

                // ...
                int sokht = 2500;

                while (true)
                {
                    // Check if the current city is not an enemy city
                    if (graph.get_city(current_city).get_city_status_int() != 3)
                    {
                        // Candidate cities for the missile's next move (Cities that don't have spies(ID, distance to start city, distance to enemy city), Cities that have spies(ID, distance to start city, distance to enemy city))
                        std::pair<std::vector<std::tuple<int, double, double>>, std::vector<std::tuple<int, double, double>>> candidates;
                        for (size_t i = 0; i < graph.city_count(); i++)
                        {
                            // Enemy city located west of the current city, within the uncontrolled range of Class A missiles (main conditions)
                            if (graph.get_city(i).get_coordinates().first <= graph.get_city(current_city).get_coordinates().first && graph.distance(current_city, i) < 500)
                            {
                                if (!graph.get_city(i).get_has_spy())
                                {
                                    candidates.first.push_back({i, graph.distance(current_city, i), graph.distance(closest_ec_id, i)});
                                }
                                else
                                {
                                    candidates.second.push_back({i, graph.distance(current_city, i), graph.distance(closest_ec_id, i)});
                                }
                            }
                            else
                            {
                                continue;
                            }
                        }
                        // Sort candidate cities in ascending order of distance
                        std::sort(candidates.first.begin(), candidates.first.end(), [](const std::tuple<int, double, double> &a, const std::tuple<int, double, double> &b)
                                  { return std::get<2>(a) < std::get<2>(b); });
                        std::sort(candidates.second.begin(), candidates.second.end(), [](const std::tuple<int, double, double> &a, const std::tuple<int, double, double> &b)
                                  { return std::get<2>(a) < std::get<2>(b); });
                        
                        // ...
                        if (sokht > 0)
                        {
                            // Check if a city without any spies exists
                            if (!candidates.first.empty())
                            {
                                current_city = std::get<0>(candidates.first.front());
                                path.push_back(std::get<0>(candidates.first.front()));
                                sokht -= std::get<1>(candidates.first.front());
                            }
                            else if (!candidates.second.empty())
                            {
                                spies_count++;
                                current_city = std::get<0>(candidates.second.front());
                                path.push_back(std::get<0>(candidates.second.front()));
                                sokht -= std::get<1>(candidates.first.front());
                            }                            
                        }
                        else
                        {
                            break;
                        }

                    }
                    else if (graph.get_city(closest_ec_id).get_defense_count() > 0)
                    {
                        if (spies_count >= 4)
                        {
                            graph.set_missile_count(a, "A1", 0);
                            graph.set_missile_count(a, "A2", 0);
                            graph.set_missile_count(a, "A3", 0);
                        }
                        else if (spies_count == 3)
                        {
                            graph.set_missile_count(a, "A1", 0);
                            graph.set_missile_count(a, "A2", 0);
                        }
                        else if (spies_count == 2)
                        {
                            graph.set_missile_count(a, "A2", 0);
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
        else 
        {
            continue;
        }
    }
}

void Simulator::scenario_3(std::unordered_map<std::string, int> missile_counts)
{
    std::vector<int> friendly_bases = graph.get_friendly_city_ids();
    std::vector<int> enemy_cities = graph.get_enemy_city_ids();

    load_missiles missile_db;

    // Utility: map string ID to correct missile object from database
    auto getMissileByType = [&](const std::string &type) -> const Missile &
    {
        if (type == "B1")
            return missile_db.get_ghadr313();
        if (type == "B2")
            return missile_db.get_tasua();
        if (type == "C1")
            return missile_db.get_said1();
        if (type == "C")
            return missile_db.get_tondar85();
        throw std::runtime_error("Unknown missile type: " + type);
    };

    struct Result
    {
        std::string missile_type;
        int base_id;
        int target_city = -1;
        bool hit_target = false;
        bool destroyed = false;
        bool detected = false;
        double total_distance = 0;
        double damage = 0;
        std::vector<int> path;
    };

    std::vector<Result> results;
    double total_damage = 0; // Total inflicted damage in this scenario

    // 🔹 Step 1: assign missiles (given in missile_counts) to friendly bases
    for (auto &[type, count] : missile_counts)
    {
        const Missile &m = getMissileByType(type);

        while (count-- > 0)
        {
            int best_base = -1, best_enemy = -1;
            double best_dis = std::numeric_limits<double>::max();

            // Find best base–enemy pair where missile can reach
            for (int base_id : friendly_bases)
            {
                for (int enemy_id : enemy_cities)
                {
                    double dis = graph.distance(base_id, enemy_id);
                    if (dis <= m.get_range() && dis < best_dis)
                    {
                        best_dis = dis;
                        best_base = base_id;
                        best_enemy = enemy_id;
                    }
                }
            }

            if (best_base == -1 || best_enemy == -1)
                continue;

            // Increment stock in chosen base
            City &base = graph.get_city(best_base);
            base.missile_stock_increment(type);

            Result res;
            res.missile_type = type;
            res.base_id = best_base;
            res.path.push_back(best_base);

            int current = best_base;
            bool reached = false;
            double traveled = 0;
            int stealth = m.get_stealth(); // local copy, decreases when seen by spies

            // 🔹 Step 2: try to route missile from base → enemy
            while (!reached)
            {
                int next_city = -1;
                double best_to_enemy = std::numeric_limits<double>::max();

                // Explore candidate next cities
                for (size_t i = 0; i < graph.city_count(); i++)
                {
                    if ((int)i == current)
                        continue;
                    double step = graph.distance(current, i);

                    // Must be within missile uncontrolled range
                    if (step <= m.get_uncontrolled_range())
                    {
                        // Direct hit possible
                        if (i == best_enemy)
                        {
                            next_city = i;
                            traveled += step;
                            res.path.push_back(i);
                            reached = true;
                            break;
                        }

                        // Otherwise choose city closer to enemy, prefer no spies
                        double d2enemy = graph.distance(i, best_enemy);
                        if (d2enemy < best_to_enemy ||
                            (d2enemy == best_to_enemy && !graph.get_city(i).get_has_spy()))
                        {
                            best_to_enemy = d2enemy;
                            next_city = i;
                        }
                    }
                }

                if (reached)
                    break;
                if (next_city == -1)
                    break; // No valid move → missile stuck

                traveled += graph.distance(current, next_city);
                current = next_city;
                res.path.push_back(current);

                City &c = graph.get_city(current);

                // Spy detection: each spy reduces stealth level by 1
                if (c.get_has_spy())
                {
                    stealth--;
                    if (stealth <= 0)
                        res.detected = true;
                }

                // Enemy defense: if missile is detected, defenses may shoot it down
                if (c.get_city_status_int() == Enemy && c.get_defense_count() > 0 && res.detected)
                {
                    c.set_defense_count(c.get_defense_count() - 1); // consume one defense unit
                    res.destroyed = true;
                    break;
                }
            }

            res.total_distance = traveled;
            res.target_city = reached ? best_enemy : -1;

            // Final outcome
            if (reached && !res.destroyed)
            {
                res.hit_target = true;
                res.damage = m.get_damage();
                total_damage += res.damage; // accumulate scenario-wide damage
            }

            results.push_back(res);
        }
    }
}

void Simulator::scenario_4()
{
    std::vector<int> friendly_cities = graph.get_friendly_city_ids();
    std::vector<int> enemy_cities = graph.get_enemy_city_ids();
    std::vector<std::vector<int>> paths;

    for (const int &fc : friendly_cities)
    {
        if (graph.get_city(fc).get_missile_count() > 0)
        {
            // Vector of enemy cities with their distances: (city_id, distance)
            std::vector<std::pair<int, double>> enemy_cities_with_distances;

            for (const int &ec : enemy_cities)
            {
                enemy_cities_with_distances.push_back({ec, graph.distance(fc, ec)});
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
            if (graph.get_city(fc).get_missile_stock().at("A1") > 0 ||
                graph.get_city(fc).get_missile_stock().at("A2") > 0 ||
                graph.get_city(fc).get_missile_stock().at("A3") > 0)
            {
                missile_min_range = missile_data.get_shahab7().get_range();
            }
            else if (graph.get_city(fc).get_missile_stock().at("C") > 0)
            {
                missile_min_range = missile_data.get_tondar85().get_range();
            }
            else if (graph.get_city(fc).get_missile_stock().at("C1") > 0)
            {
                missile_min_range = missile_data.get_said1().get_range();
            }
            else if (graph.get_city(fc).get_missile_stock().at("B1") > 0 ||
                     graph.get_city(fc).get_missile_stock().at("B2") > 0)
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
