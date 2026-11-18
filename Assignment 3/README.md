# CO3 Assignment 3 – C++ Constructors, Destructors and Operator Overloading

**Student:** A. Siva suraj sai  
**Register Number:** 192425276  
**Course Outcome:** CO3  
**Marks:** 50  
**Compiler used:** GNU g++ 14.2.0 (Debian), C++17  
**Repository:** https://github.com/Shiva-suraj/DSA0110  
**Folder:** Assignment 3

## Compile and run

Compile an individual program from this folder:

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -O0 Task01/Task01_Constructors.cpp -o task01
./task01
```

For memory checking:

```bash
g++ -std=c++17 -Wall -Wextra -fsanitize=address,undefined -fno-omit-frame-pointer Task02/Task02_Prescription.cpp -o task02_san
ASAN_OPTIONS=detect_leaks=1 ./task02_san
```

To compile and run the seven main programs:

```bash
for f in Task*/Task*.cpp; do
  exe="/tmp/$(basename "$f" .cpp)"
  g++ -std=c++17 -Wall -Wextra -Wpedantic -O0 "$f" -o "$exe" || exit 1
  "$exe"
done
```

## Task summaries

| Folder | Topic | Program/result |
|---|---|---|
| Task01 | Default, parameterised, overloaded and delegating constructors | Creates empty, donated and complete Book records; rejects negative copies. |
| Task02 | Shallow/deep copy and Rule of Three | Deep copies are independent; assignment and self-assignment are safe. |
| Task03 | Dynamic constructor, 2D seat map and destructor | Books/cancels seats; stack, block and heap lifetimes are shown; zero-row case is safe. |
| Task04 | Money arithmetic and stream operators | Uses integer paise; addition, subtraction, equality, carry and output are tested. |
| Task05 | Prefix/postfix increment, comparisons and subscript | Shows time rollover and checked playlist access. |
| Task06 | Text class and operator-overloading rules | Implements deep copy, assignment, concatenation and comparisons. |
| Task07 | Complex numbers for AC impedance | Calculates series and parallel impedance and checks division by zero. |

## Evidence and report

- Each task has its own folder and C++ source.
- `REPORT.md` contains expanded explanations, pseudocode, output predictions, test cases, hand calculations and Big-O analysis.
- `EXPERIMENTS.md` records measured timings, seat-map memory estimates, prediction checks and sanitizer/compiler evidence.
- Each task folder contains its source, `Output.txt` and `Screenshot.svg`; extra benchmark and diagnostic files are stored beside the relevant task.
- The SVG captures are terminal-style images generated from the actual recorded program output text, not photographs of a physical terminal.
- Negative demonstrations (expected compile error, reorder warning, shallow-copy double-free and intentional memory leak) are clearly labelled.

## Academic integrity and submission

This is an individual assignment. Understand the code, compile it again on your own computer and be prepared to explain or modify it during viva. Compiler timings depend on hardware and optimisation flags. The repository does not submit anything to Google Classroom; upload the report and repository link there yourself.
