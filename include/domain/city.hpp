#pragma once

#include "missile.hpp"

#include <string>
#include <utility>

enum c_status {Friendly = 1, Neutral, Enemy};

class City {
    private:
        std::string country; // Country code (3 letters, uppercase)
        std::pair<int, int> coordinates;
        c_status city_status;
        bool has_spy;
        int defense_count;
        std::vector<Missile> missiles;
        std::vector<std::vector<std::pair<Missile, int>>> missiles_t; // test -> {missile, id} (id -> A1, A2, B1, ...)
        int missile_count;


    public:
        // Default constructor
        City();

        // Constructor with parameters
        City(const std::string& country_in, const std::pair<int, int>& coord, const std::string& status, bool spy, int def, const std::vector<Missile>& missile_in, const std::vector<std::vector<std::pair<Missile, int>>>& missile_in_t);

        // Getters and setters
        std::string get_country() const;
        void set_country(const std::string& newCountry);

        std::pair<int, int> get_coordinates() const;
        void set_coordinates(const std::pair<int, int>& newCoordinates);

        int get_city_status_int() const;
        std::string get_city_status_str() const;
        void set_city_status(const std::string& newCity_status);

        bool get_has_spy() const;
        void set_has_spy(const bool& newSpy);

        int get_defense_count() const;
        void set_defense_count(const int& newDefense_count);

        std::vector<Missile> get_missiles() const;
        void set_missiles(const std::vector<Missile>& newMissiles);

        std::vector<std::vector<std::pair<Missile, int>>> get_missiles_t() const;
        void set_missiles_t(const std::vector<std::vector<std::pair<Missile, int>>>& newMissiles_t); 

        int get_missile_count() const;
        void set_missile_count(const int& newMissile_count); 
};