#ifndef KMP_SUBSTRING_SEARCHER_HPP_
#define KMP_SUBSTRING_SEARCHER_HPP_

#include <string>
#include <vector>

#include "base_substring_searcher.hpp"

/**
 * \brief Implementation of Knuth-Morris-Pratt string searching algorithm.
 */
class KmpSubstringSearcher : public BaseSubstringSearcher {
public:
    KmpSubstringSearcher();
    bool Contains(const std::string& text, const std::string& substring) const override;

private:
    /**
     * \brief Computes prefix function array for the string.
     * \param str string to compute for.
     * \return Returns prefix function array.
     * 
     * p[i] is length of
     * the longest proper prefix of the substring str[0..i] which is
     * also a suffix of this substring.
     */
    std::vector<int> ComputePrefixFunction(const std::string& str) const;
};

#endif