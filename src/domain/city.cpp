#include "../../include/domain/city.hpp"
#include "../../include/domain/missile.hpp"

#include <iostream>
#include <algorithm>
#include <cctype>
#include <vector>

// Default constructor
City::City() : country(""), coordinates({ 0,0 }), city_status(Neutral), has_spy(false), defense_count(0), missiles(), missile_stock(), missile_count(0) {}

// Constructor with validation via setters
City::City(const std::string& country_in, const std::pair<int, int>& coord, const std::string& status, bool spy, int def, const std::vector<Missile>& missile_in, std::unordered_map<std::string, int> missile_stock_in) {
    set_country(country_in);
    set_coordinates(coord);
    set_city_status(status);
    set_has_spy(spy);
    set_defense_count(def);
    set_missiles(missile_in);
    set_missile_stock(missile_stock_in);

    for (const auto& pair : missile_stock_in) {
        missile_count += pair.second;
    }
}

// Implement getters and setters
std::string City::get_country() const { return country; }

void City::set_country(const std::string& new_country) {
    if (!new_country.empty() && new_country.size() == 3) {
        country = new_country;
        std::transform(country.begin(), country.end(), country.begin(),
            [](unsigned char c) { return std::toupper(c); });
    }
}

std::pair<int, int> City::get_coordinates() const { return coordinates; }

void City::set_coordinates(const std::pair<int, int>& new_coordinates) { coordinates = new_coordinates; }

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

void City::set_city_status(const std::string& new_city_status) {
    if (!new_city_status.empty()) {
        std::string lower = new_city_status;
        std::transform(lower.begin(), lower.end(), lower.begin(),
            [](unsigned char c) { return std::tolower(c); });

        if (lower == "friendly") city_status = Friendly;
        else if (lower == "neutral") city_status = Neutral;
        else if (lower == "enemy") city_status = Enemy;
        else city_status = Neutral; // default if invalid
    }
}

bool City::get_has_spy() const { return has_spy; }

void City::set_has_spy(const bool& new_spy) { has_spy = new_spy; }

int City::get_defense_count() const { return defense_count; }

void City::set_defense_count(const int& new_defense_count) { defense_count = new_defense_count; }

std::vector<Missile> City::get_missiles() const { return missiles; }

void City::set_missiles(const std::vector<Missile>& new_missiles) {
    missiles = new_missiles;
}

// std::unordered_map<std::string, int> City::get_missile_stock() const { return missile_stock; }
int City::get_missile_count_by_id(const std::string& key) const {
    auto it = missile_stock.find(key);
    if (it != missile_stock.end()) {
        return it->second;
    }
    return 0; // اگر کلید نبود
}

void City::set_missile_stock(std::unordered_map<std::string, int>& new_missile_stock) { missile_stock = new_missile_stock; }

void City::set_missile_count(std::string class_id, int number) { 
    missile_stock[class_id] = number;
    missile_count += number;
}

bool City::increment_missile_stock(const std::string& class_id) {
    auto it = missile_stock.find(class_id);
    if (it == missile_stock.end()) {
        std::cerr << "Error: missile class not found: " << class_id << "\n";
        return false;
    }
    ++it->second;
    ++missile_count;
    return true;
}

bool City::decrement_missile_stock(const std::string& class_id) {
    auto it = missile_stock.find(class_id);
    if (it == missile_stock.end()) {
        std::cerr << "Error: missile class not found: " << class_id << "\n";
        return false;
    }
    if (it->second <= 0) {
        std::cerr << "Error: missile stock empty for class: " << class_id << "\n";
        return false;
    }
    --it->second;
    if (missile_count > 0) --missile_count;
    return true;
}

int City::get_missile_count() const { return missile_count; }
