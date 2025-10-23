SortedTree
==========

What this repository contains
----------------------------
- src/bst.hpp, src/bst.cpp: An implementation of a sorted, in-memory binary search tree that supports `put(const key_t&, const value_t&)` and `get(const key_t&) -> value_t`.
  - The implementation uses a hand-written node-based binary search tree (BST) with lexicographic comparison of byte arrays.
  - Node ownership has been refactored to use `std::unique_ptr` and concurrency control uses `std::shared_mutex` for reader-writer locking.
- tests/: doctest-based unit tests that validate functionality, including string-key helpers and concurrent access tests.
- CMakeLists.txt and build/ files to build the project and tests.

Design choices and rationale
---------------------------
Chosen data structure: Binary Search Tree (BST)
SortedTree — short summary
==========================

What this repo is
-----------------
- A hand-written sorted in-memory tree implementing only `put(const key_t&, const value_t&)` and `get(const key_t&) -> value_t`.
- Keys/values are byte arrays (`std::vector<uint8_t>`).
- Current implementation: simple binary search tree (BST) with lexicographic comparison.
- Safety and concurrency: `std::unique_ptr` for node ownership and `std::shared_mutex` for reader-writer locking.

Why BST
-------
- Easy to implement from scratch (fits the task requirement).
- Simple semantics for `put` and `get` and easy to extend (e.g., add AVL balancing later).

Build & run tests
-----------------
From repo root (PowerShell):

```powershell
cmake -S . -B build
cmake --build build --config Debug --target bst_tests
& "${PWD}\build\tests\Debug\bst_tests.exe"
```

Notes
-----
- BST is not balanced; for guaranteed O(log n) consider AVL/Red‑Black (can be added on a feature branch).
- Changes are small and incremental (good to present in an interview): memory-safety (`unique_ptr`) and better read concurrency (`shared_mutex`).

If you'd like, I can add a one-page "presenter's notes" or implement AVL balancing next on a feature branch.

