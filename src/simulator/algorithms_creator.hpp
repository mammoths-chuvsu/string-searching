#ifndef ALGORITHMS_CREATOR_HPP_
#define ALGORITHMS_CREATOR_HPP_

#include <vector>

#include "utils.hpp"

class AlgorithmsCreator {
public:
    static AlgorithmList CreateAlgorithms(const std::vector<const std::string> &algorithmsNames);
};

#endif
