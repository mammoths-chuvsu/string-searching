#ifndef STRING_SEARCHING_SUFFIX_TREE_SUBSTRING_SEARCHER_HPP
#define STRING_SEARCHING_SUFFIX_TREE_SUBSTRING_SEARCHER_HPP

#include <string>

#include "base_substring_searcher.hpp"

/**
 * \brief Implementation of suffix tree string searching algorithm.
 */
class SuffixTreeSubstringSearcher : public BaseSubstringSearcher {
public:
    SuffixTreeSubstringSearcher();

    bool Contains(const std::string& text, const std::string& substring) const override;
};

#endif  // STRING_SEARCHING_SUFFIX_TREE_SUBSTRING_SEARCHER_HPP