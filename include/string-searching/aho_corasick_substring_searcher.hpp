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
    /**
     * \brief Node of trie
     */
    struct Node {
        std::unordered_map<char, Node*> children;
        Node* fail = nullptr;         // Failure link
        bool isEndOfPattern = false;  // Flag to mark the end of the pattern
    };

    /**
     * \brief Help structure for Aho-Corasick algorithm
     */
    struct AhoCorasick {
        Node* root;  ///< root node of trie

        AhoCorasick();

        /**
         * \brief Add pattern to trie
         */
        void AddPattern(const std::string& pattern);

        /**
         * \brief Build the failure links (after constructing trie)
         */
        void Build();

        /**
         * \brief Search for pattern in text
         */
        bool Search(const std::string& text);
    };
};

#endif  // AHO_CORASICK_SUBSTRING_SEARCHER_HPP_
