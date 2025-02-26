#ifndef Z_SUBSTRING_SEARCHER_HPP_
#define Z_SUBSTRING_SEARCHER_HPP_

#include <string>
#include <vector>

#include "base_substring_searcher.hpp"

/**
 * \brief Implementation of the Z-algorithm for substring search.
 */
class ZSubstringSearcher : public BaseSubstringSearcher {
public:
    ZSubstringSearcher();
    bool Contains(const std::string& text, const std::string& substring) const override;

private:
    /**
     * \brief Computes the Z-array for the combined string (substring + separator + text).
     * \param combined The input string to process.
     * \return The Z-array where Z[i] is the length of the longest prefix match starting at index i.
     */
    std::vector<int> ComputeZArray(const std::string& combined) const;

    /**
     * \brief Checks if the Z-array contains an entry matching the substring length.
     * \param z The computed Z-array.
     * \param substring_length Length of the target substring.
     * \param combined_length Length of the combined string.
     * \return `true` if a valid match is found, `false` otherwise.
     */
    bool CheckZArrayForMatch(const std::vector<int>& z, int substring_length,
                             int combined_length) const;
};

#endif  // Z_SUBSTRING_SEARCHER_HPP_
