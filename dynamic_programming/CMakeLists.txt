set(
  cpp_files
  "climbing_stairs"
  "fibonacci_numbers"
  "house_robber"
  "longest_increasing_subsequence"
  "min_cost_climbing_stairs"
  "solving_questions_with_brainpower"
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
