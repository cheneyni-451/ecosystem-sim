#include "ecosystem.h"

#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>
#include <stack>
#include <utility>

using std::pair;

/**
 * @brief  Randomly generates a body of water in the grid
 *         relative to the size of the grid
 */
void Environment::generateWater() {
    size_t seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    const size_t gridSize = grid.size();
    size_t randRow = generator() % gridSize;
    size_t randCol = generator() % gridSize;
    grid[randRow][randCol] = Water;

    size_t maxWaterTiles = gridSize / 4 * gridSize;

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
            size_t neighborRow = wrapGridIndex(current.first + offset.first);
            size_t neighborCol = wrapGridIndex(current.second + offset.second);
            pair<size_t, size_t> neighbor(neighborRow, neighborCol);
            if (grid[neighbor.first][neighbor.second] == Land) {
                neighbors.push_back(neighbor);
            }
        }
        if (neighbors.empty()) {
            waterStack.pop();
            continue;
        }

        // randomly pick a neighbor to add to stack
        size_t randIndex = generator() % neighbors.size();
        pair<size_t, size_t> &neighbor = neighbors[randIndex];
        grid[neighbor.first][neighbor.second] = Water;
        waterStack.push(neighbor);

        --maxWaterTiles;
    }
}

/**
 * @brief  Randomly places grass on the grid. Amount is relative
 *         to grid size
 */
void Environment::generateGrass() {
    // maybe generate random coordinates to change to grass
    // instead of looping through all coordinates
    size_t seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    for (auto &row : grid) {
        for (auto &tile : row) {
            if (tile == Land && generator() % 10 < 4) {
                tile = Grass;
            }
        }
    }
}

/**
 * @brief  Outputs a visual representation of the environment grid
 */
void Environment::printGrid() const {
    for (const auto &row : grid) {
        for (const auto &val : row) {
            std::cout << val << ' ';
        }
        std::cout << '\n';
    }
}
