#ifndef BOYER_MOORE_SUBSTRING_SEARCHER_HPP_
#define BOYER_MOORE_SUBSTRING_SEARCHER_HPP_

#include <vector>

#include "base_substring_searcher.hpp"

/**
 * \brief Implementation of the Boyer-Moore algorithm for substring search.
 */
class BoyerMooreSubstringSearcher : public BaseSubstringSearcher {
public:
    BoyerMooreSubstringSearcher();

    bool Contains(const std::string& text, const std::string& substring) const override;

private:
    /**
     * \brief Computes the bad character table for the Boyer-Moore algorithm.
     *
     * This table helps determine how far to shift the pattern when a mismatch occurs,
     * based on the last occurrence of a character in the pattern.
     *
     * \param substring The pattern to search for.
     * \return A vector where each index represents a character, and the value is its last position
     * in the pattern.
     */
    static std::vector<int> computeBadCharTable(const std::string& pattern);

    /**
     * \brief Computes the good suffix table for the Boyer-Moore algorithm.
     *
     * This table determines how far to shift the pattern when a mismatch occurs,
     * based on suffix matches within the pattern.
     *
     * \param substring The pattern to search for.
     * \return A vector where each index represents a position in the pattern, and the value is the
     * shift amount.
     */
    static std::vector<int> computeGoodSuffixTable(const std::string& pattern);
};

#endif  // BOYER_MOORE_SUBSTRING_SEARCHER_HPP_
