#ifndef NAIVE_SUBSTRING_SEARCHER_HPP_
#define NAIVE_SUBSTRING_SEARCHER_HPP_

#include <string>

#include "base_substring_searcher.hpp"

/**
 * \brief Implementation of naive string searching algorithm.
 */
class NaiveSubstringSearcher : public BaseSubstringSearcher {
public:
    NaiveSubstringSearcher();
    bool Contains(const std::string& text, const std::string& substring) const override;
};

#endif