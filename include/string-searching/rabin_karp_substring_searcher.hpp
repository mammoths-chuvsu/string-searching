#ifndef RABIN_KARP_SEARCHER_HPP_
#define RABIN_KARP_SEARCHER_HPP_

#include <string>

#include "base_substring_searcher.hpp"

/**
 * @brief Implementation of the Rabin-Karp string searching algorithm.
 */
class RabinKarpSearcher : public BaseSubstringSearcher {
public:
    /**
     * @brief Constructs a Rabin-Karp searcher with default params.
     */
    RabinKarpSearcher();

    /**
     * @brief Constructs a Rabin-Karp searcher with given alphabet size and prime number.
     */
    RabinKarpSearcher(size_t alphabet_size, size_t prime);

    /**
     * @brief Checks if the substring is contained in the text.
     * @param text The text to search within.
     * @param substring The pattern to search for.
     * @return True if the pattern is found, otherwise false.
     */
    bool Contains(const std::string& text, const std::string& substring) const override;

private:
    size_t ComputeHash(const std::string& str, size_t length) const;
    size_t RollHash(size_t old_hash, char old_char, char new_char, size_t highest_power) const;

    size_t alphabet_size_ = 256;
    size_t prime_ = 1e9 + 7;
};

#endif  // RABIN_KARP_SEARCHER_HPP_