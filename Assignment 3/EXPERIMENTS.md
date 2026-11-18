# Experimental measurements and evidence

**Environment:** GNU g++ 14.2.0, C++17, Linux container. Timings below are one measured run and are illustrative only; CPU scheduling, hardware, compiler version and optimisation affect the values.

## Q2 – Prescription copy size
The benchmark deep-copies an owning array of strings 20 times for each size, compiled with `-O2`.

| Medicines | Time for 20 copies |
|---:|---:|
| 10 | 0.017846 ms |
| 1,000 | 0.209851 ms |
| 100,000 | 35.1181 ms |

The growth is consistent with copying every medicine: O(n) time and O(n) additional storage per copy.

## Q4 – One million money additions
A loop compared integer paise addition with double addition. The volatile accumulators prevent the compiler from replacing the entire loop with a single constant expression.

| Representation | Time | Final value |
|---|---:|---:|
| Integer paise | 1.31424 ms | 17,000,123 paise |
| double | 4.572657 ms | 170001.230001761 |

The floating-point value shows a small representation/accumulation error. The timing is not a general performance guarantee; the integer representation is selected primarily for currency correctness.

## Q5 – Ten million increments
The benchmark uses a volatile counter value to prevent the compiler from eliminating the loop. This introduces volatile-access overhead, so the numbers compare this benchmark setup, not all possible Time classes.

| Build | Prefix ++ | Postfix ++ |
|---|---:|---:|
| `-O0` | 26.1118 ms | 57.2773 ms |
| `-O2` | 3.43664 ms | 23.7475 ms |

The postfix operation preserves and returns the old value, so it performs extra copy work in this class benchmark.

## Q6 – 100,000 short concatenations
Each iteration creates a separate result from two short strings; the test avoids repeatedly growing one string to a huge length.

| Implementation | Time | Total result characters |
|---|---:|---:|
| Custom owning Text with + | 7.76338 ms | 1,000,000 |
| std::string with + | 1.78922 ms | 1,000,000 |

The standard library implementation is faster in this run and is preferred for ordinary application code.

## Q3 – Seat-map allocation estimate
Assuming a 64-bit platform with 8-byte pointers and 1-byte char elements, the seat data plus row-pointer array is:

| Map | Seat bytes | Row-pointer bytes | Approx. total |
|---|---:|---:|---:|
| 10 × 20 | 200 | 80 | 280 bytes |
| 100 × 200 | 20,000 | 800 | 20,800 bytes |
| 1,000 × 2,000 | 2,000,000 | 8,000 | 2,008,000 bytes |

This excludes allocator metadata and alignment overhead. The program makes one pointer-array allocation and one allocation per row.

## Prediction checks
- Logger prediction: `+A +B -B copyAc use -Ac +P -P end -A`; actual output matched.
- Counter prediction: `5 7 7`; actual output matched.

## Sanitizer and compiler evidence
- Correct Prescription, Event and Text programs completed under AddressSanitizer/UndefinedBehaviorSanitizer without diagnostics.
- The deliberately shallow-copy example triggered an AddressSanitizer double-free report.
- The deliberately missing-delete example triggered a LeakSanitizer report for a 400-byte leak.
- Removing Book's default constructor caused the expected compile error for an array.
- The deliberately reversed initializer list produced `-Wreorder` and uninitialised-member warnings.

The failing examples are intentionally unsafe demonstrations and must not be used as the submitted solutions. See the evidence text files in the matching task folders.
