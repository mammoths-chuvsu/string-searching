#include <algorithm>
#include <string-searching/boyer_moore_substring_searcher.hpp>

BoyerMooreSubstringSearcher::BoyerMooreSubstringSearcher() : BaseSubstringSearcher("boyer-moore") {}

std::vector<int> BoyerMooreSubstringSearcher::computeBadCharTable(const std::string& substring) {
    const int ALPHABET_SIZE = 256;
    std::vector<int> badChar(ALPHABET_SIZE, -1);
    for (int i = 0; i < substring.size(); i++) {
        badChar[static_cast<unsigned char>(substring[i])] = i;
    }
    return badChar;
}

std::vector<int> BoyerMooreSubstringSearcher::computeGoodSuffixTable(const std::string& substring) {
    int m = substring.size();
    std::vector<int> shift(m + 1, 0);
    std::vector<int> bpos(m + 1, 0);  // bpos[i] — position of the boundary for the suffix at i.

    // Initialize the last element.
    bpos[m] = m + 1;
    int i = m, j = m + 1;

    // Preprocessing for the strong good suffix heuristic.
    while (i > 0) {
        // Find the previous boundary while characters do not match.
        while (j <= m && substring[i - 1] != substring[j - 1]) {
            if (shift[j] == 0) shift[j] = j - i;
            j = bpos[j];
        }
        i--;
        j--;
        bpos[i] = j;
    }

    // Fill shifts for positions where the strong suffix rule does not apply.
    j = bpos[0];
    for (i = 0; i <= m; i++) {
        if (shift[i] == 0) shift[i] = j;
        if (i == j) j = bpos[j];
    }
    return shift;
}

bool BoyerMooreSubstringSearcher::Contains(const std::string& text,
                                           const std::string& substring) const {
    int n = text.size();
    int m = substring.size();
    if (m == 0) return true;

    // Preprocessing: compute the bad character and good suffix tables.
    std::vector<int> badChar = computeBadCharTable(substring);
    std::vector<int> goodSuffix = computeGoodSuffixTable(substring);

    int s = 0;  // s – shift of the pattern relatively to the text.
    while (s <= n - m) {
        int j = m - 1;

        // Compare the pattern and text from right to left.
        while (j >= 0 && substring[j] == text[s + j]) j--;

        if (j < 0) {
            // Found!
            return true;
        } else {
            // Calculate shifts using both heuristics.
            int badCharShift = j - badChar[static_cast<unsigned char>(text[s + j])];
            int goodSuffixShift = goodSuffix[j + 1];

            // Choose the maximum shift to avoid missing potential matches.
            s += std::max(1, std::max(badCharShift, goodSuffixShift));
        }
    }
    return false;
}