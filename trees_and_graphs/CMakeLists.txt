set(
  cpp_files
  "binary_tree_right_side_view"
  "binary_tree_zigzag_level_order_traversal"
  "build_graph"
  "closest_binary_search_tree_value"
  "count_good_nodes_in_binary_tree"
  "deepest_leaves_sum"
  "dfs"
  "diameter_of_binary_tree"
  "find_largest_value_in_each_tree_row"
  "inorder_dfs"
  "insert_into_a_binary_search_tree"
  "keys_and_rooms"
  "lowest_common_ancestor"
  "maximum_depth_of_binary_tree"
  "maximum_difference_between_node_and_ancestor"
  "minimum_absolute_difference_in_bst"
  "minimum_depth_of_binary_tree"
  "minimum_number_of_vertices_to_reach_all_nodes"
  "number_of_islands"
  "number_of_provinces"
  "path_sum"
  "postorder_dfs"
  "preorder_dfs"
  "print_all_nodes"
  "range_sum_of_bst"
  "reorder_routes_to_make_all_paths_lead_to_the_city_zero"
  "validate_binary_search_tree"
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