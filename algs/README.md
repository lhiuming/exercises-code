# Solutions to *Algorithms*

C++ solutions to some exercises, and implementation of algorithms listed in the
book *Algorithms*, 4th Edition, in C++. Implementation of algorithms are put in
[include](include/), and solutions are put in folders for each
chapters like [Chapter1](Chapter1/), [Chapter6](Chapter6/).

## Notes

The utility library (utils/io.hpp, utils/random.hpp, etc.) is
subtly different from those provided by the book. Check the book author's
packages here: https://github.com/kevin-wayne/algs4.

## Todos

- Implement half of all algorithms and data structures
  - at least the most important ones.
- work on the Chapter 6, and implement some algorithms in the mean time in need.
- Review the skipped (and possibly interesting) exercises.

## Implemented Algorithms and Data Structures

### Data Collections

1. Linked List (forward list) ([list.hpp](include/collections/list.hpp))

### Sort ([sort.h](include/sort.h))

1. Selection sort ([simple_sort.hpp](include/sort/simple_sort.hpp))
2. Insertion sort ([simple_sort.hpp](include/sort/simple_sort.hpp))
3. Shellsort ([simple_sort.hpp](include/sort/simple_sort.hpp))
4. Priority Queue (and Heapsort) ([heapsort.hpp](include/sort/heapsort.hpp))

### Search

1. Binary search (Symbol Table) ([binary.hpp](include/search/binary.hpp))

## Basic Algorithms and Data Structures List

<!-- Chapter 1, basics -->
0. Linked List
1. Bag, FIFO queue, LIFO stack (todo)

<!-- Chapter 2, sort  -->
1. Selection sort
2. Insertion sort
3. Shellsort
4. Top-down mergesort (todo)
5. Bottom-up mergesort (todo)
6. Quicksort (todo)
7. Quicksort with 3-way partitioning (todo)
8. Priority Queue
9. Heapsort

<!-- Chapter 3, search-->
9. Sequential Search Symbol Table (won't do)
9. Binary Search Symbol Table
11. Binary Search Tree Symbol Table class (todo)
12. Red-black Binary Search Tree Symbol Table class (todo)
    - @NOTE: Implement a complete RBBST if schedule allows.
13. Separate Chaining Hash Symbol Table (todo)
14. Linear Probing Hash Symbol Table (todo)

<!-- Chapter 4, graph -->
15. Adjacency-list Graph class (todo)
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
<!-- weighted graph -->
25. Edge Weighted Graph class (todo)
  - Edge class (todo)
26. Lazy version of Prim's MST (todo)
27. Eager version of Prim's MST (todo)
<!-- weighted directed graph -->
28. Edge-weighted Directed Graph class (todo)
  - Directed Weighted Edge class (todo)
29. Dijkstra's shortest-path (todo)
30. Shortest-path in edge-weighted DAG (todo)
31. Bellman-ford shortest-path (todo)

<!-- Chapter 5, strings -->
32. Least-significant-digit-first string sort (todo)
33. Most-significant-digit-first string sort (todo)
34. Three-way string quicksort (todo)
<!-- trie -->
35. Trie Symbol Table class (todo)
36. Ternary Search Trie Symbol Table (todo)
<!-- substring search -->
37. Knuth-Morris-Pratt substring search (todo)
  - @NOTE: very hard to understand; worthwhile to implement.
38. Boyer-Moore substring search (todo)
39. Rabin-Karp fingerprint search (todo)
40. Regular expression pattern matching (todo)
<!-- data compression -->
41. Huffman compression (todo)
42. LZW compression and expansion (todo)

## Addition Algorithms List

- Quick-select (todo; page 346)
