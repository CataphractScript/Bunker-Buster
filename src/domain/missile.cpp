#include "../include/domain/Missile.hpp"

// Default constructor
Missile::Missile()
    : name(""), range(0), uncontrolled_range(0),
      stealth(0), damage(0), class_id("Unknown") {}

// Full constructor
Missile::Missile(const std::string &name,
                 double range,
                 double uncontrolled_range,
                 int stealth,
                 int damage,
                 const std::string &class_id,
                 int start_city)
                 : name(name), range(0), uncontrolled_range(0),stealth(0), damage(0), class_id("Unknown")
{
    set_range(range);
    set_uncontrolled_range(uncontrolled_range);
    set_stealth(stealth);
    set_damage(damage);
    set_class_id(class_id);
}

// Setters with simple validation
void Missile::set_name(const std::string &new_name)
{
    if (!new_name.empty())
        name = new_name;
}

void Missile::set_range(double r)
{
    if (r >= 0)
        range = r;
}

void Missile::set_uncontrolled_range(double r)
{
    if (r >= 0)
        uncontrolled_range = r;
}

void Missile::set_stealth(int s)
{
    if (s >= 0)
        stealth = s;
}

void Missile::set_damage(int d)
{
    if (d >= 0)
        damage = d;
}

void Missile::set_class_id(const std::string &cls)
{
    if (!cls.empty())
        class_id = cls;
}