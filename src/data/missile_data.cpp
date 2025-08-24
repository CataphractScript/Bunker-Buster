#include "../../include/data/missile_data.hpp"

#include <limits>

load_missiles::load_missiles()
    : Shahab7("Shahab7", 2500, 500, 3, 100, "A1"),
      Sejid("Sejid", 2500, 500, 4, 25, "A3"),
      Hormuz3("Hormuz3", 2500, 500, 2, 130, "A2"),
      Ghadr313("Ghadr313", 5000, 500, 2, 90, "B1"),
      Tasua("Tasua", 5000, 500, 0, 300, "B2"),
      Said1("Said1", 3000, 700, 2, 110, "C1"),
      Tondar85("Tondar85", 2900, 900, 1, 10, "C"),
      SangarShekan("SangarShekan", std::numeric_limits<int>::max(), 500, 2, 1488, "D1")
{}

const Missile& load_missiles::get_shahab7() const { return Shahab7; }
const Missile& load_missiles::get_sejid() const { return Sejid; }
const Missile& load_missiles::get_hormuz3() const { return Hormuz3; }
const Missile& load_missiles::get_ghadr313() const { return Ghadr313; }
const Missile& load_missiles::get_tasua() const { return Tasua; }
const Missile& load_missiles::get_said1() const { return Said1; }
const Missile& load_missiles::get_tondar85() const { return Tondar85; }
const Missile& load_missiles::get_sangar_shekan() const { return SangarShekan; }