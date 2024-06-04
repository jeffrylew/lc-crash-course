set(
  cpp_files
  "brightest_position_on_street"
  "build_trie"
  "car_pooling"
  "find_the_divisibility_array_of_a_string"
  "hamming_distance"
  "implement_trie"
  "insert_interval"
  "maximum_product_after_k_increments"
  "meeting_rooms"
  "merge_intervals"
  "n_queens_ii"
  "search_suggestions_system"
  "single_number"
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
