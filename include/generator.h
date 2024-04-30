//
// Created by Adnan Vatric on 18.02.23.
//

#ifndef MAGIC_SQUARE_GENERATOR_H
#define MAGIC_SQUARE_GENERATOR_H

#include <random>

static std::mt19937 rng(std::random_device{}());
static std::uniform_real_distribution<double> dist(0.0, 1.0);

#endif //MAGIC_SQUARE_GENERATOR_H
