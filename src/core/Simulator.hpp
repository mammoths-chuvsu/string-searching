#ifndef SIMULATOR_HPP_
#define SUMULATOR_HPP_

#include <memory>
#include <vector>

#include "../../lib/BaseSubstringSearcher.hpp"

class Simulator {
public:
    Simulator(std::vector<std::unique_ptr<BaseSubstringSearcher>> algorithms);

    void Run(const std::string &text, const std::string &substring, std::ostream &output);

private:
    std::vector<std::unique_ptr<BaseSubstringSearcher>> algorithms_;
};

#endif
