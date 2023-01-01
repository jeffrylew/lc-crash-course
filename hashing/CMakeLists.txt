set(
  cpp_files
  "are_occurrences_equal"
  "check_if_sentence_is_pangram"
  "count_number_of_nice_subarrays"
  "counting_elements"
  "find_longest_substring"
  "find_numbers"
  "find_players_with_zero_or_one_losses"
  "first_letter_to_appear_twice"
  "group_anagrams"
  "hash_map_ops"
  "intersection_of_multiple_arrays"
  "largest_unique_number"
  "maximum_number_of_balloons"
  "maximum_sum"
  "minimum_consecutive_cards_to_pick_up"
  "missing_number"
  "subarray_sum_equals_k"
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