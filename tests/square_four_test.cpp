//
// Created by Adnan Vatric on 27.02.23.
//

#include <iostream>
#include <vector>
#include <string>

#include "magic_square.h"
#include "program_options.h"

const int POPULATION = 10000;
const int SIZE = 4;
const int ITERATIONS = 10000;

int main(int argc, char **argv) {
    const std::vector<std::string_view> args(argv, argv + argc);
    bool verbose = program_options::has(args, "-v");
    std::vector<MagicSquare> population;
    std::string name("result_4.csv");

    for (int i = 0; i < POPULATION; i++) population.emplace_back(SIZE);

    auto square = solve(population, SIZE, ITERATIONS, verbose);

    if (square.getFitness() == 0) {
        std::cout << "Found solution:" << std::endl;
        square.print(false);
        square.write(name);

        return EXIT_SUCCESS;
    }

    std::cout << "No solution found!" << std::endl;

    return EXIT_SUCCESS;
}