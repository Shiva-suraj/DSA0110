# Assignment 2 – CO2: C++ Functions and Object-Oriented Concepts

**Student:** A. Siva suraj sai  
**Register number:** 192425276  
**Course outcome:** CO2  
**Total marks:** 50  
**Compiler:** GNU g++ (Debian 14.2.0-19) 14.2.0  
**Language standard:** C++17  
**Repository folder:** https://github.com/Shiva-suraj/DSA0110/tree/main/Assignment%202

> The uploaded ASSIGNMENT 2 PDF contains seven numbered questions (Q1–Q7), not twelve. This report follows those seven questions and their code-completion, output-prediction, alternative-design and complexity requirements.

## Q1 – Call by Value, by Reference and by Pointer (6 marks)

### Objective
Demonstrate why the hostel fee remains unchanged when passed by value, but changes when passed by reference or pointer. The program also returns a reference to the larger integer and uses default arguments.

### Prediction before execution
For `change(a,b,&c)`, the initial values are a=1, b=2, c=3. The local copy of a becomes 11 but caller a remains 1. Reference b becomes 12 and pointer target c becomes 13. `bigger(a,c)=100` changes c because c is larger. `show(1)` uses y=5,z=10 and prints 16; `show(1,2)` uses z=10 and prints 13; `show(1,2,3)` prints 6.

**Predicted complete output:**
```text
1 12 13
1 100
16 13 6
after call by value   : 45000
after call by reference: 40500
after call by pointer  : 38250
returned fee (25%): 33750
```
The executed output matched the prediction.

### Pseudocode
```text
change(a by value, b by reference, c by pointer):
    increase local a
    increase caller b
    increase *c if pointer is not null

applyByValue(fee, percent):
    update local copy only

applyConcession(fee reference, percent):
    fee = fee - fee * percent / 100

applyByPointer(fee pointer, percent):
    if pointer is valid, update pointed fee

applyAndReturn(fee, percent):
    return fee - fee * percent / 100
```

### Explanation
A by-value parameter is a separate local parameter object, so changes do not affect the caller. A reference is an alias for the caller's object. A pointer stores the object's address and changes the caller's value through dereferencing; null must be considered where allowed. A `const Student&` is appropriate when a function only reads a large object: it avoids copying and prevents accidental modification.

For multiple concessions, an in-place reference updater is convenient for sequential modifications. Returning a new fee is often safer for a billing calculation because the caller can validate the calculated value before replacing the original. The program demonstrates both. The completed TODO uses `fee -= fee * percent / 100;`.

### Tests and result
| Test | Expected | Actual |
|---|---|---|
| Value: 45000, 10% | Caller stays 45000 | 45000 |
| Reference: 45000, 10% | Caller becomes 40500 | 40500 |
| Pointer: 45000, 15% | Caller becomes 38250 | 38250 |
| Return: 45000, 25% | Return 33750 | 33750 |
| Default show(1) | 16 | 16 |
| bigger(a,c)=100 | Larger variable c changes | c=100 |

### Alternative and complexity
Returning a value uses `hostelFee = applyConcession(hostelFee,10);`. Each scalar calculation is O(1) time. A long long copied by value uses O(1) space. A large Student object passed by value copies its data (potentially O(n) for collections), while reference and const reference pass an alias and generally require O(1) parameter space.

## Q2 – Return by Reference and Its Dangers (4 marks)

### Objective and pseudocode
Find the highest mark and return a reference to the array element. The caller can modify the element using the returned reference.

```text
highestMark(array,n):
    reject n <= 0
    best = 0
    for i = 1 to n-1:
        if array[i] > array[best], best = i
    return reference to array[best]
```

### Output
```text
Highest before moderation: 92
After +2 moderation: 94
Read-only highest: 94
Returned copy: 94
Index before growth: 1, value: 94
Pointer before growth: 94
After reserve, index remains valid: 94, saved value: 94
Pointer/reference obtained before growth may be invalid; do not dereference it.
```

### Explanation
An `int&` refers to the original array element and permits assignment through the function call. A `const int&` allows reading but not modification through that reference. Returning `int` creates a copy; changing it does not update the array.

Returning a reference to an automatic local variable is wrong because that variable is destroyed when the function returns. The returned reference dangles; using it is undefined behaviour. GCC emits `-Wreturn-local-addr`. The intentionally incorrect program is compiled to capture the warning but is not executed.

When a vector grows beyond capacity, it may allocate new memory and relocate its elements. Existing pointers, references and iterators can become invalid. An index remains a position and can be used again if logical ordering is unchanged, but it must be checked against the new size.

