set(
  cpp_files
  "backspace_string_compare"
  "make_the_string_great"
  "number_of_recent_calls"
  "queue_example"
  "remove_all_adjacent_duplicates"
  "simplify_path"
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