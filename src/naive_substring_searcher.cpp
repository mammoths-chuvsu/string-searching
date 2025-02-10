#include <string-searching/naive_substring_searcher.hpp>

NaiveSubstringSearcher::NaiveSubstringSearcher() : BaseSubstringSearcher("Naive") {}

bool NaiveSubstringSearcher::Contains(const std::string& text, const std::string& substring) const {
    if (substring.empty()) return true;
    if (text.length() < substring.length()) return false;

    const size_t max_index = text.length() - substring.length();
    for (size_t i = 0; i <= max_index; ++i) {
        bool match = true;
        for (size_t j = 0; j < substring.length(); ++j) {
            if (text[i + j] != substring[j]) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;
}