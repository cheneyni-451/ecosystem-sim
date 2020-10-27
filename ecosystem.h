#ifndef ECOSYSTEM_H
#define ECOSYSTEM_H

#include <vector>
#include <cstdint>
#include <utility>

using std::vector;
using std::pair;

class Environment {
private:
    vector<vector<uint8_t>> grid;  // grid of land = 0, water = 1, grass = 2
    size_t size;
    void generateWater();
    void printGrid() const;
};

#endif
