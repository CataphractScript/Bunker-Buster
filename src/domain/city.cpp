#include "../include/domain/city.hpp"
#include <algorithm>
#include <cctype>

// Default constructor
city::city() : country(""), coordinates({ 0,0 }), city_status(Neutral), spy_count(0) {}

// Constructor with validation via setters
city::city(const std::string& c, const std::pair<int, int>& coord, const std::string& status, int spies) {
    set_country(c);
    set_coordinates(coord);
    set_city_status(status);
    set_spy_count(spies);
}


std::string city::get_country() const { return country; }

void city::set_country(const std::string& newCountry) {
    if (!newCountry.empty() && newCountry.size() == 3) {
        country = newCountry;
        std::transform(country.begin(), country.end(), country.begin(),
            [](unsigned char c) { return std::toupper(c); });
    }
}


std::pair<int, int> city::get_coordinates() const { return coordinates; }

void city::set_coordinates(const std::pair<int, int>& newCoordinates) {
    coordinates = newCoordinates;
}


int city::get_city_status_int() const {
    return static_cast<int>(city_status); // static_cast: Modern C++ cast for safe and explicit type conversion
}

std::string city::get_city_status_str() const {
    switch (city_status) {
    case Friendly: return "Friendly";
    case Neutral: return "Neutral";
    case Enemy: return "Enemy";
    default: return "Unknown";
    }
}

void city::set_city_status(const std::string& newCity_status) {
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


int city::get_spy_count() const { return spy_count; }

void city::set_spy_count(const int& newSpy_count) {
    if (newSpy_count >= 0) {
        spy_count = newSpy_count;
    }
}
