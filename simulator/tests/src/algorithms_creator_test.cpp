#include <gtest/gtest.h>

#include <simulator/algorithms_creator.hpp>
#include <string-searching/naive_substring_searcher.hpp>

TEST(AlgorithmsCreatorTest, CreateValidAlgorithm) {
    AlgorithmsCreator creator;
    std::vector<std::string> names = {"Naive"};

    AlgorithmList algorithms = creator.CreateAlgorithms(names);

    ASSERT_EQ(algorithms.size(), 1);
    EXPECT_EQ(algorithms[0]->GetName(), "Naive");
}

TEST(AlgorithmsCreatorTest, UnknownAlgorithm) {
    AlgorithmsCreator creator;
    std::vector<std::string> names = {"unknown"};

    EXPECT_THROW(creator.CreateAlgorithms(names), std::invalid_argument);
}
