//
// Created by Adnan Vatric on 17.02.23.
//

#include <iostream>
#include <random>
#include <iomanip>
#include <fstream>
#include <string>

#include <omp.h>

#include "magic_square.h"

/**
 * Create a new magic square with given size.
 *
 * @param size
 * @param randomize
 */
MagicSquare::MagicSquare(int size, bool randomize) {
    this->fitness = 0;
    this->dimension = size;
    this->values.resize(size, std::vector<int>(size));
    this->sum = MAGIC_SUM(size);

    if (randomize)
        this->randomize();

    this->evaluate();
}

/**
 * Init square with 0 values.
 */
void MagicSquare::init() {
    for (auto &row: this->values)
        for (auto &col: row)
            col = 0;

    this->fitness = 0;
    this->evaluate();
}


/**
 * Generate random numbers for magic square.
 */
void MagicSquare::randomize() {
    thread_local std::mt19937 local_rng(std::random_device{}()); // Local RNG for each thread
    std::vector<int> tmpValues(this->dimension * this->dimension);
    std::iota(tmpValues.begin(), tmpValues.end(), 1);
    std::shuffle(tmpValues.begin(), tmpValues.end(), local_rng);

    int i = 0;
    for (auto &row: this->values) {
        for (auto &col: row) {
            col = tmpValues[i % (this->dimension * this->dimension)]; // Ensure the values are within range
            i++;
        }
    }
}

/**
 * Evaluate the fitness of a square solution.
 *
 * @param square
 * @param magicSum
 */
void MagicSquare::evaluate() {
    this->fitness = 0;

    this->fitness += this->fitnessRows();
    this->fitness += this->fitnessColumns();
    this->fitness += this->fitnessDiagonal1();
    this->fitness += this->fitnessDiagonal2();
}


/**
 * Change position of two random numbers.
 *
 */
void MagicSquare::swap() {
    thread_local std::mt19937 local_rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, this->dimension - 1);

    int fromRow, toRow, fromCol, toCol;
    do {
        fromRow = dist(local_rng);
        toRow = dist(local_rng);
        fromCol = dist(local_rng);
        toCol = dist(local_rng);
    } while ((fromRow == toRow) && (fromCol == toCol));

    std::swap(this->values[fromRow][fromCol], this->values[toRow][toCol]);
    this->evaluate();
}


/**
 * Print square to commandline
 *
 * @param details
 */
void MagicSquare::print(bool details) {
    int width = 2; // minimum width for single-digit numbers

    for (const auto &row: this->values) {
        for (const auto &num: row) {
            int numWidth = (int) std::to_string(num).length();
            if (numWidth > width)
                width = numWidth;
        }
    }

    // add 1 for left border
    width += 1;

    // print the matrix with borders between numbers
    for (const auto &row: this->values) {
        for (const auto &num: row)
            std::cout << "|" << std::setw(width - 1) << num;

        std::cout << "|" << std::endl;
    }

    if (details)
        std::cout << "Fitness: " << this->getFitness() << std::endl << std::endl;
}

/**
 * Output square to a csv file.
 *
 * @param name
 */
void MagicSquare::write(std::string &name) {
    std::ofstream outputFile(name, std::ios::trunc);

    for (const auto &row: this->values) {
        for (const auto &num: row)
            outputFile << num << ';';

        outputFile << std::endl;
    }

    outputFile.close();
}

/**
 * Calculate fitness for all rows of a square.
 *
 * @return
 */
int MagicSquare::fitnessRows() {
    int fit = 0;

    for (auto &rows: this->values) {
        int i = 0;

        for (auto cols: rows)
            i += cols;

        fit += std::abs(i - this->sum);
    }

    return fit;
}

/**
 * Calculate fitness for all columns of a square.
 *
 * @return
 */
int MagicSquare::fitnessColumns() {
    int fit = 0;

    for (int cols = 0; cols < this->dimension; cols++) {
        int i = 0;

        for (auto &value: this->values)
            i += value[cols];

        fit += std::abs(i - this->sum);
    }

    return fit;
}


/**
 * Calculate fitness of diagonal (left top to right bottom)
 *
 * @return
 */
int MagicSquare::fitnessDiagonal1() {
    int s = 0;

    for (int i = 0; i < this->dimension; i++)
        s += this->values[i][i];

    return std::abs(s - this->sum);
}

