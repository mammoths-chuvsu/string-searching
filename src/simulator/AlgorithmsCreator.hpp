#ifndef ALGORITHMS_CREATOR_HPP_
#define ALGORITHMS_CREATOR_HPP_

#include <memory>
#include <vector>

#include "lib/BaseSubstringSearcher.hpp"

using AlgorithmList = std::vector<std::unique_ptr<BaseSubstringSearcher>>;

class AlgorithmsCreator {
    AlgorithmList CreateAlgorithms(const std::vector<std::string> &algorithmsNames);
};

#endif
