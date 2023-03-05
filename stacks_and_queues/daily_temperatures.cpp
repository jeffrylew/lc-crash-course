#include <gtest/gtest.h>

#include <stack>
#include <vector>

static std::vector<int> dailyTemperatures(std::vector<int> temperatures)
{
    std::stack<int>  stack {};
    std::vector<int> answer(temperatures.size());

    for (int i = 0; i < temperatures.size(); ++i)
    {
        while (not stack.empty() && temperatures[stack.top()] < temperatures[i])
        {
            int j = stack.top();
            answer[j] = i - j;
            stack.pop();
        }

        stack.push(i);
    }

    return answer;
}

TEST(DailyTemperaturesTest, TestCase1)
{
    const std::vector<int> input {73, 74, 75, 71, 69, 72, 76, 73};
    const std::vector<int> expected_output {1, 1, 4, 2, 1, 1, 0, 0};
    
    EXPECT_EQ(expected_output, dailyTemperatures(input))
}

TEST(DailyTemperaturesTest, TestCase2)
{
    const std::vector<int> input {30, 40, 50, 60};
    const std::vector<int> expected_output {1, 1, 1, 0};
    
    EXPECT_EQ(expected_output, dailyTemperatures(input))
}

TEST(DailyTemperaturesTest, TestCase3)
{
    const std::vector<int> input {30, 60, 90};
    const std::vector<int> expected_output {1, 1, 0};
    
    EXPECT_EQ(expected_output, dailyTemperatures(input))
}