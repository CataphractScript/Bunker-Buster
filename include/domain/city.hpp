#pragma once

#include "missile.hpp"

#include <vector>
#include <string>
#include <utility>
#include <unordered_map>

enum c_status {Friendly = 1, Neutral, Enemy};

class City {
    private:
        std::string country; // Country code (3 letters, uppercase)
        std::pair<int, int> coordinates;
        c_status city_status;
        bool has_spy;
        int defense_count;
        std::vector<Missile> missiles;
        std::unordered_map<std::string, int> missile_stock; // Missile inventory: (missile_class_id, count)
        int missile_count;

    public:
        // Default constructor
        City();

        // Constructor with parameters
        City(const std::string& country_in, const std::pair<int, int>& coord, const std::string& status, bool spy, int def, const std::vector<Missile>& missile_in, std::unordered_map<std::string, int> missile_stock_in, int missile_count_in);

        // Getters and setters
        std::string get_country() const;
        void set_country(const std::string& new_country);

        std::pair<int, int> get_coordinates() const;
        void set_coordinates(const std::pair<int, int>& new_coordinates);

        int get_city_status_int() const;
        std::string get_city_status_str() const;
        void set_city_status(const std::string& new_city_status);

        bool get_has_spy() const;
        void set_has_spy(const bool& new_spy);

        int get_defense_count() const;
        void set_defense_count(const int& new_defense_count);

        std::vector<Missile> get_missiles() const;
        void set_missiles(const std::vector<Missile>& new_missiles);

        // std::unordered_map<std::string, int> get_missile_stock() const;
        int get_missile_count_by_id(const std::string& key) const;

        void set_missile_stock(std::unordered_map<std::string, int>& new_missile_stock);
        void set_missile_count(std::string class_id, int number); // Set the missile count for a given missile class
        bool increment_missile_stock(const std::string& class_id);
        bool decrement_missile_stock(const std::string& class_id);

        int get_missile_count() const;
};