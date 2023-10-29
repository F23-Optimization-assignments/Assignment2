# Interior-Point algorithm 

# Input format

  | Input Line | Description |
  | --- | --- |
  | 0 | Type of obj. function (min = 0, max = 1) |
  | 7 3 | Number of ALL variables, number of ALL constraints |
  | 1 2 3 4 0 0 0 | Coefficients of the objective function |
  | 1 2 3 4 1 0 0 | First row of matrix A of constraints (w/out values of constraints) | 
  | .     .     . | ... |
  | 1 2 3 4 0 0 1 | Last row of matrix A of constraints (w/out values of constraints) |
  | 1 2 3 | Vector of values of the constraints |
  | 4 5 6 | Indexes of the base variables, chosen by the user (starting from 0), |
  | 0.00001| Approximation accuracy |

# Output format

  Console printing; Simplex, Interior-Point (alpha = 0.5), Interior-Point (alpha = 0.9). 

  Any addiitonal information will be printed in the console.

![Build Status](https://github.com/F23-Optimization-assignments/Assignment1/actions/workflows/ci.yml/badge.svg)
