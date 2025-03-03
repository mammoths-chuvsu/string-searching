#ifndef STRING_SEARCHING_SUFFIX_TREE_SUBSTRING_SEARCHER_HPP
#define STRING_SEARCHING_SUFFIX_TREE_SUBSTRING_SEARCHER_HPP

#include <string>
#include <utility>
#include <vector>

#include "base_substring_searcher.hpp"

// Internal helper classes and functions.
// They are placed in a separate namespace (detail) to mark them as implementation details.
namespace detail {

const int INF = 1e9;

struct sg_tree {
    std::vector<int> arr;
    int size;  // dynamic size (power of two)

    // Method declarations for sg_tree.
    void build(const std::vector<int>& x, int n);
    int get_min(int idx, int cl, int cr, int l, int r);
    int get_min(int l, int r);
};

/// Computes the suffix array and LCP array of string s.
/// Returns a pair of vectors: (suffix array, LCP array).
std::pair<std::vector<int>, std::vector<int>> compute(std::string& s);

struct suffix_tree {
    struct edge {
        int from;
        int to;
        int next_vert;
        int suffix_here;
    };

    struct vertex {
        std::vector<edge> go;
    };

    std::string str;
    std::vector<vertex> data;

    // Method declarations for suffix_tree.
    void build(std::string& s);
    int search_str(std::string& s);
};

}  // namespace detail

/**
 * \brief Implementation of suffix tree string searching algorithm.
 */
class SuffixTreeSubstringSearcher : public BaseSubstringSearcher {
public:
    SuffixTreeSubstringSearcher();

    // Checks whether substring is contained in text.
    bool Contains(const std::string& text, const std::string& substring) const override;
};

#endif  // STRING_SEARCHING_SUFFIX_TREE_SUBSTRING_SEARCHER_HPP
