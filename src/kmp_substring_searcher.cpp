#include <string-searching/kmp_substring_searcher.hpp>

KmpSubstringSearcher::KmpSubstringSearcher() : BaseSubstringSearcher("KMP") {}

std::vector<int> KmpSubstringSearcher::ComputePrefixFunction(const std::string& str) const {
    std::vector<int> prefix(str.size(), 0);

    for (int i = 1; i < str.size(); ++i) {
        int k = prefix[i - 1];
        while (k > 0 && str[i] != str[k]) {
            k = prefix[k - 1];
        }
        if (str[i] == str[k]) {
            ++k;
        }
        prefix[i] = k;
    }

    return prefix;
}

bool KmpSubstringSearcher::Contains(const std::string& text, const std::string& substring) const {
    const std::string concatenated = substring + '\0' + text;
    const auto prefix = ComputePrefixFunction(concatenated);

    for (int index = 0; index < text.size(); ++index) {
        if (prefix[substring.size() + index + 1] == substring.size()) {
            return true;
        }
    }

    return false;
}
