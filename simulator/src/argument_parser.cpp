#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>
#include <simulator/argument_parser.hpp>
#include <sstream>
#include <stdexcept>

namespace po = boost::program_options;

std::string ArgumentParser::ReadFileContent(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + file_path);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

ArgumentParser::ArgumentParser(int argc, char** argv) {
    po::options_description description("Allowed options");
    description.add_options()("help", "produce help message")(
        "algorithms,a", po::value<std::vector<std::string>>(), "list of algorithms to use")(
        "substring,s", po::value<std::string>(), "substring to search for")(
        "substring-file,S", po::value<std::string>(), "file with substring to search for")(
        "text,t", po::value<std::string>(), "text to be searched")(
        "text-file,T", po::value<std::string>(), "file with text to be searched");

    po::store(po::parse_command_line(argc, argv, description), options_);
    po::notify(options_);

    if (options_.count("help")) {
        std::cout << description << "\n";
        exit(0);
    }

    if (options_.count("substring") && options_.count("substring-file")) {
        throw std::runtime_error(
            "Options --substring and --substring-file are mutually exclusive.");
    }
    if (options_.count("text") && options_.count("text-file")) {
        throw std::runtime_error("Options --text and --text-file are mutually exclusive.");
    }

    if (options_.count("substring-file")) {
        substring_ = ReadFileContent(options_["substring-file"].as<std::string>());
    } else if (options_.count("substring")) {
        substring_ = options_["substring"].as<std::string>();
    }

    if (options_.count("text-file")) {
        text_ = ReadFileContent(options_["text-file"].as<std::string>());
    } else if (options_.count("text")) {
        text_ = options_["text"].as<std::string>();
    }
}

const std::vector<std::string> ArgumentParser::GetAlgorithmsNames() {
    return options_.count("algorithms") ? options_["algorithms"].as<std::vector<std::string>>()
                                        : std::vector<std::string>();
}

const std::string ArgumentParser::GetSubstring() const {
    return options_.count("substring") ? options_["substring"].as<std::string>() : "";
}

const std::string ArgumentParser::GetText() const {
    return options_.count("text") ? options_["text"].as<std::string>() : "";
}
