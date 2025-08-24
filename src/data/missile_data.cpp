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