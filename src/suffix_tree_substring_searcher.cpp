#include <algorithm>  // for std::min and std::fill
#include <string-searching/suffix_tree_substring_searcher.hpp>
#include <string>
#include <utility>
#include <vector>

using namespace std;

namespace detail {

// ------- Implementation of sg_tree --------

void sg_tree::build(const vector<int> &x, int n) {
    size = 1;
    while (size < n) size *= 2;
    arr.assign(2 * size, INF);
    for (int i = 0; i < n; i++) arr[i + size] = x[i];
    for (int i = size - 1; i > 0; i--) arr[i] = min(arr[i << 1], arr[(i << 1) + 1]);
}

int sg_tree::get_min(int idx, int cl, int cr, int l, int r) {
    if (l > cr || r < cl) return INF;
    if (l <= cl && cr <= r) return arr[idx];
    int mid = (cl + cr) >> 1;
    return min(get_min(idx << 1, cl, mid, l, r), get_min((idx << 1) + 1, mid + 1, cr, l, r));
}

int sg_tree::get_min(int l, int r) { return get_min(1, 0, size - 1, l, r); }

// ------- Implementation of compute --------

pair<vector<int>, vector<int>> compute(string &s) {
    int n = s.size();
    int maxn = n + 256;  // 256 for alphabet
    vector<int> p(n), c(n), cnt(maxn, 0);
    for (int i = 0; i < n; i++) cnt[s[i]]++;
    for (int i = 1; i < maxn; i++) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i;
    int cl = 0;
    c[p[0]] = cl;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i - 1]]) cl++;
        c[p[i]] = cl;
    }
    vector<int> lcp(n, 0);
    for (int i = 1; i < n; i++) lcp[i] = (c[p[i]] == c[p[i - 1]]) ? 1 : 0;
    vector<int> pn(n), cn(n), lcpn(n);
    vector<int> rpos(n), lpos(n);
    sg_tree rmq;
    int k = 1;
    while (k < n) {
        fill(cnt.begin(), cnt.end(), 0);
        for (int i = 0; i < n; i++) rpos[c[p[i]]] = i;
        for (int i = n - 1; i >= 0; i--) lpos[c[p[i]]] = i;
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - k;
            if (pn[i] < 0) pn[i] += n;
        }
        for (int i = 0; i < n; i++) cnt[c[i]]++;
        for (int i = 1; i < maxn; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];
        cl = 0;
        cn[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            int m1 = (p[i] + k) % n, m2 = (p[i - 1] + k) % n;
            if (c[p[i]] != c[p[i - 1]] || c[m1] != c[m2]) cl++;
            cn[p[i]] = cl;
        }
        rmq.build(lcp, n);
        for (int i = 1; i < n; i++) {
            int a = p[i], b = p[i - 1];
            if (c[a] != c[b])
                lcpn[i] = lcp[lpos[c[a]]];
            else {
                int aa = (a + k) % n, bb = (b + k) % n;
                if (c[aa] == c[bb])
                    lcpn[i] = (k << 1);
                else
                    lcpn[i] = k + rmq.get_min(lpos[c[bb]] + 1, rpos[c[aa]]);
            }
            lcpn[i] = min(n, lcpn[i]);
        }
        c = cn;
        lcp = lcpn;
        k <<= 1;
    }
    return {p, lcp};
}

// ------- Implementation of suffix_tree --------

void suffix_tree::build(string &s) {
    // Build suffix and LCP arrays.
    auto info = compute(s);
    vector<int> p = info.first, lcp = info.second;
    int n = s.size();
    str = s;
    data.clear();

    // Stack for unfinished edges.
    vector<int> p_vert;
    vector<int> p_edge;
    vector<int> p_dist;

    // Add the first edge.
    vertex v;
    edge e;
    e.from = p[0];
    e.to = n;
    e.next_vert = -1;
    e.suffix_here = p[0];
    v.go.push_back(e);
    data.push_back(v);

    p_vert.push_back(0);
    p_edge.push_back(0);
    p_dist.push_back(0);

    for (int i = 1; i < n; i++) {
        int c_lcp = lcp[i];
        // Climb up to the proper level.
        while (p_dist.back() > c_lcp) {
            edge &E = data[p_vert.back()].go[p_edge.back()];
            if (E.next_vert != -1) {
                for (auto &child : data[E.next_vert].go)
                    E.suffix_here = min(E.suffix_here, child.suffix_here);
            }
            p_vert.pop_back();
            p_edge.pop_back();
            p_dist.pop_back();
        }
        vertex new_vertex;
        edge new_edge;
        int c_v = p_vert.back();
        int c_e = p_edge.back();
        int At = data[c_v].go[c_e].from + c_lcp - p_dist.back();
        p_dist.push_back(c_lcp);
        new_edge.next_vert = -1;
        new_edge.suffix_here = p[i];
        new_edge.from = p[i] + c_lcp;
        new_edge.to = n;

        if (At == data[c_v].go[c_e].from) {
            data[c_v].go.push_back(new_edge);
            p_vert.push_back(c_v);
            p_edge.push_back(data[c_v].go.size() - 1);
        } else {
            new_vertex.go.push_back(data[c_v].go[c_e]);
            new_vertex.go.back().from = At;
            new_vertex.go.push_back(new_edge);
            data.push_back(new_vertex);
            data[c_v].go[c_e].next_vert = data.size() - 1;
            data[c_v].go[c_e].to = At;
            p_vert.push_back(data.size() - 1);
            p_edge.push_back(1);
        }
    }

    while (!p_dist.empty()) {
        edge &E = data[p_vert.back()].go[p_edge.back()];
        if (E.next_vert != -1) {
            for (auto &child : data[E.next_vert].go)
                E.suffix_here = min(E.suffix_here, child.suffix_here);
        }
        p_vert.pop_back();
        p_edge.pop_back();
        p_dist.pop_back();
    }
}

int suffix_tree::search_str(string &s) {
    int n = s.size();
    int cur_v = 0;
    for (int i = 0; i < n;) {
        if (cur_v == -1) break;
        char t = s[i];
        int cur_e = -1;
        // Find an edge whose starting character is at least t.
        for (int j = 0; j < data[cur_v].go.size(); j++) {
            if (str[data[cur_v].go[j].from] >= t) {
                cur_e = j;
                break;
            }
        }
        if (cur_e == -1) return -1;
        int j;
        for (j = data[cur_v].go[cur_e].from; i < n && j < data[cur_v].go[cur_e].to; j++, i++) {
            if (str[j] != s[i]) {
                i = n + 1;  // mismatch found
                break;
            }
        }
        if (i == n) return data[cur_v].go[cur_e].suffix_here;
        cur_v = data[cur_v].go[cur_e].next_vert;
    }
    return -1;
}

}  // namespace detail

// ------- Implementation of SuffixTreeSubstringSearcher --------

SuffixTreeSubstringSearcher::SuffixTreeSubstringSearcher() : BaseSubstringSearcher("suffix-tree") {}

bool SuffixTreeSubstringSearcher::Contains(const std::string &text,
                                           const std::string &substring) const {
    if (substring.empty()) return true;
    if (text.length() < substring.length()) return false;

    // Append a termination symbol (assumed not to be in text).
    string modified_text = text;
    modified_text.push_back('#');

    detail::suffix_tree tree;
    tree.build(modified_text);

    // Use the suffix tree to search for the substring.
    string search_query = substring;
    int result = tree.search_str(search_query);
    return result != -1;
}
