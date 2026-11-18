# Assignment 2 – Experimental Measurements

Environment: GNU g++ 14.2.0, C++17. Results below are from a single measured run. Timings vary with hardware, compiler version, optimisation, CPU load and runtime environment.

## Q6 – Ten million friend-function calls

| Build | Inline function | Out-of-line function |
|---|---:|---:|
| -O0 | 27.7636 ms | 31.2967 ms |
| -O2 | 3.95762 ms | 3.89772 ms |

Both implementations produced checksum 2,050,000,000. At -O0 the inline version was slightly faster in this run. At -O2 the compiler optimised both and the difference was negligible. This demonstrates that inline is not a guarantee of improved speed.

## Q7 – Two million history insertions

| Implementation | Time |
|---|---:|
| Shifting array | 22.186 ms |
| Circular buffer | 9.473 ms |

Both retained exactly the same last 50 values. The first retained value was 1,999,950 and the last was 1,999,999. The measured result supports the O(k) versus O(1) insertion analysis.

## Compiler diagnostics

- Q2 intentionally invalid return-by-reference source generated GCC warning `-Wreturn-local-addr`. It was not executed because using the dangling reference is undefined behaviour.
- Q3 original overlapping overload declarations generated the expected ambiguous-call error. The redesigned program compiled and ran successfully.
- Correct task programs compiled with `-std=c++17 -Wall -Wextra -Wpedantic` and ran successfully.

## Output evidence

Each Task01–Task07 folder contains Output.txt and Output_Screenshot.svg. The SVG files are terminal-style images generated from the recorded program output, not photographs of a physical terminal.
