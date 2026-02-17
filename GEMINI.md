# Gemini Project Context: CodingQuestions-Quant

This file provides context for the Gemini CLI to understand the structure and conventions of this project.

## Project Overview

This repository is a collection of solutions to various quantitative and algorithmic coding questions. It serves as a personal knowledge base and practice area for common interview-style problems. The solutions are implemented in different programming languages, primarily C++ and Python.

The problems cover a wide range of topics including:
- Dynamic Programming
- Data Structures (Stacks, Queues)
- Array and String manipulation
- Probability and Combinatorics
- Algorithms (Searching, Sorting, Sampling)
- Brain Teasers

The repository also contains two PDF documents:
- `The (N+1)_(K+1) Formula_ Universal Applications.pdf`: A document explaining a powerful formula for solving "drawing without replacement" problems.
- `Coding Questions Report QUANT.pdf`: A report that appears to be the source for many of the problems in this repository.

## Directory Structure

The project is organized into numbered directories, where each directory corresponds to a specific coding problem.

- `/<problem-number>-<ProblemName>/`: Contains all files related to a single problem.
  - `README.md`: A detailed explanation of the problem, its constraints, different solution approaches, and complexity analysis.
  - `main.py` or `*.cpp`: The source code for the solution.
  - Other supporting files (e.g., executables, additional data).

**Note:** The directories `6-Find Odd Ball with Three Weighings` and `7-Bayesian Coin Bias` are currently empty.

## Problem Index

Here is a summary of the problems available in this repository:

- **1. Egg Dropping Puzzle:** Find the minimum number of trials to determine the highest safe floor to drop an egg from. (Dynamic Programming)
- **2. Stack with Two Queues:** Implement a LIFO stack using two FIFO queues. (Data Structures)
- **3. Intersection of Two Sorted Arrays:** Find the intersection of two sorted arrays, optimized for when one array is much smaller than the other. (Arrays, Binary Search)
- **4. Generate All Valid Anagrams:** Generate all valid dictionary words from a given set of letters. (Strings, Hash Maps)
- **5. Integer Partition:** Count the number of ways to write a positive integer as a sum of positive integers. (Dynamic Programming, Recursion)
- **8. Expected Draws to Get an Ace:** Calculate the expected number of draws to get the first Ace from a shuffled deck. (Probability, Combinatorics)
- **9. Ants Walking on a Stick:** Find the maximum time for all ants to fall off a stick, using the "pass-through" trick. (Lateral Thinking, Simulation)
- **10. Weighted Sampling Variations:** Implement various weighted sampling algorithms like Prefix Sum, Alias Method, and A-Res. (Probability, Algorithms)

## How to Run Solutions

Since this is a collection of independent problems, there is no single, project-wide build or run command. Solutions must be executed on a per-directory basis.

### C++ Solutions

C++ files are typically self-contained and can be compiled and run using a standard C++ compiler like `g++`.

**To compile and run a C++ file (e.g., `main.cpp`):**

```bash
# Navigate to the problem's directory
cd <problem-directory>

# Compile the source code
g++ -std=c++11 -o solution main.cpp

# Run the compiled executable
./solution
```

### Python Solutions

Python files can be run directly using the Python interpreter.

**To run a Python file (e.g., `main.py`):**

```bash
# Navigate to the problem's directory
cd <problem-directory>

# Run the Python script
python3 main.py
```

## Key Files

- **`README.md` (root):** Provides a high-level table of contents, linking to the detailed README for each problem.
- **`<problem-directory>/README.md`:** The primary documentation for a problem. It is the best place to start to understand the challenge and its solution.
- **`<problem-directory>/*.py` / `*.cpp`:** The source code implementation of the solution.
- **`The (N+1)_(K+1) Formula_ Universal Applications.pdf` / `Coding Questions Report QUANT.pdf`:** Supplementary PDF documents.

## Adding a New Problem

To add a new solution, follow the existing convention:

1.  Create a new numbered directory (e.g., `11-NewProblem`).
2.  Add a `README.md` file inside the new directory explaining the problem.
3.  Add the source code file(s) for the solution.
4.  Optionally, update the root `README.md` to include a link to the new problem.
