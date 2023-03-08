set(
  cpp_files
  "backspace_string_compare"
  "daily_temperatures"
  "longest_subarray"
  "make_the_string_great"
  "moving_average_from_data_stream"
  "number_of_recent_calls"
  "queue_example"
  "remove_all_adjacent_duplicates"
  "simplify_path"
  "sliding_window_maximum"
  "stack_example"
  "valid_parentheses"
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