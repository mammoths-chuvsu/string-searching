#include <queue>
#include <string-searching/aho_corasick_substring_searcher.hpp>

AhoCorasickSearcher::AhoCorasickSearcher() : BaseSubstringSearcher("Aho-Corasick") {}

bool AhoCorasickSearcher::Contains(const std::string& text, const std::string& substring) const {
    AhoCorasick ahoCorasick;
    ahoCorasick.AddPattern(substring);
    ahoCorasick.Build();
    return ahoCorasick.Search(text);
}

AhoCorasickSearcher::AhoCorasick::AhoCorasick() : root(new Node()) {}

void AhoCorasickSearcher::AhoCorasick::AddPattern(const std::string& pattern) {
    Node* current = root;
    for (char ch : pattern) {
        if (!current->children.count(ch)) {
            current->children[ch] = new Node();
        }
        current = current->children[ch];
    }
    current->isEndOfPattern = true;
}

void AhoCorasickSearcher::AhoCorasick::Build() {
    std::queue<Node*> q;
    for (auto& pair : root->children) {
        pair.second->fail = root;
        q.push(pair.second);
    }

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        for (auto& pair : current->children) {
            char ch = pair.first;
            Node* child = pair.second;

            Node* failure = current->fail;
            while (failure && !failure->children.count(ch)) {
                failure = failure->fail;
            }

            if (failure) {
                child->fail = failure->children[ch];
            } else {
                child->fail = root;
            }

            if (child->fail->isEndOfPattern) {
                child->isEndOfPattern = true;
            }

            q.push(child);
        }
    }
}

bool AhoCorasickSearcher::AhoCorasick::Search(const std::string& text) {
    Node* current = root;

    for (char ch : text) {
        while (current && !current->children.count(ch)) {
            current = current->fail;
        }

        if (current) {
            current = current->children[ch];
        } else {
            current = root;
        }

        if (current->isEndOfPattern) {
            return true;
        }
    }

    return false;
}
