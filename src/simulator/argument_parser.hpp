
#ifndef ARGUMENTPARSER_HPP
#define ARGUMENTPARSER_HPP

#include <boost/program_options.hpp>
#include <string>
#include <vector>

namespace po = boost::program_options;

class ArgumentParser {
private:
    po::variables_map options_;

public:
    ArgumentParser(int argc, char** argv);

    const std::vector<std::string> GetAlgorithmsNames();
    const std::string GetSubstring() const;
    const std::string GetText() const;
};

#endif  // ARGUMENTPARSER_HPP
