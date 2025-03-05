#include <algorithm>
#include <numeric>
#include <string-searching/suffix_array_substring_searcher.hpp>
#include <vector>

SuffixArraySubstringSearcher::SuffixArraySubstringSearcher()
    : BaseSubstringSearcher("suffix-array") {}

std::vector<int> SuffixArraySubstringSearcher::BuildSuffixArray(const std::string& text) const {
    int n = text.size();
    std::vector<int> suffix_array(n);
    std::iota(suffix_array.begin(), suffix_array.end(), 0);
    std::vector<int> rank(n);
    std::vector<int> temp(n);

    for (int i = 0; i < n; ++i) {
        rank[i] = text[i];  // Initializes the rank array with values from the text.
    }

    for (int len = 1; len < n; len *= 2) {
        auto cmp = [&](int i, int j) {
            if (rank[i] != rank[j]) return rank[i] < rank[j];
            int ri = (i + len < n) ? rank[i + len] : -1;
            int rj = (j + len < n) ? rank[j + len] : -1;
            return ri < rj;
        };
        std::sort(suffix_array.begin(), suffix_array.end(), cmp);

        temp[suffix_array[0]] = 0;
        for (int i = 1; i < n; ++i) {
            temp[suffix_array[i]] =
                temp[suffix_array[i - 1]] + cmp(suffix_array[i - 1], suffix_array[i]);
        }
        rank = temp;
    }

    return suffix_array;
}

bool SuffixArraySubstringSearcher::BinarySearchLCP(const std::string& text,
                                                   const std::vector<int>& suffix_array,
                                                   const std::string& substring) const {
    int left = 0, right = suffix_array.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        std::string suffix = text.substr(suffix_array[mid], substring.size());

        if (suffix == substring) {
            return true;
        }

        if (suffix < substring) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return false;
}

bool SuffixArraySubstringSearcher::Contains(const std::string& text,
                                            const std::string& substring) const {
    if (substring.empty()) return true;
    if (text.length() < substring.length()) return false;

    std::vector<int> suffix_array = BuildSuffixArray(text);
    return BinarySearchLCP(text, suffix_array, substring);
}
