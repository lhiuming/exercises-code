# Build Chapter 2 solutions

set(solution_list
  "2.2.17.LinkedListMergeSort"
)

foreach (solution ${solution_list})
  add_executable(${solution} ${solution}.cpp)
endforeach(solution)
