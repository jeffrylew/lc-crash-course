cmake_minimum_required(VERSION 3.14)
project(add-wrinkles-to-brain)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(arrays_and_strings)
add_subdirectory(hashing)
add_subdirectory(linked_lists)
add_subdirectory(stacks_and_queues)
add_subdirectory(trees_and_graphs)
# add_subdirectory(heaps)
# add_subdirectory(greedy)
# add_subdirectory(binary_search)
# add_subdirectory(back_tracking)
# add_subdirectory(dynamic_programming)
# add_subdirectory(bonus)