/**
 * Calculate fitness of diagonal (left bottom to right top)
 *
 * @return
 */
int MagicSquare::fitnessDiagonal2() {
    int s = 0;

    for (int i = this->dimension - 1; i >= 0; i--)
        s += this->values[this->dimension - (i + 1)][i];

    return std::abs(s - this->sum);
}

/**
 * Checks if given value exists in square.
 *
 * @param value
 * @return
 */
bool MagicSquare::valueExist(int value) {
    for (auto &row: this->values)
        for (auto col: row)
            if (col == value)
                return true;

    return false;
}

/**
 * Copy assign magic square.
 *
 * @param other
 * @return
 */
MagicSquare &MagicSquare::operator=(const MagicSquare &other) {
    if (this != &other)
        for (int row = 0; row < this->dimension; row++)
            for (int col = 0; col < this->dimension; col++)
                this->values[row][col] = other.getValue(row, col);

    this->evaluate();

    return *this;
}

/**
 * Custom operator comparing squares.
 *
 * @param a
 * @param b
 * @return
 */
bool operator==(const MagicSquare &a, const MagicSquare &b) {
    if (&a == &b)
        return true;

    for (int row = 0; row < a.dimension; row++)
        for (int col = 0; col < a.dimension; col++)
            if (a.getValue(row, col) != b.getValue(row, col))
                return false;

    return true;
}

/**
 * Custom operator comparing squares.
 *
 * @param a
 * @param b
 * @return
 */
bool operator!=(const MagicSquare &a, const MagicSquare &b) {
    return !(a == b);
}

/**
 * Sort squares by fitness.
 *
 * @param population
 */
void sort(std::vector<MagicSquare> &population) {
    std::sort(population.begin(),
              population.end(), [](const MagicSquare &a, const MagicSquare &b) {
                return a.getFitness() < b.getFitness();
            });
}

/**
 * Select the best third of the population.
 *
 * @param population
 * @param selected
 * @return
 */
void selection(std::vector<MagicSquare> &population, std::vector<MagicSquare> &selected) {
    sort(population);

#pragma omp parallel default(none) shared(population, selected)
    {
        std::vector<MagicSquare> local_selected;

#pragma omp for schedule(static)
        for (int i = 0; i < population.size() / 3; i++)
            if (std::find(selected.begin(), selected.end(), population[i]) == selected.end())
                local_selected.push_back(population[i]);

        // Merge local vectors into the global vector
#pragma omp critical
        selected.insert(selected.end(), local_selected.begin(), local_selected.end());
    }
}


/**
 * Combine random squares from population.
 *
 * @param offspring
 * @param size
 * @param population
 * @return
 */
void crossover(std::vector<MagicSquare> &population, std::vector<MagicSquare> &offspring, int size) {
    std::uniform_int_distribution<int> distFill(1, size * size);
    std::uniform_int_distribution<int> distParent(0, (int) population.size() - 1);

    // Creating a parallel region
#pragma omp parallel default(none) shared(population, offspring, size, distParent, distFill)
    {
        std::vector<MagicSquare> local_offspring;
        std::mt19937 local_rng(std::random_device{}());

#pragma omp for schedule(static)
        for (int i = 0; i < (population.size() / 3); i++) {
            MagicSquare parent1(size, false);
            MagicSquare parent2(size, false);
            MagicSquare child(size, false);

            do {
                child.init();

                do {
                    parent1 = population[distParent(local_rng)];
                    parent2 = population[distParent(local_rng)];
                } while (parent1 == parent2);

                // Copy rows from first parent
                int row = 0;
                for (auto &value: parent1.getValues()) {
                    int sum = 0;

                    for (int j: value) sum += j;

                    if (sum == parent1.getSum()) {
                        int col = 0;

                        for (int j: value) {
                            child.setValue(row, col, j);
                            col++;
                        }
                    }

                    row++;
                }

                // Copy Columns from first parent
                for (int col = 0; col < size; col++) {
                    int sum = 0;

                    for (auto &value: parent1.getValues()) sum += value[col];

                    if (sum == parent1.getSum()) {
                        row = 0;

                        for (auto &value: parent1.getValues()) {
                            child.setValue(row, col, value[col]);
                            row++;
                        }
                    }
                }

                // Add some values from second parent
                row = 0;
                for (auto &value: parent2.getValues()) {
                    int col = 0;

                    for (int j: value) {
                        if (child.getValue(row, col) == 0 && !child.valueExist(j))
                            child.setValue(row, col, j);

                        col++;
                    }

                    row++;
                }

                // Fill rest of empty values
                row = 0;
                for (auto &childRow: child.getValues()) {
                    int col = 0;

                    for (auto &childColum: childRow) {
                        if (childColum == 0) {
                            int tmpValue;

                            do {
                                if (!child.valueExist(tmpValue)) child.setValue(row, col, tmpValue);

                                tmpValue = distFill(local_rng);
                            } while (child.getValue(row, col) == 0);
                        }

                        col++;
                    }

                    row++;
                }
            } while (std::find(local_offspring.begin(), local_offspring.end(), child) != local_offspring.end());

            child.evaluate();
            local_offspring.push_back(child);
        }

        // Merge local vectors into the global vector
#pragma omp critical
        offspring.insert(offspring.end(), local_offspring.begin(), local_offspring.end());
    }

    // Evaluate fitness of offspring after all children have been created
#pragma omp parallel for schedule(static) default(none) shared(offspring)
    for (auto &child: offspring)
#pragma omp critical
        child.evaluate();
}

