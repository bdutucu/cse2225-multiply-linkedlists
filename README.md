# multiply-linkedlists

This project is a C implementation for performing arithmetic (specifically, addition) on arbitrarily large decimal numbers using doubly linked lists.  
It was developed as a homework assignment for a cse2225-Data Structures course.

## Project Purpose

- **Goal:**  
  To add two numbers (potentially with many digits and decimal points, i.e., "infinite" precision) that cannot be handled by standard C data types.
- **Data Structure Used:**  
  Doubly linked lists, where each node represents a single digit or the decimal point.

## How to Use

### Input

- You will be prompted to enter two decimal numbers.
- These numbers can be of any length and can include a decimal point (e.g., `12345678901234567890.123456789`).
- The program reads these numbers as input strings and converts them to linked lists for processing.

### Output

- The result of the addition is written to a file named `output.txt`.
- The sum is also printed on the console.

## Example

**Input:**  
```
Enter first number: 12345678901234567890.123
Enter second number: 98765432109876543210.877
```

**Output (in `output.txt` and console):**  
```
111111111011111111101.000
```

## File List

- `150124830_prj1.c` — Main C source file containing the doubly linked list implementation and addition logic.

## Compilation & Run

```sh
gcc 150124830_prj1.c -o multiply_linkedlists
./multiply_linkedlists
```

## Notes

- The program handles numbers much larger than the limits of standard integer or floating-point types.
- Both integer and fractional parts are supported.
- All dynamic memory is freed after use.

---
```