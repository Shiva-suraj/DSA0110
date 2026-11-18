# Assignment 2 – CO2 C++ Functions and OOP

**Student:** A. Siva suraj sai  
**Register number:** 192425276  
**Course outcome:** CO2  
**Total marks:** 50  
**Compiler:** GNU g++ (Debian 14.2.0-19) 14.2.0  
**Standard:** C++17  
**Repository:** https://github.com/Shiva-suraj/DSA0110  
**Folder:** Assignment 2

## Compile and run

From this folder:

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -O0 Task01/Task01_References.cpp -o task01
./task01
```

Change the source path and executable name for the required task. For the Q6 benchmark:

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -O0 Task06/InlineBenchmark.cpp -o inline_bench
./inline_bench
g++ -std=c++17 -Wall -Wextra -Wpedantic -O2 Task06/InlineBenchmark.cpp -o inline_bench_opt
./inline_bench_opt
```

The dangling-reference example is intentionally unsafe. Compile only to inspect its warning; do not execute it.

## Task summaries

| Folder | Topic | Main outcome |
|---|---|---|
| Task01 | Call by value, reference and pointer | Shows which parameter modes update the caller and compares in-place updates with return values. |
| Task02 | Return by reference and dangling references | Modifies the maximum array element through a reference; explains vector reallocation invalidation. |
| Task03 | Default arguments and overloading | Demonstrates ambiguous original overloads and a redesigned, non-ambiguous set. |
| Task04 | Class with internal array | SavingsAccount keeps the latest ten transactions using a circular index. |
| Task05 | Static members and arrays of objects | Assigns three bus seats, places extra tickets on the waiting list, and tests the Token prediction. |
| Task06 | Friend and inline functions | Computes time differences, tests noon/equal times and measures ten million calls. |
| Task07 | Diagnose, redesign and validate | Compares shifting history with O(1) circular-buffer insertion. |

Each task folder includes its principal C++ source, output text and an SVG terminal-style output capture. Additional diagnostics and benchmark files are included where relevant.

## Verification
- Seven main task programs and supplementary examples were compiled and executed.
- Q1 and Q5 output predictions were recorded in the report before execution; both matched.
- The original Q3 overload set was separately compiled to capture the expected ambiguity error.
- Q2's dangling-reference example was compiled to capture the compiler warning and was not run because using the reference would be undefined behaviour.
- Timing results are single-run measurements and depend on hardware, compiler and system load.
- SVG captures are generated from actual recorded console output; they are not photographs of a physical terminal.

## Individual work and submission
This is an individual assignment. Read the source, understand the design decisions, and practise changing the inputs for the viva. This folder is inside the existing repository URL supplied by the student. It is not a new repository named with the PDF's suggested naming convention. Submit the report and repository link to Google Classroom yourself.