### Tests
| Test | Expected result | Actual |
|---|---|---|
| Maximum of {78,92,85,88,91} | 92 | 92 |
| Add 2 using returned reference | 94 | 94 |
| const reference and copy | Both read 94 | Pass |
| Reserve larger vector capacity | Index remains valid; old pointer not used | Pass |
| Return local reference | Compiler warning | Warning captured; not run |

### Alternative and complexity
Returning an index makes the caller use `marks[index] += 2`; returning a pointer uses `*ptr += 2` after a null check. Finding the maximum is O(n) time and O(1) extra space for reference, index and pointer versions. Indexes are usually safer across vector reallocation than pointers or references, provided element ordering is unchanged.

## Q3 – Default Arguments and Function Overloading (6 marks)

### Problem and redesign
The original overloads `charge(double)`, `charge(double,bool)` and `charge(double,bool=false,bool=false)` overlap. The third function can be called with one argument because of defaults, making `charge(2.0)` ambiguous with the first overload. The redesign uses an int overload for grams, double for kg with default service flags, float for float kg, and a Parcel overload.

### Six predictions
| Call | Selected function | Reason |
|---|---|---|
| `charge(2)` | int grams | Exact int match |
| `charge(2.0)` | double kg | Exact double match; default flags |
| `charge(2.0f)` | float kg | Exact float match |
| `charge(1500)` | int grams | Exact int match |
| `charge(2.5,true)` | double overload | Exact double and bool |
| `charge(parcel)` | Parcel overload | Exact class match |

### Actual output
```text
charge(2) [int grams]: 40.04
charge(2.0) [double kg]: 80.00
charge(2.0f) [float kg]: 80.00
charge(1500) [int grams]: 70.00
charge(2.5, true) [double + express]: 120.00
charge(Parcel): 145.00
```

### Explanation, alternative and complexity
Overload resolution prefers an exact match over a promotion and a promotion over a standard conversion. If equally good candidates remain, the compiler reports ambiguity. Default arguments must be trailing/rightmost so callers cannot omit an earlier argument but supply a later one.

A single Parcel structure with optional fields is an alternative and makes adding new options easier. A function template is also possible, but unit conversion must be explicit to avoid mixing grams and kilograms. Overload resolution occurs at compile time, so it has no run-time algorithmic cost. Each charge calculation is O(1) time and O(1) auxiliary space. A large Parcel should be passed by const reference to avoid copying.

## Q4 – Class with an Array Inside It (6 marks)

### Design and pseudocode
SavingsAccount keeps private account number, balance, ten transaction values, count and next index. Public methods deposit, withdraw and miniStatement control access. The private array protects the account's invariants from arbitrary external changes. Some methods are defined inside the class and others outside with the scope resolution operator.

```text
addTransaction(x):
    data[next] = x
    next = (next+1) modulo 10
    if count < 10: count++

deposit(x):
    reject x <= 0
    balance += x
    addTransaction(+x)

withdraw(x):
    reject x <= 0 or x > balance
    balance -= x
    addTransaction(-x)

miniStatement():
    start at next if full, otherwise at 0
    print count entries in chronological order
```

### Output
```text
Account: 100245
Balance: Rs 1675.00
Recent transactions (oldest to newest):
1. +20.00
2. +30.00
3. +40.00
4. +50.00
5. +60.00
6. +70.00
7. +80.00
8. +90.00
9. +100.00
10. -25.00
Invalid withdrawal accepted: false
```

### Design decision and tests
With shifting, the 11th transaction moves the remaining nine entries left and inserts the new value at the end. This takes O(k) work for k stored entries. A circular buffer overwrites the oldest entry and advances an index, so insertion takes O(1). If the bank increases capacity to 50, the array size changes, but the circular approach still avoids shifting 49 elements on every insertion. A deque with push_back/pop_front is another alternative with amortised O(1) end operations and dynamic storage.

Tests include opening balance, deposit, valid withdrawal, more than ten transactions, insufficient-funds rejection and chronological mini-statement output. For fixed capacity k, circular insertion is O(1), shifting insertion is O(k) when full, statement printing is O(k), and both use O(k) storage.

## Q5 – Static Members and Arrays of Objects (7 marks)

### Design
BusTicket uses static `issued` because the count belongs to the whole class. The static data member is declared in the class and defined once outside it. The static function count() can access issued but not a particular object's non-static seat or name. A static function has no `this` pointer. Each ticket object has its own seat and name, while all tickets share issued.

### Token output prediction before execution
The PDF Token counter begins at 100. Three array objects are constructed and receive 101, 102 and 103. The extra object receives 104. The issued() result is 104-100 = 4.

Predicted output:
```text
101 103 104 4
```
Actual output matched.

### Completed BusTicket output
```text
Asha: Seat 1
Bala: Seat 2
Chitra: Seat 3
Dev: Waiting
Issued: 3
Esha: Waiting
Count inside function: 3
Esha: Waiting
Count inside function: 3
```

