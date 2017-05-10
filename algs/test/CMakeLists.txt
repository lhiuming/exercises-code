# Test the libraries

# utils.h
set(utils_list "random" "io")
foreach(name ${utils_list})
  add_executable("test_${name}" "test_${name}.cpp")
endforeach(name)

# fundamentals.hpp
set(fundamentals_list "list" "stack")
foreach(name ${fundamentals_list})
  add_executable("test_${name}" "test_${name}.cpp")
endforeach(name)

# sorting.hpp
set(sort_list "simple_sort" "heapsort")
foreach(name ${sort_list})
  add_executable("test_${name}" "test_${name}.cpp")
endforeach(name)

# symbol_tables.hpp
set(st_list "binary" "bst")
foreach(name ${st_list})
  add_executable("test_${name}" "test_${name}.cpp")
endforeach(name)
