#include <string-searching/suffix_tree_substring_searcher.hpp>
#include <utility>

SuffixTreeSubstringSearcher::SuffixTreeSubstringSearcher() : BaseSubstringSearcher("suffix-tree") {}

bool SuffixTreeSubstringSearcher::Contains(const std::string& text,
                                           const std::string& substring) const {
    if (substring.empty()) return true;
    if (text.size() < substring.size()) return false;

    // Build the suffix tree for the full text and search for the substring.
    SuffixTrie tree(text);
    return tree.search(substring);
}

// A recursive function to insert a suffix of the txt in
// subtree rooted with this node
void SuffixTreeSubstringSearcher::SuffixTrieNode::insertSuffix(std::string suffix, int index) {
    // Store index in linked list
    indexes->push_back(index);

    // If string has more characters
    if (!suffix.empty()) {
        // Find the first character
        char cIndex = suffix.at(0);

        // If there is no edge for this character, add a new edge
        if (children[cIndex] == nullptr) children[cIndex] = new SuffixTrieNode();

        // Recur for next suffix
        children[cIndex]->insertSuffix(suffix.substr(1), index + 1);
    }
}

// A recursive function to search a pattern in subtree rooted with
// this node
bool SuffixTreeSubstringSearcher::SuffixTrieNode::search(std::string pat) {
    if (pat.empty()) {
        return indexes;
    }

    if (children[pat.at(0)] != nullptr) {
        return (children[pat.at(0)])->search(pat.substr(1));
    } else {
        return false;
    }
}
bool SuffixTreeSubstringSearcher::SuffixTrie::search(std::string pat) {
    return root.search(std::move(pat));
}
