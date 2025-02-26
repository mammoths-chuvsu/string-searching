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
     * @brief Constructs a Rabin-Karp searcher using the specified alphabet size and prime number.
     *
     * @param alphabet_size Number of characters in the alphabet (default 256).
     * @param prime Prime number for hash calculations (default 1e9 + 7).
     */
    RabinKarpSearcher(size_t alphabet_size = 256, size_t prime = 1e9 + 7);

    bool Contains(const std::string& text, const std::string& substring) const override;

private:
    size_t ComputeHash(const std::string& str, size_t length) const;

    size_t RollHash(size_t old_hash, char old_char, char new_char, size_t highest_power) const;

    size_t alphabet_size_;
    size_t prime_;
};

#endif  // RABIN_KARP_SEARCHER_HPP_
