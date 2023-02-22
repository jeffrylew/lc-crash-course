#include <gtest/gtest.h>

#include <numeric>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

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

//! @brief Solution from HR discussion section to convert to canonical path
//! @param[in] path Absolute path on Unix-style machine
//! @return std::string containing canonical path
static std::string simplifyPathDS(std::string path)
{
    //! @details https://leetcode.com/problems/simplify-path/solutions/511289/
    //!          official-solution/
    //!
    //!          Time complexity O(N) where N = characters in original path.
    //!          Spend O(N) to split input path into components then process
    //!          each one by one, another O(N) operation.
    //!          Space complexity (N) for array containing split components
    //!          and stack

    std::istringstream      iss {path};
    std::stack<std::string> path_components {};

    std::string directory {};
    while (std::getline(iss, directory, '/'))
    {
        //! A no-op for a "." or an empty string
        if (directory == "." || directory.empty())
        {
            continue;
        }
        else if (directory == "..")
        {
            //! If current component is a ".." the pop an entry
            //! from the stack if it's not empty
            if (not path_components.empty())
            {
                path_components.pop();
            }
        }
        else
        {
            path_components.emplace(std::move(directory));
        }
    }

    //! Stitch together directory names, reusing directory variable
    directory.clear();
    int path_vec_idx {static_cast<int>(path_components.size()) - 1};

    std::vector<std::string> path_vec(path_components.size());
    while (not path_components.empty())
    {
        path_vec[path_vec_idx--] = path_components.top();
        path_components.pop();
    }
    directory = std::accumulate(path_vec.begin(),
                                path_vec.end(),
                                std::string {},
                                [](std::string lhs, std::string rhs) {
                                    return std::move(lhs)
                                           + "/"
                                           + std::move(rhs);
                                });

    return directory.empty() ? "/" : directory;

} // static std::string simplifyPathDS( ...

TEST(SimplifyPathTest, SampleTest)
{
    EXPECT_EQ("/home", simplifyPathFA("/home/"));
    EXPECT_EQ("/c", simplifyPathFA("/a/./b/../../c/"));
    EXPECT_EQ("/", simplifyPathFA("/."));
    EXPECT_NE(".", simplifyPathFA("/..."));

    EXPECT_EQ("/home", simplifyPathDS("/home/"));
    EXPECT_EQ("/c", simplifyPathDS("/a/./b/../../c/"));
    EXPECT_EQ("/", simplifyPathDS("/."));
    EXPECT_EQ(".", simplifyPathDS("/..."));
}