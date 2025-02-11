#include <algorithm>
#include <string-searching/z_substring_searcher.hpp>
#include <string>
#include <vector>

ZSubstringSearcher::ZSubstringSearcher() : BaseSubstringSearcher("ZAlgorithm") {}

std::vector<int> ZSubstringSearcher::ComputeZArray(const std::string& combined) const {
    const int n = static_cast<int>(combined.length());
    std::vector<int> z(n, 0);
    int left = 0, right = 0;

    for (int i = 1; i < n; ++i) {
        if (i <= right) {
            z[i] = std::min(right - i + 1, z[i - left]);
        }

        while (i + z[i] < n && combined[z[i]] == combined[i + z[i]]) {
            ++z[i];
        }

        if (i + z[i] - 1 > right) {
            left = i;
            right = i + z[i] - 1;
        }
    }
    return z;
}

bool ZSubstringSearcher::CheckZArrayForMatch(const std::vector<int>& z, int substring_length,
                                             int combined_length) const {
    // Start checking after the separator (position = substring_length)
    for (int i = substring_length + 1; i < combined_length; ++i) {
        if (z[i] == substring_length) {
            return true;
        }
    }
    return false;
}

bool ZSubstringSearcher::Contains(const std::string& text, const std::string& substring) const {
    if (substring.empty()) return true;
    if (text.length() < substring.length()) return false;

    // Combine substring, separator '\0', and text
    const std::string combined = substring + '\0' + text;
    const int substring_length = static_cast<int>(substring.length());
    const int combined_length = static_cast<int>(combined.length());

    // Compute Z-array and check for matches
    const std::vector<int> z = ComputeZArray(combined);
    return CheckZArrayForMatch(z, substring_length, combined_length);
}