cmake_minimum_required (VERSION 3.0)
project (ALGS)

#--------------------
# Add subdirectories
#--------------------

# Include idrectory
include_directories(${PROJECT_SOURCE_DIR}/include)

# Set compile flags
set(CMAKE_CXX_FLAGS "-g -O3 -Wall -std=c++11")

# Build the tests
enable_testing ()
add_subdirectory(test)

# Build each Chapters
add_subdirectory(Chapter2)
add_subdirectory(Chapter6)
