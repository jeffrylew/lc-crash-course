#include <gtest/gtest.h>

#include <stack>
#include <string>

//! @brief First attempt solution to convert absolute path to canonical path
//! @param[in] path Absolute path on Unix-style machine
//! @return std::string containing canonical path
static std::string simplifyPathFA(std::string path)
{
    std::string canonical_path {};

    for (const auto c : path)
    {
        if (not canonical_path.empty())
        {
            const auto last_char = canonical_path.back();

            if (last_char == '/' && c == '/')
            {
                continue;
            }

            if (last_char == '.' && c == '/')
            {
                canonical_path.pop_back();
                continue;
            }

            if (last_char == '.' && c == '.')
            {
                canonical_path.pop_back();
                canonical_path.pop_back();
                
                while (not canonical_path.empty()
                       && canonical_path.back() != '/')
                {
                    canonical_path.pop_back();
                }

                continue;
            }
        }

        canonical_path.push_back(c);
    }

    if (canonical_path.size() > 1ULL
        && (canonical_path.back() == '/'
            || canonical_path.back() == '.'))
    {
        canonical_path.pop_back();
    }

    return canonical_path.empty() ? "/" : canonical_path;

} // static std::string simplifyPathFA( ...

TEST(SimplifyPathTest, SampleTest)
{
    EXPECT_EQ("/home", simplifyPathFA("/home/"));
    EXPECT_EQ("/c", simplifyPathFA("/a/./b/../../c/"));
    EXPECT_EQ("/", simplifyPathFA("/."));
    EXPECT_NE(".", simplifyPathFA("/..."));
}