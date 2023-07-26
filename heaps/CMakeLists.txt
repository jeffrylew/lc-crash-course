set(
  cpp_files
  "find_median_from_data_stream"
  "heap_ops"
  "kth_largest_element_in_a_stream"
  "last_stone_weight"
  "minimum_cost_to_connect_sticks"
  "minimum_operations_to_halve_array_sum"
  "remove_stones_to_minimize_total"
  "top_k_frequent_elements"
)

foreach(cpp_file IN ITEMS ${cpp_files})
  add_executable(
    ${cpp_file}_test
    ${cpp_file}.cpp
  )

  target_link_libraries(
    ${cpp_file}_test
    PRIVATE
    gtest_main
  )
endforeach()

include(GoogleTest)

foreach(cpp_file IN ITEMS ${cpp_files})
  gtest_discover_tests(${cpp_file}_test)
endforeach()