The first three tickets take the seats; the fourth waits. The helper function is called twice, but the shared count remains 3 because capacity has been reached. Local ticket objects are destroyed on function exit, but static data remains.

### Alternative and complexity
A global counter also stores one value but is not encapsulated. A TicketOffice object can own the count and be passed to tickets, allowing two buses to have independent capacity and count. Both designs have O(1) counter storage and O(1) creation/count operations. Static state is simple for one bus; a separate office is better for multiple buses.

## Q6 – Friend Functions and Inline Functions (8 marks)

### Pseudocode
```text
minutesBetween(a,b):
    x = a.hours*60 + a.minutes
    y = b.hours*60 + b.minutes
    return absolute(x-y)

earlier(a,b):
    compare hours
    if equal, compare minutes
    return true only if a is earlier
```

Friend functions are non-member functions that receive two Time objects equally. Their friend declaration grants access to private h and m. A member alternative would be called as a.minutesTo(b). Public getters are another alternative, but making the fields public would allow invalid values such as 25:99.

### Output and hand check
```text
205 false
10 true
0 false
```
9:45 is 585 minutes after midnight and 13:10 is 790, so the difference is 205 minutes. 13:10 is not earlier than 9:45. The 11:55 to 12:05 difference is ten minutes; equal times have zero difference and neither is earlier.

### Inline timing experiment
Ten million calls were measured on GNU g++ 14.2.0:

| Build | Inline | Out-of-line |
|---|---:|---:|
| -O0 | 27.7636 ms | 31.2967 ms |
| -O2 | 3.95762 ms | 3.89772 ms |

Both checksums were 2,050,000,000. At -O0, inline was slightly faster in this sample. At -O2, the compiler optimised both and the difference was negligible. Inline is not a guarantee of faster code; it permits inline substitution, and the compiler chooses whether to perform it. Both functions are O(1) time and O(1) extra space. Member functions/getters have the same complexity and can also be inlined.

### Deployment decision
Friend functions are justified for symmetric two-object comparisons that need private access. For a large production API, getters or member functions may reduce friendship. Keeping fields private protects valid-time rules. The benchmark is one run and depends on hardware and compiler settings.

## Q7 – Diagnose, Redesign and Validate (13 marks)

### A. Diagnose
The original shifting history in Task04 moves all retained elements left whenever a new item arrives after the fixed array is full. This costs O(k) per new item. The movement is unnecessary because only the oldest entry must be discarded.

### B. Measurable objective
Use a circular buffer that adds each item in O(1), preserves exactly the same latest 50 entries as the shift implementation, and uses a fixed array of 50 integers.

### C. Revised design and pseudocode
The redesigned class has an array, count and next-write index:
```text
add(value):
    data[next] = value
    next = (next+1) modulo capacity
    if count < capacity: count++

readOldestFirst(i):
    start = next if full, otherwise 0
    return data[(start+i) modulo capacity]
```
No dynamic memory is required. The trade-off is slightly more index logic when displaying the history.

### D. Prediction before implementation
After two million sequential values, both designs should retain the same last 50 values. Circular insertion should be faster because it writes one slot instead of shifting up to 49 values.

### E. Validation
Both implementations were compiled with C++17 and -O2 and received the same two-million-item sequence. Measured output:
```text
Shift array time: 22.186 ms
Circular buffer time: 9.473 ms
Same final 50 values: true
First retained: 1999950, last retained: 1999999
```
The circular buffer was faster in this run and the retained values matched. Timings vary by system; the complexity improvement is the primary evidence.

### F. Final evaluation
The objective was achieved. Both designs use O(k) storage and O(k) time to print the history. A full shift-array insertion costs O(k), while circular-buffer insertion costs O(1). A shift array may be easier to understand for tiny histories or rare updates. The circular buffer is better for frequent insertions and larger histories, with the trade-off of more complicated index handling.

## Overall conclusion
The work demonstrates function parameter semantics, safe reference lifetimes, overload resolution, class encapsulation, static shared state, friend access, inline optimisation and an evidence-based redesign. A design should be selected based on correctness, lifetime, maintainability and measured workload rather than syntax alone.

## References
1. Uploaded ASSIGNMENT 2.pdf, CO2 Q1–Q7 and submission requirements.
2. cppreference – C++ functions, references, overloads, classes, static members, friends and inline: https://en.cppreference.com/
3. GNU GCC documentation: https://gcc.gnu.org/onlinedocs/
4. cppreference – std::vector capacity and invalidation: https://en.cppreference.com/w/cpp/container/vector

## Viva preparation
Be ready to explain value/reference/pointer parameters; dangling references; overload selection and defaults; circular-buffer indexing; static members and lack of this; friend access and inline optimisation; and why Q7 changes insertion from O(k) to O(1).
