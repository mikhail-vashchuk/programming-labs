
# Lab — Selection sort with constraints (22 real numbers)

## Task
Given 22 real numbers. Sort **positive elements** that are located on **odd positions** (positions counted from 1) in **ascending order**.
All other elements must remain in their original places. Sorting method: **selection sort**.

## Solution idea
- Positions in the statement are 1-based, so odd positions (1,3,5,...) correspond to indices (0,2,4,...) in C++.
- Only elements that satisfy:
  - `value > 0`
  - `index % 2 == 0`
  participate in sorting.
- Other elements are never moved.

## Build & Run (macOS/Linux)
```bash
cmake -S . -B build
cmake --build build
./build/app