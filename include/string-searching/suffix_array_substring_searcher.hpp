#ifndef SUFFIX_ARRAY_SUBSTRING_SEARCHER_HPP_
#define SUFFIX_ARRAY_SUBSTRING_SEARCHER_HPP_

#include <string>
#include <vector>

#include "base_substring_searcher.hpp"

/**
 * \brief Implementation of the suffix array for substring search.
 */
class SuffixArraySubstringSearcher : public BaseSubstringSearcher {
public:
    SuffixArraySubstringSearcher();

    bool Contains(const std::string& text, const std::string& substring) const override;

private:
    /**
     * \brief Builds a suffix array using Karkkainen-Sanders algorithm.
     * \param text The input string.
     * \return The suffix array of the given text.
     */
    std::vector<int> BuildSuffixArray(const std::string& text) const;

    /**
     * \brief Searches for a substring using binary search with LCP optimization.
     * \param text The original text.
     * \param suffix_array The constructed suffix array.
     * \param lcp_array The computed LCP array.
     * \param substring The substring to search for.
     * \return True if the substring is found, false otherwise.
     */
    bool BinarySearchLCP(const std::string& text, const std::vector<int>& suffix_array,
                         const std::string& substring) const;
};

#endif  // SUFFIX_ARRAY_SUBSTRING_SEARCHER_HPP_
