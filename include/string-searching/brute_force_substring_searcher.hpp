#ifndef NAIVE_SUBSTRING_SEARCHER_HPP_
#define NAIVE_SUBSTRING_SEARCHER_HPP_

#include <string>

#include "base_substring_searcher.hpp"

/**
 * \brief Implementation of brute force string searching algorithm.
 */
class BruteForceSubstringSearcher : public BaseSubstringSearcher {
public:
    BruteForceSubstringSearcher();

    bool Contains(const std::string& text, const std::string& substring) const override;
};

#endif  // BRUTE_FORCE_SUBSTRING_SEARCHER_HPP_
