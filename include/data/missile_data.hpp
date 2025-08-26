#pragma once

#include "../domain/missile.hpp"

#include <vector>

class load_missiles {
    private:
        Missile Shahab7;
        Missile Sejid;
        Missile Hormuz3;
        Missile Ghadr313;
        Missile Tasua;
        Missile Said1;
        Missile Tondar85;
        Missile SangarShekan;

    public:
        load_missiles();
        
        // Getters (const reference to avoid copy)
        const Missile& get_shahab7() const;
        const Missile& get_sejid() const;
        const Missile& get_hormuz3() const;
        const Missile& get_ghadr313() const;
        const Missile& get_tasua() const;
        const Missile& get_said1() const;
        const Missile& get_tondar85() const;
        const Missile& get_sangar_shekan() const;
};
