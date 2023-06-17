set(
  cpp_files
  "01_matrix"
  "all_nodes_distance_k_in_binary_tree"
  "binary_tree_right_side_view"
  "binary_tree_zigzag_level_order_traversal"
  "build_graph"
  "closest_binary_search_tree_value"
  "count_good_nodes_in_binary_tree"
  "deepest_leaves_sum"
  "dfs"
  "diameter_of_binary_tree"
  "find_if_path_exists_in_graph"
  "find_largest_value_in_each_tree_row"
  "inorder_dfs"
  "insert_into_a_binary_search_tree"
  "keys_and_rooms"
  "lowest_common_ancestor"
  "max_area_of_island"
  "maximum_depth_of_binary_tree"
  "maximum_difference_between_node_and_ancestor"
  "minimum_absolute_difference_in_bst"
  "minimum_depth_of_binary_tree"
  "minimum_number_of_vertices_to_reach_all_nodes"
  "nearest_exit_from_entrance_in_maze"
  "number_of_connected_components_in_an_undirected_graph.cpp"
  "number_of_islands"
  "number_of_provinces"
  "open_the_lock"
  "path_sum"
  "postorder_dfs"
  "preorder_dfs"
  "print_all_nodes"
  "range_sum_of_bst"
  "reachable_nodes_with_restrictions"
  "reorder_routes_to_make_all_paths_lead_to_the_city_zero"
  "shortest_path_in_a_grid_with_obstacles_elimination"
  "shortest_path_in_binary_matrix"
  "shortest_path_with_alternating_colors"
  "snakes_and_ladders"
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