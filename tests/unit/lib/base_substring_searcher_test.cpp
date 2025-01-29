#include <gtest/gtest.h>

#include <optional>
#include <src/lib/base_substring_searcher.hpp>
#include <string>

TEST(BaseSubstringSearcherTest, GetAlgorithmByNameNaive) {
    auto algorithm = BaseSubstringSearcher::GetAlgorithmByName("Naive");
    EXPECT_TRUE(algorithm.has_value());
    EXPECT_EQ(algorithm.value(), SubstringSearchAlgorithm::kNaive);
}

TEST(BaseSubstringSearcherTest, GetAlgorithmByNameNonExistent) {
    auto algorithm = BaseSubstringSearcher::GetAlgorithmByName("NonExistent");
    EXPECT_FALSE(algorithm.has_value());
}