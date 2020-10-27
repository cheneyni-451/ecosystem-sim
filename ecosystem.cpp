#include "ecosystem.h"

#include <chrono>
#include <cstdint>
#include <random>
#include <stack>
#include <utility>
#include <iostream>

using std::pair;

void Environment::generateWater() {
    size_t seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    size_t randRow = generator() % size;
    size_t randCol = generator() % size;
    grid[randRow][randCol] = 1;  // set to water

    size_t maxWaterTiles = size / 4 * size;

    pair<size_t, size_t> start(randRow, randCol);
    std::stack<pair<size_t, size_t>> waterStack;
    waterStack.push(start);
    static const pair<size_t, size_t> offsets[4] = {
        { -1, 0 },
        { 1, 0 },
        { 0, -1 },
        { 0, 1 }
    };

    while (maxWaterTiles != 0) {
        const pair<size_t, size_t> &current = waterStack.top();

        vector<pair<size_t, size_t>> neighbors;
        neighbors.reserve(4);
        for (const auto &offset : offsets) {
            pair<size_t, size_t> neighbor(current.first + offset.first, current.second + offset.second);
            if (grid[neighbor.first][neighbor.second] == 0) {
                neighbors.push_back(neighbor);
            }
        }
        if (neighbors.empty()) {
            waterStack.pop();
            continue;
        }
        size_t randIndex = generator() % neighbors.size();
        pair<size_t, size_t> &neighbor = neighbors[randIndex];
        grid[neighbor.first][neighbor.second] = 1;  // set to water
        waterStack.push(neighbor);

        --maxWaterTiles;
    }
}


void Environment::printGrid() const {
    for (const auto &row : grid) {
        for (const auto &val : row) {
            std::cout << val << ' ';
        }
        std::cout << '\n';
    }
}
