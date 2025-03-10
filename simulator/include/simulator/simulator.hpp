#ifndef SIMULATOR_HPP_
#define SIMULATOR_HPP_

#include "utils.hpp"

/**
 * \brief Class for running and comparing string searching algorithms.
 */
class Simulator {
public:
    /**
     * \brief Constructor.
     * \param algorithms list of algorithms (BaseSubstringSearcher implementations).
     */
    Simulator(AlgorithmList algorithms);

    /**
     * \brief Run all algorithms and print result into output.
     * \param text text where to search substring.
     * \param substring string to search in text.
     *
     * Format of output:
     * ----------------------------
     * Timestamp: %Y-%m-%d %H:%M:%S
     * Algorithm: {algorithm name}
     * Duration: {time of execution} ms
     * Status: substring [not] found
     * ----------------------------
     */
    void Run(const std::string &text, const std::string &substring, std::ostream &output,
             int iterations = 1);

private:
    const AlgorithmList algorithms_;  ///< List of algorithms.
};

#endif
