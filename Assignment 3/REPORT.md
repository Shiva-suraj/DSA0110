# CO3 Assignment 3 – Expanded Report

**Name:** A. Siva suraj sai  
**Register Number:** 192425276  
**Compiler:** GNU g++ 14.2.0, C++17  
**Repository:** https://github.com/Shiva-suraj/DSA0110/tree/main/Assignment%203

> The supplied PDF is titled Assignment 3 and contains seven main questions (Q1–Q7), not twelve. This report follows the uploaded PDF, including its additional code-completion, output-prediction, experiment and alternative-complexity requirements.

## Q1 – Constructors and constructor overloading (6 marks)

### Problem and design
A library needs to create an empty Book record, a donated book with only a title, and a complete record with title, copy count and author. The class uses a default constructor, an explicit title constructor, a two-argument overload and a full constructor. The shorter constructors delegate to the full constructor, so common initialisation and validation are kept in one place. Every constructor uses a member initializer list.

### Pseudocode
1. Define Book fields: title, copies and author.
2. Default constructor delegates with safe values.
3. Title constructor delegates with one copy and unknown author.
4. Two-argument constructor delegates with unknown author.
5. Full constructor initialises all fields and calls validation.
6. If copies are negative, throw invalid_argument.
7. Create and print one object through each constructor; test a negative value.

### Output
```text
Title: Untitled, Copies: 0, Author: Unknown
Title: The Alchemist, Copies: 1, Author: Unknown
Title: Clean Code, Copies: 4, Author: Robert C. Martin
Rejected: number of copies cannot be negative
```

### Explanation and evaluation
A compiler-generated default constructor is available only when no constructor has been declared by the programmer. Declaring a parameterised constructor suppresses the implicit default constructor; therefore, an array such as `Book shelf[3]` fails to compile if Book has no no-argument constructor.

Member initializer lists directly initialise members. Assigning in the constructor body first default-constructs class-type members and then assigns to them. Initializer lists are also required for const members, references and members that do not have a default constructor.

Members are initialised in class declaration order, not the textual order of the initializer list. The separate reorder demonstration intentionally reverses the list and produces `-Wreorder`; it also shows why reading a later member before its initialisation is unsafe.

The title constructor is marked `explicit` to prevent unintended implicit conversion. Direct initialisation `Book b("Novel")` is allowed, while copy-initialisation `Book b = "Novel"` is rejected when the constructor is explicit. The negative-copy test confirms invalid state is rejected before a usable Book object is created.

### Test cases
| Test | Action | Expected/observed result |
|---|---|---|
| 1 | Default construction | Safe empty values |
| 2 | Title-only construction | One copy, unknown author |
| 3 | Full construction | Supplied values retained |
| 4 | Negative copies | invalid_argument caught |
| 5 | Array after removing default constructor | Compiler error: no matching Book() |
| 6 | Reverse initializer-list order | -Wreorder warning |

### Alternative and complexity
One constructor with default arguments could represent all three creation forms. Validation would remain in that constructor. Both approaches require constant work for fixed-size members: O(1) time and O(1) auxiliary space. Overloads with delegation communicate the creation cases more clearly and avoid repeating validation.

## Q2 – Copy constructors: shallow and deep copies (7 marks)

### Problem and implementation
Prescription owns a dynamically allocated array of medicine names. The deep-copy constructor allocates a new array and copies every medicine. Copy assignment checks self-assignment, allocates and fills replacement storage before deleting the old array, then returns `*this`. The destructor uses `delete[]`.

### Pseudocode
```text
COPY CONSTRUCTOR(other):
    allocate a new array of other.count strings
    copy each medicine
COPY ASSIGNMENT(other):
    if this != address(other):
        allocate replacement array
        copy all medicines into replacement
        delete old array
        take ownership of replacement
    return *this
DESTRUCTOR:
    delete[] medicines
```

### Memory diagrams
Shallow copy (wrong):
```text
p.medicines ----+
                +----> [Paracetamol | ORS]
q.medicines ----+
```
Both objects own the same pointer. A modification through q changes what p sees, and both destructors attempt to delete the same allocation. This can cause a double-free crash.

