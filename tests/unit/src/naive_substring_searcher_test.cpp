#include <gtest/gtest.h>

#include <string-searching/naive_substring_searcher.hpp>
#include <string>

TEST(NaiveSubstringSearcherTest, ContainsEmptySubstring) {
    NaiveSubstringSearcher searcher;
    EXPECT_TRUE(searcher.Contains("any text", ""));
}

TEST(NaiveSubstringSearcherTest, ContainsEmptyText) {
    NaiveSubstringSearcher searcher;
    EXPECT_FALSE(searcher.Contains("", "substring"));
}

TEST(NaiveSubstringSearcherTest, ContainsSubstringFound) {
    NaiveSubstringSearcher searcher;
    EXPECT_TRUE(searcher.Contains("hello world", "world"));
}

TEST(NaiveSubstringSearcherTest, ContainsSubstringNotFound) {
    NaiveSubstringSearcher searcher;
    EXPECT_FALSE(searcher.Contains("hello world", "planet"));
}

TEST(NaiveSubstringSearcherTest, ContainsSubstringEqualToText) {
    NaiveSubstringSearcher searcher;
    EXPECT_TRUE(searcher.Contains("sample", "sample"));
}
