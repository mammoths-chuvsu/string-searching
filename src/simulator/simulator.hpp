#ifndef SIMULATOR_HPP_
#define SIMULATOR_HPP_

#include "utils.hpp"

class Simulator {
public:
    Simulator(AlgorithmList algorithms);

    void Run(const std::string &text, const std::string &substring, std::ostream &output);

private:
    const AlgorithmList algorithms_;
};

#endif
