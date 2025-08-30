#include "../../include/data/graph_data.hpp"
#include "../../include/domain/missile.hpp"
#include "../../include/graph/graph.hpp"
#include "../../include/data/missile_data.hpp"

#include <unordered_map>
#include <vector>
#include <limits>

static std::unordered_map<std::string, int> empty_stock() { return {}; }

Graph load_graph_for_scenario1()
{
    Graph g;
    load_missiles missiles;

    // -------- IRAN (Friendly) --------
    g.add_city(City("IRN", {500, 700}, "friendly", false, 0,
                    {missiles.get_sangar_shekan(), missiles.get_sangar_shekan()}, {{"D1", 2}}, 2));

    g.add_city(City("IRN", {550, 650}, "friendly", false, 0,
                    {missiles.get_sangar_shekan(), missiles.get_sangar_shekan()}, {{"D1", 2}}, 2));

    g.add_city(City("IRN", {600, 720}, "friendly", false, 0,
                    {missiles.get_sangar_shekan(), missiles.get_sangar_shekan()}, {{"D1", 2}}, 2));

    g.add_city(City("IRN", {480, 780}, "friendly", false, 0,
                    {missiles.get_sangar_shekan(), missiles.get_sangar_shekan()}, {{"D1", 2}}, 2));

    g.add_city(City("IRN", {620, 680}, "friendly", false, 0,
                    {missiles.get_sangar_shekan(), missiles.get_sangar_shekan()}, {{"D1", 2}}, 2));

    g.add_city(City("IRN", {580, 600}, "friendly", false, 0,
                    {missiles.get_sangar_shekan(), missiles.get_sangar_shekan()}, {{"D1", 2}}, 2));

    g.add_city(City("IRN", {650, 750}, "friendly", false, 0,
                    {missiles.get_sangar_shekan(), missiles.get_sangar_shekan()}, {{"D1", 2}}, 2));

    g.add_city(City("IRN", {52, 80}, "friendly", false, 0,
                    {missiles.get_sangar_shekan(), missiles.get_sangar_shekan()}, {{"D1", 2}}, 2));

    // -------- IRAQ (Neutral) --------
    g.add_city(City("IRQ", {400, 620}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("IRQ", {420, 580}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("IRQ", {380, 550}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("IRQ", {360, 600}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("IRQ", {440, 640}, "neutral", false, 0, {}, empty_stock(), 0));

    // -------- SYRIA (Neutral) --------
    g.add_city(City("SYR", {300, 700}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("SYR", {280, 680}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("SYR", {32, 650}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("SYR", {260, 720}, "neutral", false, 0, {}, empty_stock(), 0));

    // -------- LEBANON (Neutral) --------
    g.add_city(City("LBN", {220, 730}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("LBN", {200, 700}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("LBN", {180, 740}, "neutral", false, 0, {}, empty_stock(), 0));

    // -------- JORDAN (Neutral) --------
    g.add_city(City("JOR", {280, 550}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("JOR", {300, 520}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("JOR", {260, 500}, "neutral", false, 0, {}, empty_stock(), 0));

    // -------- ISRAEL (Enemy) --------
    g.add_city(City("ISR", {240, 480}, "enemy", false, 5, {}, empty_stock(), 0));
    g.add_city(City("ISR", {220, 460}, "enemy", false, 10, {}, empty_stock(), 0));
    g.add_city(City("ISR", {260, 440}, "enemy", false, 8, {}, empty_stock(), 0));
    g.add_city(City("ISR", {200, 400}, "enemy", false, 0, {}, empty_stock(), 0));
    g.add_city(City("ISR", {280, 420}, "enemy", false, 2, {}, empty_stock(), 0));
    g.add_city(City("ISR", {250, 380}, "enemy", false, 4, {}, empty_stock(), 0));

    // Compute adjacency matrix after all cities are added
    g.compute_adjacency_matrix();

    return g;
}

// Graph load_graph_for_scenario2()
// {
//     Graph g;
//     load_missiles missiles;

//     // -------- IRAN (Friendly) --------
//     g.add_city(City("IRN", {500, 1000}, "friendly", false, 0,
//                     {}, {{"A1", 3}, {"A3", 2}}, 5));

//     // -------- IRAQ (Neutral) --------
//     g.add_city(City("IRQ", {400, 900}, "neutral", false, 0, {}, empty_stock(), 0));


//     // -------- SYRIA (Neutral) --------
//     g.add_city(City("SYR", {300, 800}, "neutral", false, 0, {}, empty_stock(), 0));

//     // -------- LEBANON (Neutral) --------
//     g.add_city(City("LBN", {200, 700}, "neutral", false, 0, {}, empty_stock(), 0));

//     // -------- JORDAN (Neutral) --------
//     g.add_city(City("JOR", {100, 500}, "neutral", false, 0, {}, empty_stock(), 0));
//     g.add_city(City("JOR", {50, 300}, "neutral", false, 0, {}, empty_stock(), 0));    


//     // -------- ISRAEL (Enemy) --------
//     g.add_city(City("ISR", {0, 0}, "enemy", false, 0, {}, empty_stock(), 0));

//     // Compute adjacency matrix after all cities are added
//     g.compute_adjacency_matrix();

//     return g;
// }

Graph load_graph_for_scenario2()
{
    Graph g;
    load_missiles missiles;

    // -------- IRAN (Friendly) --------
    g.add_city(City("IRN", {500, 700}, "friendly", false, 0,
                    {}, {{"A1", 3}, {"A3", 1}}, 4));

    g.add_city(City("IRN", {550, 650}, "friendly", false, 0,
                    {}, {{"A1", 1}, {"A3", 3}}, 4));

    g.add_city(City("IRN", {600, 720}, "friendly", false, 0,
                    {}, empty_stock(), 0));

    g.add_city(City("IRN", {480, 780}, "friendly", false, 0,
                    {}, empty_stock(), 0));

    g.add_city(City("IRN", {620, 680}, "friendly", false, 0,
                    {}, {{"A2", 2}, {"A3", 1}}, 3));

    g.add_city(City("IRN", {580, 600}, "friendly", false, 0,
                    {}, empty_stock(), 0));

    g.add_city(City("IRN", {650, 750}, "friendly", false, 0,
                    {}, empty_stock(), 0));


    // -------- IRAQ (Neutral) --------
    g.add_city(City("IRQ", {400, 520}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("IRQ", {420, 540}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("IRQ", {380, 560}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("IRQ", {360, 574}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("IRQ", {440, 523}, "neutral", false, 0, {}, empty_stock(), 0));

    // -------- SYRIA (Neutral) --------
    g.add_city(City("SYR", {300, 487}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("SYR", {330, 465}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("SYR", {308, 400}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("SYR", {340, 478}, "neutral", false, 0, {}, empty_stock(), 0));

    // -------- LEBANON (Neutral) --------
    g.add_city(City("LBN", {220, 330}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("LBN", {200, 301}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("LBN", {180, 304}, "neutral", false, 0, {}, empty_stock(), 0));

    // -------- JORDAN (Neutral) --------
    g.add_city(City("JOR", {190, 204}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("JOR", {168, 205}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("JOR", {180, 200}, "neutral", false, 0, {}, empty_stock(), 0));

    // -------- ISRAEL (Enemy) --------
    g.add_city(City("ISR", {55, 110}, "enemy", false, 5, {}, empty_stock(), 0));
    g.add_city(City("ISR", {90, 100}, "enemy", false, 10, {}, empty_stock(), 0));
    g.add_city(City("ISR", {96, 125}, "enemy", false, 8, {}, empty_stock(), 0));
    g.add_city(City("ISR", {70, 148}, "enemy", false, 0, {}, empty_stock(), 0));
    g.add_city(City("ISR", {74, 140}, "enemy", false, 2, {}, empty_stock(), 0));
    g.add_city(City("ISR", {29, 180}, "enemy", false, 4, {}, empty_stock(), 0));

    // Compute adjacency matrix after all cities are added
    g.compute_adjacency_matrix();

    return g;
}

Graph load_graph_for_scenario3()
{
    Graph g;
    load_missiles missiles;

    // -------- IRAN (Friendly) --------
    g.add_city(City("IRN", {500, 700}, "friendly", false, 0,
                    {}, empty_stock(), 0));

    g.add_city(City("IRN", {550, 650}, "friendly", false, 0,
                    {}, empty_stock(), 0));

    g.add_city(City("IRN", {600, 720}, "friendly", false, 0,
                    {}, empty_stock(), 0));

    g.add_city(City("IRN", {480, 780}, "friendly", false, 0,
                    {}, empty_stock(), 0));

    g.add_city(City("IRN", {620, 680}, "friendly", false, 0,
                    {}, empty_stock(), 0));

    g.add_city(City("IRN", {580, 600}, "friendly", false, 0,
                    {}, empty_stock(), 0));

    g.add_city(City("IRN", {650, 750}, "friendly", false, 0,
                    {}, empty_stock(), 0));

    g.add_city(City("IRN", {52, 80}, "friendly", false, 0,
                    {}, empty_stock(), 0));

    // -------- IRAQ (Neutral) --------
    g.add_city(City("IRQ", {400, 620}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("IRQ", {420, 580}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("IRQ", {380, 550}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("IRQ", {360, 600}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("IRQ", {440, 640}, "neutral", false, 0, {}, empty_stock(), 0));

    // -------- SYRIA (Neutral) --------
    g.add_city(City("SYR", {300, 700}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("SYR", {280, 680}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("SYR", {32, 650}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("SYR", {260, 720}, "neutral", false, 0, {}, empty_stock(), 0));

    // -------- LEBANON (Neutral) --------
    g.add_city(City("LBN", {220, 730}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("LBN", {200, 700}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("LBN", {180, 740}, "neutral", false, 0, {}, empty_stock(), 0));

    // -------- JORDAN (Neutral) --------
    g.add_city(City("JOR", {280, 550}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("JOR", {300, 520}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("JOR", {260, 500}, "neutral", false, 0, {}, empty_stock(), 0));

    // -------- ISRAEL (Enemy) --------
    g.add_city(City("ISR", {240, 480}, "enemy", false, 5, {}, empty_stock(), 0));
    g.add_city(City("ISR", {220, 460}, "enemy", false, 10, {}, empty_stock(), 0));
    g.add_city(City("ISR", {260, 440}, "enemy", false, 8, {}, empty_stock(), 0));
    g.add_city(City("ISR", {200, 400}, "enemy", false, 0, {}, empty_stock(), 0));
    g.add_city(City("ISR", {280, 420}, "enemy", false, 2, {}, empty_stock(), 0));
    g.add_city(City("ISR", {250, 380}, "enemy", false, 4, {}, empty_stock(), 0));

    // Compute adjacency matrix after all cities are added
    g.compute_adjacency_matrix();

    return g;
}

Graph load_graph_for_scenario4()
{
    Graph g;
    load_missiles missiles;

    // -------- IRAN (Friendly) --------
    g.add_city(City("IRN", {800, 1000}, "friendly", false, 0,
                    {}, {{"A2", 2}, {"B2", 4}, {"C1", 1}}, 7));

    g.add_city(City("IRN", {550, 800}, "friendly", false, 0,
                    {}, {{"A1", 3}, {"B2", 1}, {"C", 3}}, 7));

    g.add_city(City("IRN", {600, 900}, "friendly", false, 0,
                    {}, empty_stock(), 0));

    g.add_city(City("IRN", {480, 780}, "friendly", false, 0,
                    {}, empty_stock(), 0));

    g.add_city(City("IRN", {620, 850}, "friendly", false, 0,
                    {}, empty_stock(), 0));

    g.add_city(City("IRN", {580, 700}, "friendly", false, 0,
                    {}, {{"A3", 3}, {"B1", 1}, {"C1", 5}}, 9));

    g.add_city(City("IRN", {650, 750}, "friendly", false, 0,
                    {}, empty_stock(), 0));

    g.add_city(City("IRN", {580, 956}, "friendly", false, 0,
                    {}, {{"A2", 5}, {"B1", 6}, {"C", 2}}, 13));

    // -------- IRAQ (Neutral) --------
    g.add_city(City("IRQ", {400, 700}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("IRQ", {420, 654}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("IRQ", {380, 550}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("IRQ", {360, 600}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("IRQ", {440, 640}, "neutral", false, 0, {}, empty_stock(), 0));

    // -------- SYRIA (Neutral) --------
    g.add_city(City("SYR", {300, 600}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("SYR", {280, 547}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("SYR", {310, 550}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("SYR", {260, 600}, "neutral", false, 0, {}, empty_stock(), 0));

    // -------- LEBANON (Neutral) --------
    g.add_city(City("LBN", {200, 500}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("LBN", {125, 450}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("LBN", {210, 440}, "neutral", false, 0, {}, empty_stock(), 0));

    // -------- JORDAN (Neutral) --------
    g.add_city(City("JOR", {299, 599}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("JOR", {238, 560}, "neutral", false, 0, {}, empty_stock(), 0));
    g.add_city(City("JOR", {300, 480}, "neutral", false, 0, {}, empty_stock(), 0));

    // -------- ISRAEL (Enemy) --------
    g.add_city(City("ISR", {100, 300}, "enemy", false, 5, {}, empty_stock(), 0));
    g.add_city(City("ISR", {150, 257}, "enemy", false, 5, {}, empty_stock(), 0));
    g.add_city(City("ISR", {154, 269}, "enemy", false, 3, {}, empty_stock(), 0));
    g.add_city(City("ISR", {136, 287}, "enemy", false, 4, {}, empty_stock(), 0));
    g.add_city(City("ISR", {121, 300}, "enemy", false, 2, {}, empty_stock(), 0));
    g.add_city(City("ISR", {0, 0}, "enemy", false, 4, {}, empty_stock(), 0));

    // Compute adjacency matrix after all cities are added
    g.compute_adjacency_matrix();

    return g;
}