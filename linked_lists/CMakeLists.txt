set(
  cpp_files
  "doubly_linked_list"
  "find_node"
  "get_middle"
  "has_cycle"
  "middle_of_the_linked_list"
  "remove_duplicates_from_sorted_list"
  "reverse_linked_list_ii"
  "reversing_a_linked_list"
  "swap_nodes_in_pairs"
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