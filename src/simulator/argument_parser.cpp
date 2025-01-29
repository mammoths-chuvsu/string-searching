
#include "argument_parser.hpp"

#include <iostream>

ArgumentParser::ArgumentParser(int argc, char** argv) {
    po::options_description description("Allowed options");
    description.add_options()("help", "produce help message")(
        "algorithms,a", po::value<std::vector<std::string>>(), "list of algorithms to use")(
        "substring,s", po::value<std::string>(), "substring to search for")(
        "text,t", po::value<std::string>(), "text to be searched");

    po::store(po::parse_command_line(argc, argv, description), options_);
    po::notify(options_);

    if (options_.count("help")) {
        std::cout << description << "\n";
        exit(0);
    }
}

const std::vector<std::string> ArgumentParser::GetAlgorithmsNames() {
    return options_.count("algorithms")
               ? options_["algorithms"].as<std::vector<std::string>>()
               : std::vector<std::string>();
}

const std::string ArgumentParser::GetSubstring() const {
    return options_.count("substring") ? options_["substring"].as<std::string>() : "";
}

const std::string ArgumentParser::GetText() const {
    return options_.count("text") ? options_["text"].as<std::string>() : "";
}
