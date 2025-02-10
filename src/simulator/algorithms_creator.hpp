#ifndef ALGORITHMS_CREATOR_HPP_
#define ALGORITHMS_CREATOR_HPP_

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
