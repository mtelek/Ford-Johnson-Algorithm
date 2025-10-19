# Ford-Johnson Algorithm (Merge-Insertion Sort)

A C++ implementation of the Ford-Johnson algorithm, also known as Merge-Insertion Sort.

## 📋 About

The Ford-Johnson algorithm is a comparison-based sorting algorithm that combines merge and insertion sort strategies. It's particularly interesting because it was one of the first algorithms proven to achieve the optimal number of comparisons for sorting.

## 🚀 Features

- Implemented in C++98 standard
- Handles integer sorting
- Educational implementation with clear code structure
- Makefile for easy compilation

## 🛠️ Building

To compile the project:

```bash
make
```
This will create an executable called algorithm.

## 💻 Usage
Run the program with a list of integers to sort:
```bash
./algorithm [numbers...]
```
### Examples
```bash
./algorithm 5 2 8 1 9
./algorithm 3 2 1
./algorithm 10 5 7 3 8 2 9 1 4 6
```

## 📚 Algorithm Details
- Time Complexity: O(n log n) comparisons
- Space Complexity: O(n)
- Method: Combination of merge sort and insertion sort

## 🔧 Requirements
C++98 compatible compiler (g++, c++)  
Make
