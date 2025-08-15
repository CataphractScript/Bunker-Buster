#include "../../include/domain/city.hpp"
#include <algorithm>
#include <cctype>

// Default constructor
City::City() : country(""), coordinates({ 0,0 }), city_status(Neutral), spy_count(0), defense_count(0) {}

// Constructor with validation via setters
City::City(const std::string& c, const std::pair<int, int>& coord, const std::string& status, int spies, int def) {
    set_country(c);
    set_coordinates(coord);
    set_city_status(status);
    set_spy_count(spies);
    set_defense_count(def);
}


std::string City::get_country() const { return country; }

void City::set_country(const std::string& newCountry) {
    if (!newCountry.empty() && newCountry.size() == 3) {
        country = newCountry;
        std::transform(country.begin(), country.end(), country.begin(),
            [](unsigned char c) { return std::toupper(c); });
    }
}


std::pair<int, int> City::get_coordinates() const { return coordinates; }

void City::set_coordinates(const std::pair<int, int>& newCoordinates) {
    coordinates = newCoordinates;
}


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


int City::get_spy_count() const { return spy_count; }

void City::set_spy_count(const int& newSpy_count) {
    if (newSpy_count >= 0) {
        spy_count = newSpy_count;
    }
}


int City::get_defense_count() const {
    return defense_count;
}

void City::set_defense_count(const int& newDefense_count) {
    defense_count = newDefense_count;
}
