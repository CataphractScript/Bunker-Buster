#include "../../include/domain/city.hpp"
#include "../../include/domain/missile.hpp"

#include <algorithm>
#include <cctype>
#include <vector>

// Default constructor
City::City() : country(""), coordinates({ 0,0 }), city_status(Neutral), has_spy(false), defense_count(0), missiles(), missile_count(0) {}

// Constructor with validation via setters
City::City(const std::string& country_in, const std::pair<int, int>& coord, const std::string& status, bool spy, int def, const std::vector<Missile>& missile_in) {
    set_country(country_in);
    set_coordinates(coord);
    set_city_status(status);
    set_has_spy(spy);
    set_defense_count(def);
    set_missiles(missile_in);
}

// Implement getters and setters
std::string City::get_country() const { return country; }

void City::set_country(const std::string& newCountry) {
    if (!newCountry.empty() && newCountry.size() == 3) {
        country = newCountry;
        std::transform(country.begin(), country.end(), country.begin(),
            [](unsigned char c) { return std::toupper(c); });
    }
}

std::pair<int, int> City::get_coordinates() const { return coordinates; }
void City::set_coordinates(const std::pair<int, int>& newCoordinates) { coordinates = newCoordinates; }

int City::get_city_status_int() const {
    return static_cast<int>(city_status); // static_cast: Modern C++ cast for safe and explicit type conversion
}

std::string City::get_city_status_str() const {
    switch (city_status) {
    case Friendly: return "Friendly";
    case Neutral: return "Neutral";
    case Enemy: return "Enemy";
    default: return "Unknown";
    }
}

void City::set_city_status(const std::string& newCity_status) {
    if (!newCity_status.empty()) {
        std::string lower = newCity_status;
        std::transform(lower.begin(), lower.end(), lower.begin(),
            [](unsigned char c) { return std::tolower(c); });

        if (lower == "friendly") city_status = Friendly;
        else if (lower == "neutral") city_status = Neutral;
        else if (lower == "enemy") city_status = Enemy;
        else city_status = Neutral; // default if invalid
    }
}

bool City::get_has_spy() const { return has_spy; }
void City::set_has_spy(const bool& newSpy) { has_spy = newSpy; }

int City::get_defense_count() const { return defense_count; }
void City::set_defense_count(const int& newDefense_count) { defense_count = newDefense_count; }

std::vector<Missile> City::get_missiles() const { return missiles; }
void City::set_missiles(const std::vector<Missile>& newMissiles) {
    missiles = newMissiles;
    missile_count = newMissiles.size();
}

int City::get_missile_count() const { return missile_count; }
