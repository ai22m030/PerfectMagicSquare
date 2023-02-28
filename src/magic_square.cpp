//
// Created by Adnan Vatric on 27.02.23.
//

#include <iostream>
#include <random>

#include "magic_square.h"

// Define the random number generator
std::mt19937 rng(std::random_device{}());

MagicSquare::MagicSquare(int size, bool randomize) {
    this->fitness = 0;
    this->dimension = size;
    this->values.resize(size, std::vector<int>(size));
    this->magicSum = MAGIC_SUM(size);

    if(randomize)
        this->randomize();

    this->evaluate();
}

void MagicSquare::init() {
    for(auto& row : this->values)
        for(auto& col : row)
            col = 0;

    this->fitness = 0;
    this->evaluate();
}

void MagicSquare::randomize() {
    std::vector<int> tmpValues(this->dimension * this->dimension);
    std::iota(tmpValues.begin(), tmpValues.end(), 1);
    std::shuffle(tmpValues.begin(), tmpValues.end(), rng);

    int i = 0;
    for(auto &row : this->values){
        for(auto &col : row){
            col = tmpValues[i];
            i++;
        }
    }
}

void MagicSquare::evaluate() {
    this->fitness = 0;

    this->fitness += this->fitnessRows();
    this->fitness += this->fitnessColumns();
    this->fitness += this->fitnessDiagonal1();
    this->fitness += this->fitnessDiagonal2();
}

void MagicSquare::swap() {
    std::uniform_int_distribution<int> dist(0, this->dimension - 1);

    int fromRow, toRow, fromCol, toCol;

    do {
        fromRow = dist(rng);
        toRow = dist(rng);
        fromCol = dist(rng);
        toCol = dist(rng);
    } while((fromRow == toRow) && (fromCol == toCol));

    std::swap(this->values[fromRow][fromCol], this->values[toRow][toCol]);

    this->evaluate();
}

void MagicSquare::print(bool details) {
    for (auto &value: this->values) {
        for (int j: value) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }

    if(details)
        std::cout << "Fitness: " << this->getFitness() << std::endl << std::endl;
}

int MagicSquare::fitnessRows() {
    int fit = 0;

    for (auto &rows: this->values) {
        int sum = 0;

        for (auto cols: rows) {
            sum += cols;
        }

        fit += std::abs(sum - magicSum);
    }

    return fit;
}

int MagicSquare::fitnessColumns() {
    int fit = 0;

    for (int cols = 0; cols < this->dimension; cols++) {
        int sum = 0;

        for (auto &value: this->values) {
            sum += value[cols];
        }

        fit += std::abs(sum - this->magicSum);
    }

    return fit;
}

int MagicSquare::fitnessDiagonal1() {
    int sum = 0;

    for (int i = 0; i < this->dimension; i++) {
        sum += this->values[i][i];
    }

    return std::abs(sum - this->magicSum);
}

int MagicSquare::fitnessDiagonal2() {
    int sum = 0;

    for (int i = this->dimension - 1; i >= 0; i--) {
        sum += this->values[this->dimension - (i + 1)][i];
    }

    return std::abs(sum - this->magicSum);
}

bool MagicSquare::valueExist(int value) {
    for(auto& row : this->values)
        for(auto col : row)
            if(col == value)
                return true;

    return false;
}

MagicSquare &MagicSquare::operator=(const MagicSquare &other) {
    if (this != &other)
        for(int row = 0; row < this->dimension; row++)
            for(int col = 0; col < this->dimension; col++)
                this->values[row][col] = other.getValue(row, col);

    this->evaluate();

    return *this;
}

bool operator==(const MagicSquare &a, const MagicSquare &b) {
    if(&a == &b)
        return true;

    for(int row = 0; row < a.dimension; row++)
        for(int col = 0; col < a.dimension; col++)
            if(a.getValue(row, col) != b.getValue(row, col))
                return false;

    return true;
}

bool operator!=(const MagicSquare &a, const MagicSquare &b) {
    return !(a == b);
}

