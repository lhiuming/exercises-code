# Test the libraries

# utils.h
set(utils_list "random" "io")
foreach(name ${utils_list})
  add_executable("test_${name}" "test_${name}.cpp")
endforeach(name)

# fundamentals.h
set(fundamentals_list "list" "stack")
foreach(name ${fundamentals_list})
  add_executable("test_${name}" "test_${name}.cpp")
endforeach(name)

# sort.h
set(sort_list "simple_sort" "heapsort")
foreach(name ${sort_list})
  add_executable("test_${name}" "test_${name}.cpp")
endforeach(name)

# search
set(search_list "symbol_table")
foreach(name ${search_list})
  add_executable("test_${name}" "test_${name}.cpp")
endforeach(name)
