#include <gtest/gtest.h>

#include <string-searching/aho_corasick_substring_searcher.hpp>
#include <string-searching/boyer_moore_substring_searcher.hpp>
#include <string-searching/brute_force_substring_searcher.hpp>
#include <string-searching/kmp_substring_searcher.hpp>
#include <string-searching/rabin_karp_substring_searcher.hpp>
#include <string-searching/shift_or_substring_searcher.hpp>
#include <string-searching/suffix_tree_substring_searcher.hpp>
#include <string-searching/z_substring_searcher.hpp>

// Typedef for the list of algorithm types to be tested
using Algorithms =
    ::testing::Types<BruteForceSubstringSearcher, KmpSubstringSearcher, RabinKarpSearcher,
                     ShiftOrSubstringSearcher, ZSubstringSearcher, AhoCorasickSearcher,
                     SuffixTreeSubstringSearcher, BoyerMooreSubstringSearcher>;

// Define a test suite template for all algorithm types
template <typename T>
class SubstringSearcherTest : public ::testing::Test {};

// Associate the test suite template with the list of algorithm types
TYPED_TEST_SUITE(SubstringSearcherTest, Algorithms);

// Test for an empty substring
TYPED_TEST(SubstringSearcherTest, ContainsEmptySubstring) {
    TypeParam searcher;
    EXPECT_TRUE(searcher.Contains("any text", ""));
}

// Test for an empty text
TYPED_TEST(SubstringSearcherTest, ContainsEmptyText) {
    TypeParam searcher;
    EXPECT_FALSE(searcher.Contains("", "substring"));
}

// Test for finding a substring
TYPED_TEST(SubstringSearcherTest, ContainsSubstringFound) {
    TypeParam searcher;
    EXPECT_TRUE(searcher.Contains("hello world", "world"));
}

// Test for not finding a substring
TYPED_TEST(SubstringSearcherTest, ContainsSubstringNotFound) {
    TypeParam searcher;
    EXPECT_FALSE(searcher.Contains("hello world", "planet"));
}

// Test for a substring that is equal to the text
TYPED_TEST(SubstringSearcherTest, ContainsSubstringEqualToText) {
    TypeParam searcher;
    EXPECT_TRUE(searcher.Contains("sample", "sample"));
}