void sort(std::vector<MagicSquare>& population) {
    std::sort(population.begin(),
              population.end(),[](const MagicSquare &a, const MagicSquare &b) {
                return a.getFitness() < b.getFitness();
            });
}

void selection(std::vector<MagicSquare>& population, std::vector<MagicSquare>& selected) {
    sort(population);

    for (int i = 0; i < population.size() / 3; i++)
        if(std::find(selected.begin(), selected.end(),population[i]) == selected.end())
            selected.push_back(population[i]);
}

void crossover(std::vector<MagicSquare>& population, std::vector<MagicSquare>& offspring, int size) {
    std::uniform_int_distribution<int> distFill(1, size * size);
    std::uniform_int_distribution<int> distParent(0, (int) population.size() - 1);

    for(int i = 0; i < (population.size() / 3 ); i++) {
        MagicSquare parent1(size, false);
        MagicSquare parent2(size, false);
        MagicSquare child(size, false);

        do {
            child.init();

            do {
                parent1 = population[distParent(rng)];
                parent2 = population[distParent(rng)];
            } while (parent1 == parent2);

            // Copy rows from first parent
            int row = 0;
            for (auto &value: parent1.getValues()) {
                int sum = 0;

                for (int j: value) sum += j;

                if (sum == parent1.getMagicSum()) {
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

                if (sum == parent1.getMagicSum()) {
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
                        int tmpValue = distFill(rng);

                        do {
                            if (!child.valueExist(tmpValue)) child.setValue(row, col, tmpValue);

                            tmpValue = distFill(rng);
                        } while (child.getValue(row, col) == 0);
                    }

                    col++;
                }

                row++;
            }
        } while (std::find(offspring.begin(), offspring.end(), child) != offspring.end());

        child.evaluate();
        offspring.push_back(child);
    }
}

void mutate(std::vector<MagicSquare>& population, double probability) {
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    // Mutate each square with a certain probability
    for (auto &square: population)
        if (dist(rng) < probability)
            square.swap();
}

MagicSquare solve(std::vector<MagicSquare>& population, int size, int iterations, bool verbose) {
    int lastFitness = -1;
    int unchanged = 0;
    double probability = BASE_MUTATION;
    bool infinite = false;

    if(iterations == -1) infinite = true;

    for (int it = 0; (it < iterations) || infinite; it++) {
        auto selected = std::vector<MagicSquare>();
        auto offspring = std::vector<MagicSquare>();
        auto check = std::vector<MagicSquare>();
        selection(population, selected);

        if(selected[0].getFitness() == 0)
            return selected[0];

        if(verbose){
            int count = 0;

            std::cout << "Current top 5:" << std::endl << std::endl;

            while(count < 5){
                std::cout << '#' << count + 1 << ':' << std::endl;
                selected[count].print();
                count++;
            }
        }

        crossover(population, offspring, size);
        sort(offspring);

        if(offspring[0].getFitness() == 0)
            return offspring[0];

        if (population[0].getFitness() == lastFitness) {
            unchanged++;

            if (probability < 1) probability += 0.1;
        } else {
            if (unchanged > 0) unchanged--;

            if (probability >= 1) probability = BASE_MUTATION;

            if (probability > BASE_MUTATION) probability -= 0.1;
        }

        mutate(offspring, probability);

        int i = 0;
        for(auto& oneSquare : selected) {
            population[i] = oneSquare;
            i++;
        }

        for(auto &oneSquare : offspring) {
            if (std::find(selected.begin(), selected.end(),oneSquare) == selected.end()) {
                population[i] = oneSquare;
                i++;
            }
        }

        while (i < population.size()) {
            MagicSquare tmpSquare = MagicSquare(size);

            if ((std::find(selected.begin(), selected.end(),tmpSquare) == selected.end()) &&
                (std::find(offspring.begin(), offspring.end(),tmpSquare) == offspring.end()) &&
                (std::find(check.begin(), check.end(),tmpSquare) == check.end())) {
                population[i] = tmpSquare;
                check.push_back(tmpSquare);
                i++;
            }
        }
    }

    sort(population);
    return population[0];
}
