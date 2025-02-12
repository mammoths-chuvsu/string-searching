#include <gtest/gtest.h>

#include <simulator/algorithms_creator.hpp>
#include <string-searching/brute_force_substring_searcher.hpp>

TEST(AlgorithmsCreatorTest, CreateValidAlgorithm) {
    AlgorithmsCreator creator;
    std::vector<std::string> names = {"brute-force"};

    AlgorithmList algorithms = creator.CreateAlgorithms(names);

    ASSERT_EQ(algorithms.size(), 1);
    EXPECT_EQ(algorithms[0]->GetName(), "brute-force");
}

TEST(AlgorithmsCreatorTest, UnknownAlgorithm) {
    AlgorithmsCreator creator;
    std::vector<std::string> names = {"unknown"};

    EXPECT_THROW(creator.CreateAlgorithms(names), std::invalid_argument);
}
