#ifndef ALGORITHMS_CREATOR_HPP_
#define ALGORITHMS_CREATOR_HPP_

#include <functional>
#include <string-searching/base_substring_searcher.hpp>
#include <unordered_map>

#include "utils.hpp"

class AlgorithmsCreator {
public:
    /**
     * \brief Creates list of algorithm implementations by list of algorithms' names.
     * \param algorithmsNames vector of algorithms' names.
     * \return Returns list of algorithms (BaseSubstringSearcher implementations).
     */
    static AlgorithmList CreateAlgorithms(const std::vector<std::string> &algorithmsNames);
};

#endif