/**
 * Change position of two numbers in a square by a given probability.
 *
 * @param population
 * @param probability
 */
void mutate(std::vector<MagicSquare> &population, double probability) {
#pragma omp parallel default(none) shared(population, probability)
    {
        thread_local std::mt19937 local_rng(std::random_device{}()); // Local RNG for each thread
        std::uniform_real_distribution<double> dist(0.0, 1.0);

        // Mutate each square with a certain probability
#pragma omp for schedule(static)
        for (auto &square: population)
            if (dist(local_rng) < probability)
#pragma omp critical
                square.swap();
    }
}

/**
 * Solve a magic square using given parameters.
 *
 * @param population
 * @param size
 * @param iterations
 * @param verbose
 * @return
 */
MagicSquare solve(std::vector<MagicSquare> &population, int size, int iterations, bool verbose) {
    int lastFitness = -1;
    int unchanged = 0;
    double probability = BASE_MUTATION;
    bool infinite = false;

    if (iterations == -1) infinite = true;

    for (int it = 0; (it < iterations) || infinite; it++) {
        auto selected = std::vector<MagicSquare>();
        auto offspring = std::vector<MagicSquare>();
        auto check = std::vector<MagicSquare>();
        selection(population, selected);

        if (selected.front().getFitness() == 0)
            return selected.front();

        if (verbose) {
            int count = 0;

            std::cout << "Current top 5:" << std::endl << std::endl;

            while (count < 5) {
                std::cout << '#' << count + 1 << ':' << std::endl;
                selected[count].print();
                count++;
            }
        }

        crossover(population, offspring, size);
        sort(offspring);

        if (offspring.front().getFitness() == 0)
            return offspring.front();

        if (population.front().getFitness() == lastFitness) {
            unchanged++;

            if (probability < 1 && unchanged >= BASE_CHANGE_COUNT) probability += 0.1;
        } else {
            unchanged = 0;
            probability = BASE_MUTATION;
        }

        mutate(offspring, probability);

        int i = 0;
#pragma omp parallel for schedule(static) default(none) shared(population, selected, offspring, check, i)
        for (auto &oneSquare: selected) {
#pragma omp critical
            {
                population[i] = oneSquare;
                i++;
            }
        }

#pragma omp parallel for schedule(static) default(none) shared(population, selected, offspring, check, i)
        for (auto &oneSquare: offspring) {
            if (std::find(selected.begin(), selected.end(), oneSquare) == selected.end()) {
#pragma omp critical
                {
                    population[i] = oneSquare;
                    i++;
                }
            }
        }

        while (i < population.size()) {
            MagicSquare tmpSquare = MagicSquare(size);

            if ((std::find(selected.begin(), selected.end(), tmpSquare) == selected.end()) &&
                (std::find(offspring.begin(), offspring.end(), tmpSquare) == offspring.end()) &&
                (std::find(check.begin(), check.end(), tmpSquare) == check.end())) {
                population[i] = tmpSquare;
                check.push_back(tmpSquare);
                i++;
            }
        }
    }

    sort(population);
    return population.front();
}
