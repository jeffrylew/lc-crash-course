set(
  cpp_files
  "best_time_to_buy_and_sell_stock_iv"
  "climbing_stairs"
  "coin_change"
  "fibonacci_numbers"
  "house_robber"
  "longest_common_subsequence"
  "longest_increasing_subsequence"
  "maximum_value_of_k_coins_from_piles"
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
