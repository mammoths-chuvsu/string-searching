#ifndef ARGUMENTPARSER_HPP
#define ARGUMENTPARSER_HPP

#include <boost/program_options.hpp>
#include <string>
#include <vector>

namespace po = boost::program_options;

/**
 * \brief Command options arguments parser.
 */
class ArgumentParser {
private:
    po::variables_map options_;  ///< Parsed arguments storage.
    std::string substring_;
    std::string text_;

public:
    std::string ReadFileContent(const std::string& file_path);

    /**
     * \brief Construct object, containing parsed arguments.
     *
     * \param argc number of arguments.
     * \param argv pointer to array of arguments.
     */
    ArgumentParser(int argc, char** argv);

    /**
     * \brief Get parsed names of algorithms.
     */
    const std::vector<std::string> GetAlgorithmsNames();

    /**
     * \brief Get parsed substring to search in text.
     */
    const std::string GetSubstring() const;

    /**
     * \brief Get parsed text.
     */
    const std::string GetText() const;
};

#endif  // ARGUMENTPARSER_HPP
