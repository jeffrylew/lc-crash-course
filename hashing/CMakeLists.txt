set(
  cpp_files
  "check_if_sentence_is_pangram"
  "find_numbers"
  "first_letter_to_appear_twice"
  "hash_map_ops"
  "missing_number"
  "two_sum"
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