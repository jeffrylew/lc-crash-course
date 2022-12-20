set(
  cpp_files
  "answer_queries"
  "check_if_palindrome"
  "check_for_target"
  "combine"
  "find_best_subarray"
  "find_length"
  "find_length_of_binary_str"
  "is_subsequence"
  "maximum_average_subarray"
  "max_consecutive_ones_3"
  "num_subarray_product_less_than_k"
  "number_of_ways_to_split_array"
  "reverse_string"
  "running_sum_of_1d_array"
  "squares_of_a_sorted_array"
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