Deep copy (correct):
```text
p.medicines --------> [Paracetamol | ORS]
q.medicines --------> [Paracetamol | Cetirizine]
r.medicines --------> [Paracetamol | ORS]
```
Each object has its own allocation, so changes do not affect another object.

### Rule of Three and copy situations
A class that manually owns a resource generally needs a destructor, copy constructor and copy assignment operator. These three functions define how the resource is released, duplicated into a new object and replaced in an existing object. A copy constructor can be called when initialising from another object, passing an object by value, or returning an object by value when copy elision does not remove the copy. Passing by const reference does not copy the object.

### Output and tests
```text
[copy constructor: 2 items]
Ibuprofen ORS | Paracetamol Cetirizine | Paracetamol ORS
Self-assignment safe: Paracetamol
[copy constructor: 2 items]
Inside byValue, count=2
Inside byReference, count=2
```
The q modification does not change p. Assignment r=p creates independent storage. Self-assignment retains the original medicine. Passing by value triggers a copy; passing by const reference does not. The correct program was run with AddressSanitizer/UndefinedBehaviorSanitizer without a diagnostic. A separate intentionally shallow-copy program produced an AddressSanitizer double-free report.

### Complexity and alternative
Copying n medicine names requires O(n) time and O(n) extra space (more precisely, time is proportional to the total number of characters copied). A shallow pointer copy is O(1), but it is incorrect for independent ownership. Using `std::vector<std::string>` gives deep value-copy behaviour automatically and follows the Rule of Zero; the compiler-generated copy operations are then suitable.

## Q3 – Dynamic constructors and destructors (7 marks)

### Design
Event creates a two-dimensional seat map dynamically. The outer pointer array stores row addresses and each row has its own char array. B means booked and a dot means available. The destructor deletes each row and then the pointer array. Copying is disabled to prevent accidental shallow copying of the owning pointer.

### Pseudocode
1. Validate dimensions and treat negative dimensions as zero.
2. Allocate row-pointer array when both dimensions are positive.
3. Allocate and initialise each row.
4. If an allocation fails, release all completed rows and rethrow.
5. Book/cancel only when row and seat indices are valid.
6. Destructor releases every row and the row-pointer array.

### Memory layout
```text
map -> [row0 pointer | row1 pointer | ...]
          |              |
          v              v
        [. B .]        [. . B] ... [rowN]
```
For positive dimensions, memory is approximately rows × seats bytes plus rows × sizeof(char*) for row pointers. The implementation makes rows+1 allocations.

### Predict-the-output question (prediction written first)
Predicted Logger output:
```text
+A +B -B copyAc use -Ac +P -P end -A
```
Explanation: A is constructed first. B is constructed in the nested block and destroyed at block exit. Passing a to use by value constructs Ac; use prints, then the parameter is destroyed. P is dynamically constructed and destroyed by delete. The word end is printed, then local A is destroyed at main exit. The executed program produced exactly the predicted sequence.

### Lifetime, safety and tests
Local objects are destroyed automatically when their scope ends, in reverse construction order. A block object is destroyed at block exit. A heap object remains alive until delete. Forgetting delete leaks memory. An array allocated with new[] must be released with delete[], not scalar delete. A destructor has no parameters and no return type, so it cannot be overloaded.

The seat-map program tested stack, block-scope and heap objects, booking, cancellation and zero rows. The correct program passed AddressSanitizer/UndefinedBehaviorSanitizer. A separate intentional missing-delete program caused LeakSanitizer to report a 400-byte leak. This is a negative demonstration, not the correct implementation.

### Alternative and complexity
A contiguous allocation can store seats at index `r * seats + s`. It requires one allocation rather than rows+1 and removes the row-pointer overhead; access remains O(1). A vector<vector<char>> is safer and convenient but may allocate each row separately. Construction/destruction are O(rows × seats); an individual seat lookup, booking or cancellation is O(1).

