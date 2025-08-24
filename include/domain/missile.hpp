#ifndef MISSILE_HPP
#define MISSILE_HPP

#include <string>

class Missile
{
public:
    // Default constructor
    Missile();

    // Full constructor
    Missile(const std::string &name,
            double range,
            double uncontrolled_range,
            int stealth,
            int damage,
            const std::string &class_id);

    // Getters
    const std::string &get_name() const { return name; }
    double get_range() const { return range; }
    double get_uncontrolled_range() const { return uncontrolled_range; }
    int get_stealth() const { return stealth; }
    int get_damage() const { return damage; }
    const std::string &get_class_id() const { return class_id; }

    // Setters
    void set_name(const std::string &new_name);
    void set_range(double r);
    void set_uncontrolled_range(double r);
    void set_stealth(int s);
    void set_damage(int d);
    void set_class_id(const std::string &cls);

private:
    std::string name;
    double range;              // total range budget
    double uncontrolled_range; // max distance without passing a control point
    int stealth;               // radar-evading level
    int damage;                // inflicted damage on a successful hit
    std::string class_id;      // classification (A, B, C, D, ...)
};

#endif // MISSILE_HPP