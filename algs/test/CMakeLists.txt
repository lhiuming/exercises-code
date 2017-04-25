# Test the libraries

# sort.h
set(sort_list "heapsort")
foreach(name ${sort_list})
  add_executable("test_${name}" "test_${name}.cpp")
endforeach(name)

# utils.h
set(utils_list "random")
foreach(name ${utils_list})
  add_executable("test_${name}" "test_${name}.cpp")
endforeach(name)
