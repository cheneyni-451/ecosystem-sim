#include <getopt.h>
#include <iostream>

#include "ecosystem.h"

using namespace std;

int main() {
    // std::ios_base::sync_with_stdio(false);
    Environment env(5);

    env.generateWater();
    env.generateGrass();
    env.printGrid();

    return 0;
}
