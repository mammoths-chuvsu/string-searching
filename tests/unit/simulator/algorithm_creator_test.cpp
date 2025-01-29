#include <gtest/gtest.h>

#include "src/simulator/AlgorithmsCreator.hpp"

TEST(AlgorithmsCreatorTest, CreateNaiveAlgorithm) {
    AlgorithmsCreator creator;
    auto algorithms = creator.CreateAlgorithms({"Naive"});
    ASSERT_EQ(algorithms.size(), 1);
    EXPECT_EQ(algorithms[0]->getName(), "Naive");
}

TEST(AlgorithmsCreatorTest, CreateNonExistentAlgorithm) {
    AlgorithmsCreator creator;
    auto algorithms = creator.CreateAlgorithms({"NonExistent"});
    EXPECT_EQ(algorithms.size(), 0);
}

TEST(AlgorithmsCreatorTest, CreateMultipleAlgorithms) {
    AlgorithmsCreator creator;
    auto algorithms = creator.CreateAlgorithms({"Naive", "NonExistent"});
    ASSERT_EQ(algorithms.size(), 1); 
    EXPECT_EQ(algorithms[0]->getName(), "Naive");
}