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
                    {missiles.get_sangar_shekan(), missiles.get_sangar_shekan()}, {{"D1", 2}}));

    g.add_city(City("IRN", {550, 650}, "friendly", false, 0,
                    {missiles.get_sangar_shekan(), missiles.get_sangar_shekan()}, {{"D1", 2}}));

    g.add_city(City("IRN", {600, 720}, "friendly", false, 0,
                    {missiles.get_sangar_shekan(), missiles.get_sangar_shekan()}, {{"D1", 2}}));

    g.add_city(City("IRN", {480, 780}, "friendly", false, 0,
                    {missiles.get_sangar_shekan(), missiles.get_sangar_shekan()}, {{"D1", 2}}));

    g.add_city(City("IRN", {620, 680}, "friendly", false, 0,
                    {missiles.get_sangar_shekan(), missiles.get_sangar_shekan()}, {{"D1", 2}}));

    g.add_city(City("IRN", {580, 600}, "friendly", false, 0,
                    {missiles.get_sangar_shekan(), missiles.get_sangar_shekan()}, {{"D1", 2}}));

    g.add_city(City("IRN", {650, 750}, "friendly", false, 0,
                    {missiles.get_sangar_shekan(), missiles.get_sangar_shekan()}, {{"D1", 2}}));

    g.add_city(City("IRN", {52, 80}, "friendly", false, 0,
                    {missiles.get_sangar_shekan(), missiles.get_sangar_shekan()}, {{"D1", 2}}));

    // -------- IRAQ (Neutral) --------
    g.add_city(City("IRQ", {400, 620}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("IRQ", {420, 580}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("IRQ", {380, 550}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("IRQ", {360, 600}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("IRQ", {440, 640}, "neutral", false, 0, {}, empty_stock()));

    // -------- SYRIA (Neutral) --------
    g.add_city(City("SYR", {300, 700}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("SYR", {280, 680}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("SYR", {32, 650}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("SYR", {260, 720}, "neutral", false, 0, {}, empty_stock()));

    // -------- LEBANON (Neutral) --------
    g.add_city(City("LBN", {220, 730}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("LBN", {200, 700}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("LBN", {180, 740}, "neutral", false, 0, {}, empty_stock()));

    // -------- JORDAN (Neutral) --------
    g.add_city(City("JOR", {280, 550}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("JOR", {300, 520}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("JOR", {260, 500}, "neutral", false, 0, {}, empty_stock()));

    // -------- ISRAEL (Enemy) --------
    g.add_city(City("ISR", {240, 480}, "enemy", false, 5, {}, empty_stock()));
    g.add_city(City("ISR", {220, 460}, "enemy", false, 10, {}, empty_stock()));
    g.add_city(City("ISR", {260, 440}, "enemy", false, 8, {}, empty_stock()));
    g.add_city(City("ISR", {200, 400}, "enemy", false, 0, {}, empty_stock()));
    g.add_city(City("ISR", {280, 420}, "enemy", false, 2, {}, empty_stock()));
    g.add_city(City("ISR", {250, 380}, "enemy", false, 4, {}, empty_stock()));

    // Compute adjacency matrix after all cities are added
    g.compute_adjacency_matrix();

    return g;
}

Graph load_graph_for_scenario2()
{
    Graph g;
    load_missiles missiles;

    // -------- IRAN (Friendly) --------
    g.add_city(City("IRN", {500, 700}, "friendly", false, 0,
                    {}, {{"A1", 3}, {"A3", 1}}));

    g.add_city(City("IRN", {550, 650}, "friendly", false, 0,
                    {}, {{"A1", 1}, {"A3", 3}}));

    g.add_city(City("IRN", {600, 720}, "friendly", false, 0,
                    {}, empty_stock()));

    g.add_city(City("IRN", {480, 780}, "friendly", false, 0,
                    {}, empty_stock()));

    g.add_city(City("IRN", {620, 680}, "friendly", false, 0,
                    {}, {{"A2", 2}, {"A3", 1}}));

    g.add_city(City("IRN", {580, 600}, "friendly", false, 0,
                    {}, empty_stock()));

    g.add_city(City("IRN", {650, 750}, "friendly", false, 0,
                    {}, empty_stock()));

    g.add_city(City("IRN", {52, 80}, "friendly", false, 0,
                    {}, {{"A1", 4}, {"A2", 1}}));

    // -------- IRAQ (Neutral) --------
    g.add_city(City("IRQ", {400, 620}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("IRQ", {420, 580}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("IRQ", {380, 550}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("IRQ", {360, 600}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("IRQ", {440, 640}, "neutral", false, 0, {}, empty_stock()));

    // -------- SYRIA (Neutral) --------
    g.add_city(City("SYR", {300, 700}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("SYR", {280, 680}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("SYR", {32, 650}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("SYR", {260, 720}, "neutral", false, 0, {}, empty_stock()));

    // -------- LEBANON (Neutral) --------
    g.add_city(City("LBN", {220, 730}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("LBN", {200, 700}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("LBN", {180, 740}, "neutral", false, 0, {}, empty_stock()));

    // -------- JORDAN (Neutral) --------
    g.add_city(City("JOR", {280, 550}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("JOR", {300, 520}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("JOR", {260, 500}, "neutral", false, 0, {}, empty_stock()));

    // -------- ISRAEL (Enemy) --------
    g.add_city(City("ISR", {240, 480}, "enemy", false, 5, {}, empty_stock()));
    g.add_city(City("ISR", {220, 460}, "enemy", false, 10, {}, empty_stock()));
    g.add_city(City("ISR", {260, 440}, "enemy", false, 8, {}, empty_stock()));
    g.add_city(City("ISR", {200, 400}, "enemy", false, 0, {}, empty_stock()));
    g.add_city(City("ISR", {280, 420}, "enemy", false, 2, {}, empty_stock()));
    g.add_city(City("ISR", {250, 380}, "enemy", false, 4, {}, empty_stock()));

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
                    {}, empty_stock()));

    g.add_city(City("IRN", {550, 650}, "friendly", false, 0,
                    {}, empty_stock()));

    g.add_city(City("IRN", {600, 720}, "friendly", false, 0,
                    {}, empty_stock()));

    g.add_city(City("IRN", {480, 780}, "friendly", false, 0,
                    {}, empty_stock()));

    g.add_city(City("IRN", {620, 680}, "friendly", false, 0,
                    {}, empty_stock()));

    g.add_city(City("IRN", {580, 600}, "friendly", false, 0,
                    {}, empty_stock()));

    g.add_city(City("IRN", {650, 750}, "friendly", false, 0,
                    {}, empty_stock()));

    g.add_city(City("IRN", {52, 80}, "friendly", false, 0,
                    {}, empty_stock()));

    // -------- IRAQ (Neutral) --------
    g.add_city(City("IRQ", {400, 620}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("IRQ", {420, 580}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("IRQ", {380, 550}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("IRQ", {360, 600}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("IRQ", {440, 640}, "neutral", false, 0, {}, empty_stock()));

    // -------- SYRIA (Neutral) --------
    g.add_city(City("SYR", {300, 700}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("SYR", {280, 680}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("SYR", {32, 650}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("SYR", {260, 720}, "neutral", false, 0, {}, empty_stock()));

    // -------- LEBANON (Neutral) --------
    g.add_city(City("LBN", {220, 730}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("LBN", {200, 700}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("LBN", {180, 740}, "neutral", false, 0, {}, empty_stock()));

    // -------- JORDAN (Neutral) --------
    g.add_city(City("JOR", {280, 550}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("JOR", {300, 520}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("JOR", {260, 500}, "neutral", false, 0, {}, empty_stock()));

    // -------- ISRAEL (Enemy) --------
    g.add_city(City("ISR", {240, 480}, "enemy", false, 5, {}, empty_stock()));
    g.add_city(City("ISR", {220, 460}, "enemy", false, 10, {}, empty_stock()));
    g.add_city(City("ISR", {260, 440}, "enemy", false, 8, {}, empty_stock()));
    g.add_city(City("ISR", {200, 400}, "enemy", false, 0, {}, empty_stock()));
    g.add_city(City("ISR", {280, 420}, "enemy", false, 2, {}, empty_stock()));
    g.add_city(City("ISR", {250, 380}, "enemy", false, 4, {}, empty_stock()));

    // Compute adjacency matrix after all cities are added
    g.compute_adjacency_matrix();

    return g;
}

Graph load_graph_for_scenario4()
{
    Graph g;
    load_missiles missiles;

    // -------- IRAN (Friendly) --------
    g.add_city(City("IRN", {500, 700}, "friendly", false, 0,
                    {}, {{"A2", 2}, {"B2", 4}, {"C1", 1}}));

    g.add_city(City("IRN", {550, 650}, "friendly", false, 0,
                    {}, {{"A1", 3}, {"B2", 1}, {"C", 3}}));

    g.add_city(City("IRN", {600, 720}, "friendly", false, 0,
                    {}, empty_stock()));

    g.add_city(City("IRN", {480, 780}, "friendly", false, 0,
                    {}, empty_stock()));

    g.add_city(City("IRN", {620, 680}, "friendly", false, 0,
                    {}, empty_stock()));

    g.add_city(City("IRN", {580, 600}, "friendly", false, 0,
                    {}, {{"A3", 3}, {"B1", 1}, {"C1", 5}}));

    g.add_city(City("IRN", {650, 750}, "friendly", false, 0,
                    {}, empty_stock()));

    g.add_city(City("IRN", {52, 80}, "friendly", false, 0,
                    {}, {{"A2", 5}, {"B1", 6}, {"C", 2}}));

    // -------- IRAQ (Neutral) --------
    g.add_city(City("IRQ", {400, 620}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("IRQ", {420, 580}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("IRQ", {380, 550}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("IRQ", {360, 600}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("IRQ", {440, 640}, "neutral", false, 0, {}, empty_stock()));

    // -------- SYRIA (Neutral) --------
    g.add_city(City("SYR", {300, 700}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("SYR", {280, 680}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("SYR", {32, 650}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("SYR", {260, 720}, "neutral", false, 0, {}, empty_stock()));

    // -------- LEBANON (Neutral) --------
    g.add_city(City("LBN", {220, 730}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("LBN", {200, 700}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("LBN", {180, 740}, "neutral", false, 0, {}, empty_stock()));

    // -------- JORDAN (Neutral) --------
    g.add_city(City("JOR", {280, 550}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("JOR", {300, 520}, "neutral", false, 0, {}, empty_stock()));
    g.add_city(City("JOR", {260, 500}, "neutral", false, 0, {}, empty_stock()));

    // -------- ISRAEL (Enemy) --------
    g.add_city(City("ISR", {240, 480}, "enemy", false, 5, {}, empty_stock()));
    g.add_city(City("ISR", {220, 460}, "enemy", false, 5, {}, empty_stock()));
    g.add_city(City("ISR", {260, 440}, "enemy", false, 8, {}, empty_stock()));
    g.add_city(City("ISR", {200, 400}, "enemy", false, 4, {}, empty_stock()));
    g.add_city(City("ISR", {280, 420}, "enemy", false, 2, {}, empty_stock()));
    g.add_city(City("ISR", {250, 380}, "enemy", false, 4, {}, empty_stock()));

    // Compute adjacency matrix after all cities are added
    g.compute_adjacency_matrix();

    return g;
}