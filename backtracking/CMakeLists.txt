set(
  cpp_files
  "all_paths_from_source_to_target"
  "combinations"
  "combination_sum"
  "generate_parentheses"
  "letter_combinations_of_a_phone_number"
  "n_queens_ii"
  "permutations"
  "subsets"
  "word_search"
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