## Q4 – Arithmetic and stream operator overloading (7 marks)

### Design and pseudocode
Money stores total paise in a long long, avoiding binary floating-point rounding for ordinary two-decimal currency. Addition and subtraction return new objects. += modifies the left object and returns a reference. Equality and less-than compare paise. Stream insertion is a non-member friend because the left operand is ostream; extraction is also a friend to read values.

```text
PLUS(a,b): return Money(a.paise + b.paise)
MINUS(a,b): return Money(a.paise - b.paise)
PLUS_ASSIGN(a,b): update a; return a by reference
EQUAL(a,b): compare paise values
OUTPUT(m): print rupees and exactly two paise digits
```

### Output
```text
Rs 200.00
true
Paise carry: Rs 1.25
Negative balance: -Rs 1.25
```
Rs 120.75 + Rs 79.25 = Rs 200.00. Rs 0.75 + Rs 0.50 carries into one rupee and gives Rs 1.25.

### Explanation and engineering decision
For member addition, `a+b` is interpreted as `a.operator+(b)`. + returns a new object and does not change operands. += returns `Money&` to `*this`, supporting chained updates. << must be a non-member because the left operand is an output stream, not Money. Multiplying one Money by another Money is not usually meaningful because the unit becomes currency squared; multiplying Money by a numeric quantity is meaningful. The sample permits negative values and prints a minus sign; a real billing system should explicitly decide whether negative balances mean refunds/credits or must be rejected.

### Alternative and complexity
Friend non-member arithmetic can support symmetric expressions such as numeric-left-operand plus Money if suitable overloads/conversions are supplied. Named functions add() and equals() are also possible but less natural for arithmetic. Each operation is O(1) time and O(1) space. A double implementation can accumulate rounding errors; integer paise is safer for two-decimal amounts. Benchmark timings for one million operations depend on compiler, optimisation and hardware.

## Q5 – Increment, comparison and subscript operators (6 marks)

### Design and pseudocode
Time stores total seconds, which makes increment and hour/minute rollover straightforward. Prefix ++ increments and returns a reference to the changed object. Postfix ++ saves the old value, increments the object and returns the saved copy. The dummy int parameter distinguishes postfix. Playlist overloads [] in const and non-const forms and check the index before access.

### Predict-the-output question
Predicted Counter output:
```text
5 7 7
```
Starting from 5, c++ copies 5 to a and then increments c to 6. ++c increments to 7 and returns the updated object, so b=7 and c=7. The executed program matched the prediction.

### Verified playlist tests
The program verifies prefix/postfix values, comparison, 59:59 to 1:00:00 rollover, editable playlist entries and invalid indices. Both playlist[-1] and playlist[size] should throw std::out_of_range. The const overload returns a const reference; the mutable overload returns a modifiable reference.

### Complexity and alternative
Checked operator[] and at(i) are O(1), with a bounds comparison and branch. An unchecked subscript avoids the check but invalid access is undefined behaviour. Prefix and postfix are O(1) for this small Time object, but postfix makes an old-value copy. ++i is commonly preferred for class types when the old value is not needed. Timing 10,000,000 operations at -O0 and -O2 must be measured on the same computer because compiler optimisation changes the result.

## Q6 – Rules of operator overloading (7 marks)

### Design and pseudocode
Text owns a dynamically allocated null-terminated character array. It implements a constructor, deep-copy constructor, copy assignment, destructor, concatenation, ==, != and stream insertion.

```text
CONSTRUCT(s): allocate length(s)+1 and copy string
COPY(other): allocate separate buffer and copy characters
ASSIGN(other): if not self, allocate replacement, copy, release old buffer
DESTRUCT: delete[] buffer
PLUS(other): allocate combined length, concatenate and return a Text
COMPARE: use string comparison for equality/inequality
```

### Output and tests
```text
Hello World!
Empty text: []
Self assignment: Hello
a==same: true, a!=b: true
This is a longer message used to test dynamic character storage safely.
```
Empty input, long input, concatenation and self-assignment were tested. The correct program passed AddressSanitizer/UndefinedBehaviorSanitizer.

