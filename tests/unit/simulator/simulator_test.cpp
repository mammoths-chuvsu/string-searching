#include "simulator/simulator.hpp"

#include <gtest/gtest.h>
#include <sstream>

#include "lib/naive_substring_searcher.hpp"

class MockAlgorithm : public BaseSubstringSearcher {
public:
    MockAlgorithm() : BaseSubstringSearcher("MockAlgorithm") {}

    bool Contains(const std::string& text, const std::string& substring) const override {
        return text.find(substring) != std::string::npos;
    }
};

TEST(SimulatorTest, Run) {
    AlgorithmList algorithms;
    algorithms.push_back(std::make_unique<MockAlgorithm>());
    Simulator simulator(std::move(algorithms));

    std::ostringstream output;
    simulator.Run("sample text", "sample", output);

    std::string result = output.str();
    
    EXPECT_TRUE(result.find("MockAlgorithm") != std::string::npos);
    
    EXPECT_TRUE(result.find("Duration:") != std::string::npos);

    EXPECT_TRUE(result.find("Status: Substring found") != std::string::npos);
}