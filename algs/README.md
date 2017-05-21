# Solutions to *Algorithms*

C++ solutions to some exercises, and implementation of algorithms listed in the
book *Algorithms*, 4th Edition, in C++. Implementation of algorithms are put in
[include](include/), and solutions are put in folders for each
chapters like [Chapter1](Chapter1/), [Chapter6](Chapter6/).

Yes, the book is written for **Java**, and this repository is written in
**C++** (or, more precisely, C++11, with full respect for C++14 or C++17
regarding deprecated stuffs).

## Notes

The utility library (utils/io.hpp, utils/random.hpp, etc.) is
subtly different from those provided by the book. Check the book author's
packages here: https://github.com/kevin-wayne/algs4.

## Todos

- Implement half of all algorithms and data structures
  - at least the most important ones.
- Implement some of the most interesting algorithms from the exercise.
- work on the Chapter 6.

## Implemented Algorithms and Data Structures

### [Fundamentals](include/fundamentals/)

1. Linked List ([list.hpp](include/fundamentals/list.hpp))
0. Stack (with linked-list) ([stack.hpp](include/fundamentals/stack.hpp))

### [Sorting](include/sorting/)

1. Selection sort ([simple_sort.hpp](include/sorting/simple_sort.hpp))
0. Insertion sort ([simple_sort.hpp](include/sorting/simple_sort.hpp))
0. Shellsort ([simple_sort.hpp](include/sorting/simple_sort.hpp))
0. Mergesort ([mergesort.hpp](include/sorting/mergesort.hpp))
0. Heapsort (and Priority Queue) ([heapsort.hpp](include/sorting/heapsort.hpp))

### [Symbol Tables](include/symbol_tables/)

1. Binary search (Symbol Table) ([binary.hpp](include/symbol_tables/binary.hpp))
0. Binary Search Tree ([binary_tree.hpp](include/symbol_tables/binary_tree.hpp))

### Graphs

### Strings

<!-- Algorithms and Data Structures : Complete List

-- Chapter 1, basics --
1. Stack (with resizing array) (todo)
0. Stack (with linked-list)
0. FIFO queue (todo)
0. Bag (todo)

-- Chapter 2, sort  --
1. Selection sort
2. Insertion sort
3. Shellsort
4. Top-down mergesort
5. Bottom-up mergesort
6. Quicksort (todo)
7. Quicksort with 3-way partitioning (todo)
8. Priority Queue
9. Heapsort

-- Chapter 3, search--
1. Sequential Search Symbol Table (todo)
9. Binary Search Symbol Table
11. Binary Search Tree Symbol Table class
12. Red-black Binary Search Tree Symbol Table class (todo)
    - @NOTE: Implement a complete RBBST if schedule allows.
    - @NOTE: Try to refer to the STL implementation.
13. Separate Chaining Hash Symbol Table (todo)
14. Linear Probing Hash Symbol Table (todo)

-- Chapter 4, graph --
1. Adjacency-list Graph class (todo)
    - Linked-list Bag class (todo)
16. Depth-first search for paths (todo)
17. Breadth-first search for paths (todo)
18. Depth-first search for connected components (todo)
19. Adjacency-list Directed Digraph class (todo)
20. Reachability / Directed Depth-first search (todo)
    - Depth-first directed paths (todo)
    - Breadth-first directed paths (todo)
21. Directed cycle (todo)
22. Depth-first Order (todo)
23. Topological sort (todo)
24. Kosaraju strong connected components (todo)
-- weighted graph --
25. Edge Weighted Graph class (todo)
    - Edge class (todo)
26. Lazy version of Prim's MST (todo)
27. Eager version of Prim's MST (todo)
-- weighted directed graph --
28. Edge-weighted Directed Graph class (todo)
    - Directed Weighted Edge class (todo)
29. Dijkstra's shortest-path (todo)
30. Shortest-path in edge-weighted DAG (todo)
31. Bellman-ford shortest-path (todo)

-- Chapter 5, strings --
1. Least-significant-digit-first string sort (todo)
33. Most-significant-digit-first string sort (todo)
34. Three-way string quicksort (todo)
-- trie --
35. Trie Symbol Table class (todo)
36. Ternary Search Trie Symbol Table (todo)
-- substring search --
37. Knuth-Morris-Pratt substring search (todo)
    - @NOTE: very hard to understand; worthwhile to implement.
38. Boyer-Moore substring search (todo)
39. Rabin-Karp fingerprint search (todo)
40. Regular expression pattern matching (todo)
-- data compression --
41. Huffman compression (todo)
42. LZW compression and expansion (todo)

## Addition Algorithms List

1. Quick-select (todo; page 346)

-->