The operators `::`, `.`, `.*`, `?:` and `sizeof` cannot be overloaded. Overloading cannot change precedence, associativity or arity. At least one operand must be a user-defined type. operator= must be a non-static member. Friend functions are useful for non-member operators that need private access, especially stream insertion.

The expression a+b+c creates intermediate concatenation values. Exact copy-constructor counts can vary because copy elision/NRVO is permitted; record the actual compiler and flags if reporting a measured count.

### Alternative and complexity
std::string is preferred in production because it manages allocation and copying. For (a+b)+c with lengths n1, n2 and n3, the first concatenation copies roughly n1+n2 characters and the second roughly n1+n2+n3. Total character copying is approximately 2n1+2n2+n3. Time and temporary storage are O(n1+n2+n3) for this fixed chain. Using += on a copied left operand is another implementation; move semantics and elision can reduce temporary costs.

## Q7 – Complex-number class and AC impedance (10 marks)

### Stage 1 – Requirements
Store real and imaginary parts as doubles. Provide default, real-only and real-plus-imaginary constructors. Implement +, -, *, /, == and <<, plus magnitude. Division by zero must be handled safely.

### Stage 2 – Formulas
For z1=a+jb and z2=c+jd:
- Addition: (a+c)+j(b+d)
- Subtraction: (a-c)+j(b-d)
- Multiplication: (ac-bd)+j(ad+bc)
- Division: ((ac+bd)/(c²+d²))+j((bc-ad)/(c²+d²))
- Magnitude: sqrt(a²+b²)

Arithmetic operators are members because the left operand is Complex. << is a friend non-member because the left operand is ostream.

### Stage 3 – Hand calculation
Use R=10 ohms, angular frequency ω=1000 rad/s, L=0.01 H and C=10 microfarads.
- Resistor: ZR=10+j0 ohms.
- Inductor: ZL=jωL=j10 ohms.
- Capacitor: ZC=-j/(ωC)=-j100 ohms.
- Series: Z=ZR+ZL+ZC=10-j90 ohms.
- Magnitude: sqrt(10²+90²)=sqrt(8200)=90.55 ohms.
- Parallel R-L: (10 × j10)/(10+j10)=5+j5 ohms; magnitude=7.07 ohms.

### Output
```text
R = 10.00 + j0.00, |R| = 10.00
Series RLC impedance = 10.00 - j90.00, magnitude = 90.55
Parallel R-L impedance = 5.00 + j5.00, magnitude = 7.07
Safe error: division by zero impedance
```

### Stage 4 – Evaluation and alternative
std::complex<double> is the standard, well-tested type and is usually preferred in production. The custom class demonstrates operator overloading and allows custom output and division-by-zero policy. Floating-point equality needs a tolerance; the implementation uses 1e-9. A limitation is that this educational calculator does not model component tolerances, measurement uncertainty or numerical conditioning.

Both the custom class and std::complex<double> use two doubles and perform each basic arithmetic operation in O(1) time and O(1) space. The standard type reduces maintenance and is broadly tested; the custom type gives control but requires more testing.

## Overall conclusion
Constructors establish valid object state, destructors release owned resources, copy operations define ownership, and operator overloading makes user-defined values natural to use. Raw owning pointers require careful copy/destruction control (Rule of Three). Standard containers and strings often allow the Rule of Zero. Operators should preserve familiar meanings and avoid surprising behaviour.

## References
1. Uploaded CO3 Assignment 3 PDF, Q1–Q7 and submission instructions.
2. cppreference.com – C++ constructors, copy constructors, destructors and operator overloading.
3. cppreference.com – std::string, std::vector and std::complex.
4. GNU Compiler Collection documentation – g++ warning options and sanitizers.

## Viva preparation
Be ready to explain constructor delegation, declaration-order initialisation, explicit, shallow versus deep copy, Rule of Three/Zero, RAII, delete[] pairing, prefix versus postfix, stream operator placement, operator-overloading restrictions, and the Big-O costs of copying and concatenation.
