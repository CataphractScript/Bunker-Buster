#include "../../include/sim/simulator.hpp"
#include "../../include/domain/city.hpp"
#include "../../include/domain/missile.hpp"
#include "../../include/graph/graph.hpp"
#include <limits>
#include <algorithm>

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

    case 2:
        scenario_2();
        break;

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

void Simulator::scenario_2()
{
    /* code */
}
