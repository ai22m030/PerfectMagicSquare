# Evolutionary Algorithm: Solving a magic square

This is an implementation of an evolutionary algorithm in C++ for solving magic squares of sizes between three and nine.
The program generates a population of random candidate solutions and evolves them over multiple generations using selection, crossover, and mutation.
The fitness of each candidate is evaluated based on how closely it matches the constraints of a magic square.

## Usage

To run the program, generate the make files using cmake and compile with your C++ compiler of choice.
Then run the resulting executable. The size of the magic square can be passed as a command-line argument. For example:

```bash
$ cmake .
$ make
$ ./bin/PerfectMagicSquare -d 3 -p 1000 -i 1000
```

This will solve a 3x3 magic square and output the solution to the console.

Following command can be used to run tests and generate squares of sizes between 3 and 9:

```bash
$ ctest
```

## Implementation Details

The program uses a `MagicSquare` class to represent a candidate solution to the magic square problem. The `MagicSquare` class contains a 2D array of integers to store the values of the magic square and a `fitness` value to represent how well it matches the constraints of a magic square.

The main loop of the program repeatedly evaluates the fitness of the population, selects the best candidates,
performs crossover and mutation to generate offspring,
and replaces candidates with the offspring. To make the algorithm more efficient additional new candidates are added to the population.
An elimination of duplicates is permanently happening in the process.
The program terminates when a solution with a fitness of 0 (i.e., a perfect magic square) is found or after a maximum number of iterations is reached.

## Limitations

The program uses a simple crossover strategy, which may not be the most effective for solving magic squares.
Other selection and crossover strategies could be investigated to improve the algorithm's performance.

The program may not find a solution to larger magic squares within a reasonable amount of time or memory.
Additional optimizations or heuristics may be needed to solve larger magic squares efficiently.

## Test results

Running all tests with the given parameters:

![results_image](img/tests.png "Test results")

### Resulting squares

3x3 Square:
```bash
+---+---+---+
| 2 | 7 | 6 |
+---+---+---+
| 9 | 5 | 1 |
+---+---+---+
| 4 | 3 | 8 |
+---+---+---+
```

4x4 Square:
```bash
+----+----+----+----+
| 13 |  4 | 16 |  1 |
+----+----+----+----+
| 11 |  6 | 10 |  7 |
+----+----+----+----+
|  2 | 15 |  3 | 14 |
+----+----+----+----+
|  8 |  9 |  5 | 12 |
+----+----+----+----+
```

5x5 Square:
```bash
+----+----+----+----+----+
|  1 | 14 | 20 | 17 | 13 |
+----+----+----+----+----+
| 16 | 24 |  5 |  8 | 12 |
+----+----+----+----+----+
|  3 | 18 | 19 | 21 |  4 |
+----+----+----+----+----+
| 22 |  2 |  6 | 10 | 25 |
+----+----+----+----+----+
| 23 |  7 | 15 |  9 | 11 |
+----+----+----+----+----+
```

6x6 Square:
```bash
+----+----+----+----+----+----+
|  3 |  8 | 30 | 32 | 20 | 18 |
+----+----+----+----+----+----+
|  7 |  9 | 15 | 26 | 29 | 25 |
+----+----+----+----+----+----+
| 17 | 33 | 24 |  6 | 12 | 19 |
+----+----+----+----+----+----+
| 36 | 10 | 28 | 31 |  2 |  4 |
+----+----+----+----+----+----+
| 34 | 16 | 13 |  5 | 21 | 22 |
+----+----+----+----+----+----+
| 14 | 35 |  1 | 11 | 27 | 23 |
+----+----+----+----+----+----+
```

7x7 Square:
```bash
+----+----+----+----+----+----+----+
| 18 | 35 |  3 | 46 | 30 | 22 | 21 |
+----+----+----+----+----+----+----+
| 41 |  9 | 26 | 43 | 12 | 37 |  7 |
+----+----+----+----+----+----+----+
| 40 | 27 | 29 | 31 | 34 |  1 | 13 |
+----+----+----+----+----+----+----+
| 47 |  2 | 38 | 24 | 14 | 45 |  5 |
+----+----+----+----+----+----+----+
|  6 | 25 | 16 | 17 | 33 | 36 | 42 |
+----+----+----+----+----+----+----+
|  8 | 28 | 44 |  4 | 20 | 23 | 48 |
+----+----+----+----+----+----+----+
| 15 | 49 | 19 | 10 | 32 | 11 | 39 |
+----+----+----+----+----+----+----+
```

8x8 Square:
```bash
+----+----+----+----+----+----+----+----+
| 39 |  1 | 18 | 43 | 50 | 64 | 20 | 25 |
+----+----+----+----+----+----+----+----+
| 16 | 63 | 45 | 44 | 10 |  4 | 24 | 54 |
+----+----+----+----+----+----+----+----+
| 36 | 11 | 14 | 48 | 60 | 22 | 17 | 52 |
+----+----+----+----+----+----+----+----+
| 42 |  2 | 23 | 15 | 32 | 46 | 47 | 53 |
+----+----+----+----+----+----+----+----+
| 40 | 62 |  5 | 30 | 38 | 35 |  9 | 41 |
+----+----+----+----+----+----+----+----+
| 28 |  7 | 61 | 26 | 31 | 49 | 55 |  3 |
+----+----+----+----+----+----+----+----+
| 51 | 58 | 37 | 33 | 27 |  6 | 29 | 19 |
+----+----+----+----+----+----+----+----+
|  8 | 56 | 57 | 21 | 12 | 34 | 59 | 13 |
+----+----+----+----+----+----+----+----+

```

9x9 Square:
```bash
+----+----+----+----+----+----+----+----+----+
| 19 | 78 | 43 |  3 | 11 | 68 | 72 | 36 | 39 |
+----+----+----+----+----+----+----+----+----+
| 75 | 33 | 28 | 14 | 57 | 40 | 66 | 44 | 12 |
+----+----+----+----+----+----+----+----+----+
| 64 | 79 | 69 |  7 | 35 | 30 | 48 |  5 | 32 |
+----+----+----+----+----+----+----+----+----+
| 46 | 13 | 65 | 77 | 16 | 29 | 60 | 61 |  2 |
+----+----+----+----+----+----+----+----+----+
| 22 | 38 | 58 | 63 | 50 | 55 |  6 |  1 | 76 |
+----+----+----+----+----+----+----+----+----+
| 24 | 10 | 26 | 49 | 54 | 47 | 34 | 51 | 74 |
+----+----+----+----+----+----+----+----+----+
| 53 | 27 | 15 | 67 | 56 | 18 | 17 | 71 | 45 |
+----+----+----+----+----+----+----+----+----+
| 41 | 70 | 42 |  8 | 59 | 73 |  4 | 20 | 52 |
+----+----+----+----+----+----+----+----+----+
| 25 | 21 | 23 | 81 | 31 |  9 | 62 | 80 | 37 |
+----+----+----+----+----+----+----+----+----+
```