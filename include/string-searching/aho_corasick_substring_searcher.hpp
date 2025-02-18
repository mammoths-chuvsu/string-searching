#ifndef AHO_CORASICK_SUBSTRING_SEARCHER_HPP_
#define AHO_CORASICK_SUBSTRING_SEARCHER_HPP_

#include <string>
#include <unordered_map>

#include "base_substring_searcher.hpp"

/**
 * \brief Implementation of the Aho-Corasick algorithm for substring search.
 */
class AhoCorasickSearcher : public BaseSubstringSearcher {
public:
    AhoCorasickSearcher();
    bool Contains(const std::string& text, const std::string& substring) const override;

private:
    struct Node {
        std::unordered_map<char, Node*> children;
        Node* fail = nullptr;         // Failure link
        bool isEndOfPattern = false;  // Flag to mark the end of the pattern
    };

    struct AhoCorasick {
        Node* root;

        AhoCorasick();
        void AddPattern(const std::string& pattern);
        void Build();
        bool Search(const std::string& text);
    };
};

#endif  // AHO_CORASICK_SUBSTRING_SEARCHER_HPP_
