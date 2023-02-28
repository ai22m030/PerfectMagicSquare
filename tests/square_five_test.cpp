//
// Created by Adnan Vatric on 17.02.23.
//

#include <iostream>
#include <vector>

#include "magic_square.h"

const int POPULATION = 10000;
const int SIZE = 5;
const int ITERATIONS = 10000;

int main() {
    std::vector<MagicSquare> population;

    for(int i = 0; i < POPULATION; i++) population.emplace_back(SIZE);

    auto square = solve(population, SIZE, ITERATIONS, true);

    if(square.getFitness() == 0) {
        std::cout << "Found solution:" << std::endl;
        square.print(false);
    } else {
        std::cout << "No solution found!" << std::endl;
    }

    return EXIT_SUCCESS;
}