#include "../../include/domain/missile.hpp"

#include <iostream>  

// Default constructor
Missile::Missile()
    : name(""), range(0), uncontrolled_range(0),
      stealth(0), damage(0), class_id("Unknown") {}

// Full constructor
Missile::Missile(const std::string &n, double r, double ur, int s, int d, const std::string &cls)
{
    set_name(n);
    set_range(r);
    set_uncontrolled_range(ur);
    set_stealth(s);
    set_damage(d);
    set_class_id(cls);
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