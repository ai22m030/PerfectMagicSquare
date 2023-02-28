//
// Created by Adnan Vatric on 27.02.23.
//

#ifndef PERFECT_MAGIC_SQUARE_MAGIC_SQUARE_H
#define PERFECT_MAGIC_SQUARE_MAGIC_SQUARE_H

#include <vector>

#define MAGIC_SUM(square_size) ((square_size * (square_size * square_size + 1)) / 2)

const double BASE_MUTATION = 0.1;

class MagicSquare{
public:
    explicit MagicSquare(int, bool = true);

    void init();
    void randomize();
    void evaluate();
    void swap();

    void print(bool = true);

    [[nodiscard]] auto getFitness() const { return this->fitness; }
    [[nodiscard]] auto getMagicSum() const { return this->magicSum; }
    [[nodiscard]] auto getValue(int row, int col) const { return this->values[row][col]; }
    auto& getValues() { return this->values; }

    void setValue(int row, int col, int value) { this->values[row][col] = value; }

    bool valueExist(int);

    MagicSquare& operator=(const MagicSquare&);

    friend bool operator== (const MagicSquare&, const MagicSquare&);
    friend bool operator!= (const MagicSquare&, const MagicSquare&);
private:
    std::vector<std::vector<int>> values;
    int dimension;
    int fitness;
    int magicSum;

    int fitnessRows();
    int fitnessColumns();
    int fitnessDiagonal1();
    int fitnessDiagonal2();
};

bool operator== (const MagicSquare&, const MagicSquare&);
bool operator!= (const MagicSquare&, const MagicSquare&);

void sort(std::vector<MagicSquare>&);
void selection(std::vector<MagicSquare>&, std::vector<MagicSquare>&);
void crossover(std::vector<MagicSquare>&, std::vector<MagicSquare>&, int);
void mutate(std::vector<MagicSquare> &population, double probability);

MagicSquare solve(std::vector<MagicSquare>&, int, int, bool = false);

#endif //PERFECT_MAGIC_SQUARE_MAGIC_SQUARE_H
