#include <string-searching/suffix_tree_substring_searcher.hpp>

SuffixTreeSubstringSearcher::SuffixTreeSubstringSearcher() : BaseSubstringSearcher("suffix-tree") {}

bool SuffixTreeSubstringSearcher::Contains(const std::string& text,
                                           const std::string& substring) const {
    if (substring.empty()) return true;
    if (text.size() < substring.size()) return false;

    // Build the suffix tree for the full text and search for the substring.
    SuffixTree tree(text);
    return tree.search(substring);
}

SuffixTreeSubstringSearcher::Edge::Edge(int s, int e, Node* child)
    : start(s), end(e), child(child) {}

SuffixTreeSubstringSearcher::SuffixTree::SuffixTree(const std::string& s) : s(s) {
    root = new Node();
    buildTree();
}

SuffixTreeSubstringSearcher::SuffixTree::~SuffixTree() { deleteSubtree(root); }

void SuffixTreeSubstringSearcher::SuffixTree::deleteSubtree(Node* node) {
    if (!node) return;
    for (auto& entry : node->children) {
        SuffixTreeSubstringSearcher::Edge* edge = entry.second;
        deleteSubtree(edge->child);
        delete edge;
    }
    delete node;
}

void SuffixTreeSubstringSearcher::SuffixTree::insertSuffix(int pos) {
    Node* current = root;
    int i = pos;
    while (i < s.size()) {
        char currentChar = s[i];
        // If no edge starts with the current character, create a new leaf edge.
        if (current->children.find(currentChar) == current->children.end()) {
            Node* leaf = new Node();
            current->children[currentChar] = new Edge(i, s.size(), leaf);
            return;
        }
        Edge* edge = current->children[currentChar];
        int edgeStart = edge->start;
        int edgeEnd = edge->end;
        int j = edgeStart;
        // Walk along the edge while characters match.
        while (j < edgeEnd && i < s.size() && s[j] == s[i]) {
            ++j;
            ++i;
        }
        if (j == edgeEnd) {
            // Entire edge matched; move to the child node.
            current = edge->child;
            continue;
        }
        // Mismatch found: split the edge.
        Node* splitNode = new Node();
        // Create a new edge for the remainder of the old edge.
        splitNode->children[s[j]] = new Edge(j, edgeEnd, edge->child);
        // Create a new edge for the remaining part of the suffix.
        Node* newLeaf = new Node();
        splitNode->children[s[i]] = new Edge(i, s.size(), newLeaf);
        // Adjust the current edge to point to the split node.
        edge->end = j;
        edge->child = splitNode;
        return;
    }
}

void SuffixTreeSubstringSearcher::SuffixTree::buildTree() {
    for (int i = 0; i < s.size(); ++i) {
        insertSuffix(i);
    }
}

bool SuffixTreeSubstringSearcher::SuffixTree::search(const std::string& pattern) const {
    Node* current = root;
    int i = 0;
    while (i < pattern.size()) {
        char ch = pattern[i];
        if (current->children.find(ch) == current->children.end()) return false;
        Edge* edge = current->children.at(ch);
        int edgeLen = edge->end - edge->start;
        int k = 0;
        while (k < edgeLen && i < pattern.size()) {
            if (s[edge->start + k] != pattern[i]) return false;
            ++k;
            ++i;
        }
        current = edge->child;
    }
    return true;
}
