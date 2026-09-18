# On A Roll Again: Analysis of a Dice Removal Game

This repository contains the companion C++ code for the paper:

Camellini, F., Ghantous, W., Lanocita, A. M., Mangiapanello, L. E., Miller, S. J., Tresch, G., & Yildirim, E. Z. (2026). On A Roll Again: Analysis of a Dice Removal Game. The PUMP Journal of Undergraduate Research, 9, 145–157. https://doi.org/10.46787/pump.v9i.6774

## Overview

The game studied in the paper is a sequential dice-removal process. Suppose we begin with n dice, each with s faces, where s >= n. On each round:

- roll all dice still in play,
- remove every die that shows the current number of remaining dice,
- continue until no dice remain.

The quantity of interest is the total number of rounds required to finish the game. The paper derives exact recursive and non-recursive expressions for the expected value and variance, and provides simulation-based estimates for comparison.

This project implements both approaches in C++:

- exact symbolic/combinatorial calculations,
- Monte Carlo simulation of random game trajectories.

## Mathematical setup

Let D denote the initial number of dice and S the number of faces on each die. The game ends when the remaining number of dice reaches zero.

The paper shows that this process can be represented by a maximum of independent geometric-type random variables, and derives exact formulas for the expected value and variance of the total number of turns. In the code, the exact calculations use binomial coefficients and powers of 1/S and (S-1)/S.

The recursive expected-value computation implemented in calculations.cpp evaluates values of the form

- E[1] = 1,
- for j >= 1, a recurrence involving binomial coefficients and powers of 1/S and (S-1)/S,
- and the final quantity E[D].

The variance is then computed from the corresponding recursive identities. The code also includes non-recursive formulations, which serve as a check against the recursion.

## Repository contents

### code/calculations.cpp

This file computes exact values for the expected value and variance of the game length for given D and S.

It includes:

- power calculations for 1/S and (S-1)/S,
- a recursive binomial coefficient routine,
- recursive formulas for expected value and variance,
- non-recursive verification formulas,
- a small command-line interface that reads D and S from standard input.

### code/simulations.cpp

This file simulates many independent random runs of the dice-removal game and estimates the expected value and variance from sample data.

It includes:

- random game generation,
- the nThrows count of repeated rolls needed to obtain a successful result for each die,
- a maximum-over-dice step for each round,
- aggregation across N independent game realizations.

## Build and run

From the project root, compile the C++ programs with:

```bash
g++ code/calculations.cpp -O2 -std=c++17 -o calculations
g++ code/simulations.cpp -O2 -std=c++17 -o simulations
```

### Exact calculations

Run:

```bash
./calculations
```

Then enter:

```text
D S
```

Example:

```text
5 6
```

The program prints the recursive and non-recursive expected-value calculations and the recursive and non-recursive variance calculations.

### Monte Carlo simulation

Run:

```bash
./simulations
```

Then enter:

```text
N D S mu
```

where:

- N is the number of simulated game runs,
- D is the initial number of dice,
- S is the number of faces on each die,
- mu is the exact expected value used for variance estimation.

The code reports:

- the time taken to generate random sequences,
- the time taken to estimate the mean,
- the time taken to estimate variance,
- the estimated expected value,
- the estimated variance.

## Notes on assumptions

- The code assumes S >= D, which matches the paper's setting.
- For exact formulas, the implementation uses floating-point arithmetic for convenience and readability.
- The simulation file uses a random process consistent with the game definition: for each die, repeatedly roll until the result equals S, counting the number of trials; then take the maximum over the D dice in that round.

## Citation

If you use this code or adapt it for research or teaching, please cite:

Camellini, F., Ghantous, W., Lanocita, A. M., Mangiapanello, L. E., Miller, S. J., Tresch, G., & Yildirim, E. Z. (2026). On A Roll Again: Analysis of a Dice Removal Game. The PUMP Journal of Undergraduate Research, 9, 145–157.

## License

This repository is intended for research and educational use in support of the publication above.
