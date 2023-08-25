set(
  cpp_files
  "boats_to_save_people"
  "destroying_asteroids"
  "how_many_apples_can_you_put_into_the_basket"
  "ipo"
  "least_number_of_unique_integers_after_k_removals"
  "maximum_69_number"
  "maximum_units_on_a_truck"
  "partition_array_such_that_max_diff_is_k"
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