# Ford-Johnson Algorithm (Merge-Insertion Sort)

A C++ implementation of the Ford-Johnson algorithm, also known as Merge-Insertion Sort.

## 📋 About

The algorithm is a hybrid sorting algorithm, famous for using a clever insertion sequence to minimize the number of comparisons.  
It's particularly interesting because it was one of the first algorithms proven to achieve the optimal number of comparisons for sorting.

For a detailed explanation and a step-by-step visualization of the Ford-Johnson sorting algorithm, see this article:  
https://dev.to/emuminov/human-explanation-and-step-by-step-visualisation-of-the-ford-johnson-algorithm-5g91

## 🚀 Features

- Implemented in C++98 standard
- Handles integer sorting
- Tracks the exact number of comparisons performed
- Measures and compares sorting performance across `containers`
- Educational implementation with clear code structure
- Makefile for easy compilation

## 🛠️ Building

To compile the project:

```bash
make
```
This will create an executable called algorithm.

## 💻 Usage
The current build configuration limits the sorting algorithm to around 3000 integers.  
To increase this capacity, modify the `LIMIT` macro definition within the Makefile to the required size.

Run the program with a list of integers to sort:
```bash
./algorithm [numbers...]
```
### Example
```bash
./algorithm 10 5 7 3 8 2 9 1 4 6
```

## 📚 Algorithm Details
- Time Complexity: `O(n*log(n))` comparisons
- Space Complexity: `O(n²)`
- Method: Specialized recursive algorithm using Jacobsthal number sequencing with binary search insertion

## 🔧 Requirements
C++98 compatible compiler (`g++`, `c++`)  
Make
