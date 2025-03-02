#include <gtest/gtest.h>

#include <simulator/algorithms_creator.hpp>
#include <simulator/argument_parser.hpp>
#include <simulator/simulator.hpp>
#include <sstream>

class SimulatorBenchmarkTest : public ::testing::Test {
protected:
    void SetUp() override {
        algorithms_ =
            AlgorithmsCreator::CreateAlgorithms({"brute-force", "KMP", "Rabin-Karp", "Z-algorithm",
                                                 "Aho-Corasick", "suffix-tree", "boyer-moore"});
        algorithms_move_ =
            AlgorithmsCreator::CreateAlgorithms({"brute-force", "KMP", "Rabin-Karp", "Z-algorithm",
                                                 "Aho-Corasick", "suffix-tree", "boyer-moore"});
    }

    void VerifyOutput(const std::string& output, const std::string& algorithm_name,
                      bool expected_found) {
        std::istringstream iss(output);
        std::string line;
        while (std::getline(iss, line)) {
            if (line.find("Algorithm: " + algorithm_name) != std::string::npos) {
                std::getline(iss, line);  // Read Duration line
                std::getline(iss, line);  // Read Status line
                std::string expected_status =
                    "Status: Substring" + std::string(expected_found ? " " : " not ") + "found";
                ASSERT_EQ(line, expected_status);
                return;
            }
        }
        FAIL() << "No output for algorithm: " << algorithm_name;
    }

    ArgumentParser parser_{0, nullptr};  // Stub for ReadFileContent usage
    AlgorithmList algorithms_, algorithms_move_;
};

TEST_F(SimulatorBenchmarkTest, Text500k_Substring63_NotFound) {
    algorithms_ = AlgorithmsCreator::CreateAlgorithms({});
    algorithms_move_ = AlgorithmsCreator::CreateAlgorithms({});
    std::string text = parser_.ReadFileContent(
        "../../../simulator/tests/resources/test-text-500k-substring-63-not-found/text.txt");
    std::string substring = parser_.ReadFileContent(
        "../../../simulator/tests/resources/test-text-500k-substring-63-not-found/substring.txt");

    Simulator simulator(std::move(algorithms_move_));

    std::ostringstream output;
    simulator.Run(text, substring, output);

    for (auto& algorithm : algorithms_) {
        VerifyOutput(output.str(), algorithm->GetName(), false);
    }
}

TEST_F(SimulatorBenchmarkTest, Text500k_Substring63_Found) {
    algorithms_ = AlgorithmsCreator::CreateAlgorithms({});
    algorithms_move_ = AlgorithmsCreator::CreateAlgorithms({});
    std::string text = parser_.ReadFileContent(
        "../../../simulator/tests/resources/test-text-500k-substring-63-found/text.txt");
    std::string substring = parser_.ReadFileContent(
        "../../../simulator/tests/resources/test-text-500k-substring-63-found/substring.txt");

    Simulator simulator(std::move(algorithms_move_));

    std::ostringstream output;
    simulator.Run(text, substring, output);

    for (auto& algorithm : algorithms_) {
        VerifyOutput(output.str(), algorithm->GetName(), true);
    }
}

TEST_F(SimulatorBenchmarkTest, Text500k_Substring1k_NotFound) {
    std::string text = parser_.ReadFileContent(
        "../../../simulator/tests/resources/test-text-500k-substring-1k-not-found/text.txt");
    std::string substring = parser_.ReadFileContent(
        "../../../simulator/tests/resources/test-text-500k-substring-1k-not-found/substring.txt");

    Simulator simulator(std::move(algorithms_move_));

    std::ostringstream output;
    simulator.Run(text, substring, output);

    for (auto& algorithm : algorithms_) {
        VerifyOutput(output.str(), algorithm->GetName(), false);
    }
}

TEST_F(SimulatorBenchmarkTest, Text500k_Substring1k_Found) {
    std::string text = parser_.ReadFileContent(
        "../../../simulator/tests/resources/test-text-500k-substring-1k-found/text.txt");
    std::string substring = parser_.ReadFileContent(
        "../../../simulator/tests/resources/test-text-500k-substring-1k-found/substring.txt");

    Simulator simulator(std::move(algorithms_move_));

    std::ostringstream output;
    simulator.Run(text, substring, output);

    for (auto& algorithm : algorithms_) {
        VerifyOutput(output.str(), algorithm->GetName(), true);
    }
}

TEST_F(SimulatorBenchmarkTest, Text1M_Substring10k_NotFound) {
    std::string text = parser_.ReadFileContent(
        "../../../simulator/tests/resources/test-text-1m-substring-10k-not-found/text.txt");
    std::string substring = parser_.ReadFileContent(
        "../../../simulator/tests/resources/test-text-1m-substring-10k-not-found/substring.txt");

    Simulator simulator(std::move(algorithms_move_));

    std::ostringstream output;
    simulator.Run(text, substring, output);

    for (auto& algorithm : algorithms_) {
        VerifyOutput(output.str(), algorithm->GetName(), false);
    }
}

TEST_F(SimulatorBenchmarkTest, Text1M_Substring10k_Found) {
    std::string text = parser_.ReadFileContent(
        "../../../simulator/tests/resources/test-text-1m-substring-10k-found/text.txt");
    std::string substring = parser_.ReadFileContent(
        "../../../simulator/tests/resources/test-text-1m-substring-10k-found/substring.txt");

    Simulator simulator(std::move(algorithms_move_));

    std::ostringstream output;
    simulator.Run(text, substring, output);

    for (auto& algorithm : algorithms_) {
        VerifyOutput(output.str(), algorithm->GetName(), true);
    }
}

TEST_F(SimulatorBenchmarkTest, Text1M_Substring10k_NotFound_AntiBruteForce) {
    std::string text = parser_.ReadFileContent(
        "../../../simulator/tests/resources/test-text-1m-substring-10k-not-found-anti-bf/text.txt");
    std::string substring = parser_.ReadFileContent(
        "../../../simulator/tests/resources/test-text-1m-substring-10k-not-found-anti-bf/"
        "substring.txt");

    Simulator simulator(std::move(algorithms_move_));

    std::ostringstream output;
    simulator.Run(text, substring, output);

    for (auto& algorithm : algorithms_) {
        VerifyOutput(output.str(), algorithm->GetName(), false);
    }
}