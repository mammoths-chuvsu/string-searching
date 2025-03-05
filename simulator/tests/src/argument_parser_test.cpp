#include <gtest/gtest.h>

#include <simulator/argument_parser.hpp>

TEST(ArgumentParserTest, HelpOption) {
    const char* argv[] = {"program", "--help"};
    int argc = 2;

    testing::internal::CaptureStdout();
    EXPECT_EXIT({ ArgumentParser parser(argc, const_cast<char**>(argv)); },
                testing::ExitedWithCode(0), ".*");
}

TEST(ArgumentParserTest, GetAlgorithmsNames) {
    const char* argv[] = {"program", "--algorithms", "brute-force"};
    int argc = 3;
    ArgumentParser parser(argc, const_cast<char**>(argv));

    auto algorithms = parser.GetAlgorithmsNames();
    ASSERT_EQ(algorithms.size(), 1);
    EXPECT_EQ(algorithms[0], "brute-force");
}

TEST(ArgumentParserTest, GetSubstring) {
    const char* argv[] = {"program", "--substring", "test"};
    int argc = 3;
    ArgumentParser parser(argc, const_cast<char**>(argv));

    auto substring = parser.GetSubstring();
    EXPECT_EQ(substring, "test");
}

TEST(ArgumentParserTest, GetText) {
    const char* argv[] = {"program", "--text", "This is a sample text"};
    int argc = 3;
    ArgumentParser parser(argc, const_cast<char**>(argv));

    auto text = parser.GetText();
    EXPECT_EQ(text, "This is a sample text");
}