#ifndef ECOSYSTEM_H
#define ECOSYSTEM_H

#include <cstdint>
#include <utility>
#include <vector>

using std::pair;
using std::vector;

class Environment {
   public:
    enum TerrainType : uint8_t {
        Land,
        Water,
        Grass
    };

    Environment(const size_t sz_) {
        grid.resize(sz_);
        for (auto &row : grid) {
            row.resize(sz_);
        }
    }

    void generateWater();
    void generateGrass();
    void printGrid() const;

   private:
    vector<vector<TerrainType>> grid;  // grid of land = 0, water = 1, grass = 2

    // helper functions
    size_t wrapGridIndex(const size_t index) const {
        return (index + grid.size()) % grid.size();
    }
};

#endif
