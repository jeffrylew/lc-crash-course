set(
  cpp_files
  "binary_tree_right_side_view"
  "count_good_nodes_in_binary_tree"
  "deepest_leaves_sum"
  "dfs"
  "diameter_of_binary_tree"
  "find_largest_value_in_each_tree_row"
  "inorder_dfs"
  "lowest_common_ancestor"
  "maximum_depth_of_binary_tree"
  "maximum_difference_between_node_and_ancestor"
  "minimum_depth_of_binary_tree"
  "path_sum"
  "postorder_dfs"
  "preorder_dfs"
  "print_all_nodes"
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