#ifndef STRING_SEARCHING_SUFFIX_TREE_SUBSTRING_SEARCHER_HPP
#define STRING_SEARCHING_SUFFIX_TREE_SUBSTRING_SEARCHER_HPP

#include <list>
#include <string>
#include <unordered_map>

#include "base_substring_searcher.hpp"

#define MAX_CHAR 256

/**
 * \brief Implementation of the Suffix Tree algorithm for substring search.
 */
class SuffixTreeSubstringSearcher : public BaseSubstringSearcher {
public:
    SuffixTreeSubstringSearcher();
    bool Contains(const std::string& text, const std::string& substring) const override;

private:
    class SuffixTrieNode {
    private:
        SuffixTrieNode* children[MAX_CHAR]{};
        std::list<int>* indexes;

    public:
        SuffixTrieNode()
        {
            // Create an empty linked list for indexes of
            // suffixes starting from this node
            indexes = new std::list<int>;

            // Initialize all child pointers as NULL
            for (auto &i : children) i = nullptr;
        }

        // A recursive function to insert a suffix of the txt
        // in subtree rooted with this node
        void insertSuffix(std::string suffix, int index);

        // A function to search a pattern in subtree rooted
        // with this node.The function returns pointer to a linked
        // list containing all indexes where pattern is present.
        // The returned indexes are indexes of last characters
        // of matched text.
        bool search(std::string pat);
    };

    class SuffixTrie {
    private:
        SuffixTrieNode root;

    public:
        // Constructor (Builds a trie of suffixes of the given text)
        SuffixTrie(const std::string& txt) {
            // Consider all suffixes of given string and insert
            // them into the Suffix Trie using recursive function
            // insertSuffix() in SuffixTrieNode class
            for (int i = 0; i < txt.length(); i++) root.insertSuffix(txt.substr(i), i);
        }

        // Function to searches a pattern in this suffix trie.
        bool search(std::string pat);
    };
};

#endif  // STRING_SEARCHING_SUFFIX_TREE_SUBSTRING_SEARCHER_HPP
