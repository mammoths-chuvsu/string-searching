#include <string-searching/base_substring_searcher.hpp>
#include <string-searching/rabin_karp_substring_searcher.hpp>

RabinKarpSearcher::RabinKarpSearcher() : BaseSubstringSearcher("Rabin-Karp") {}

RabinKarpSearcher::RabinKarpSearcher(size_t alphabet_size, size_t prime)
    : BaseSubstringSearcher("Rabin-Karp"), alphabet_size_(alphabet_size), prime_(prime) {}

bool RabinKarpSearcher::Contains(const std::string& text, const std::string& substring) const {
    if (substring.empty()) return true;
    if (text.length() < substring.length()) return false;

    size_t pattern_length = substring.size();
    size_t pattern_hash = ComputeHash(substring, pattern_length);
    size_t text_hash = ComputeHash(text, pattern_length);

    size_t highest_power = 1;  // Highest power of alphabet size used for rolling hash
    for (size_t i = 0; i < pattern_length - 1; ++i) {
        highest_power = (highest_power * alphabet_size_) % prime_;
    }

    for (size_t i = 0; i <= text.size() - pattern_length; ++i) {
        // Match found if hashes are equal and content matches
        if (pattern_hash == text_hash && text.compare(i, pattern_length, substring) == 0) {
            return true;
        }

        // Roll the hash to the next window
        if (i < text.size() - pattern_length) {
            text_hash = RollHash(text_hash, text[i], text[i + pattern_length], highest_power);
        }
    }

    return false;
}

size_t RabinKarpSearcher::ComputeHash(const std::string& str, size_t length) const {
    size_t hash = 0;
    for (size_t i = 0; i < length; ++i) {
        hash = (hash * alphabet_size_ + str[i]) % prime_;
    }
    return hash;
}

size_t RabinKarpSearcher::RollHash(size_t old_hash, char old_char, char new_char,
                                   size_t highest_power) const {
    // Adjusted hash calculation for sliding the window in text
    size_t new_hash = (old_hash + prime_ - old_char * highest_power % prime_) % prime_;
    new_hash = (new_hash * alphabet_size_ + new_char) % prime_;
    return new_hash;
}
