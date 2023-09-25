set(
  cpp_files
  "binary_search"
  "binary_search_templates"
  "koko_eating_bananas"
  "longest_subsequence_with_limited_sum"
  "search_a_2d_matrix"
  "search_input_position"
  "successful_pairs_of_spells_and_potions"
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