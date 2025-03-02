#ifndef STRING_SEARCHING_SUFFIX_TREE_SUBSTRING_SEARCHER_HPP
#define STRING_SEARCHING_SUFFIX_TREE_SUBSTRING_SEARCHER_HPP

#include <string>
#include <unordered_map>

#include "base_substring_searcher.hpp"


class SuffixTreeSubstringSearcher : public BaseSubstringSearcher {
public:
    SuffixTreeSubstringSearcher();
    bool Contains(const std::string& text, const std::string& substring) const override;

private:
    struct Edge;

    /**
     * \brief Node of the suffix tree.
     */
    struct Node {
        std::unordered_map<char, Edge*> children;
    };

    /**
     * \brief Edge of the suffix tree.
     *
     * Each edge is labeled by a substring of the text with indices [start, end)
     * and points to a child node.
     */
    struct Edge {
        int start;
        int end;
        Node* child;
        Edge(int s, int e, Node* child);
    };

    /**
     * \brief Suffix tree for a given text.
     *
     * The tree is built by inserting every suffix of the text. The search method
     * uses the tree to determine if a given substring exists.
     */
    class SuffixTree {
    public:
        /**
         * \brief Constructs the suffix tree from the provided text.
         */
        SuffixTree(const std::string &s);

        /**
         * \brief Destructor: frees all allocated nodes and edges.
         */
        ~SuffixTree();

        /**
         * \brief Searches for the pattern in the suffix tree.
         *
         * \param pattern The substring to search for.
         * \return True if pattern is found in the text.
         */
        bool search(const std::string &pattern) const;

    private:
        /**
         * \brief Recursively deletes nodes and associated edges.
         */
        void deleteSubtree(Node* node);

        /**
         * \brief Inserts the suffix of s starting at position pos into the tree.
         */
        void insertSuffix(int pos);

        /**
         * \brief Builds the suffix tree by inserting all suffixes.
         */
        void buildTree();

        Node* root;
        const std::string &s;
    };
};

#endif  // STRING_SEARCHING_SUFFIX_TREE_SUBSTRING_SEARCHER_HPP

