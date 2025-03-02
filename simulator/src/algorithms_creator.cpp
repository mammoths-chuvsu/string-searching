#include <memory>
#include <simulator/algorithms_creator.hpp>
#include <stdexcept>
#include <string-searching/aho_corasick_substring_searcher.hpp>
#include <string-searching/boyer_moore_substring_searcher.hpp>
#include <string-searching/brute_force_substring_searcher.hpp>
#include <string-searching/kmp_substring_searcher.hpp>
#include <string-searching/rabin_karp_substring_searcher.hpp>
#include <string-searching/shift_or_substring_searcher.hpp>
#include <string-searching/suffix_tree_substring_searcher.hpp>
#include <string-searching/z_substring_searcher.hpp>

#include "simulator/utils.hpp"

AlgorithmList AlgorithmsCreator::CreateAlgorithms(
    const std::vector<std::string>& algorithms_names) {
    using AlgorithmFactory = std::function<std::unique_ptr<BaseSubstringSearcher>()>;

    static std::unordered_map<std::string, AlgorithmFactory> factory_map = {
        {"brute-force", []() { return std::make_unique<BruteForceSubstringSearcher>(); }},
        {"KMP", []() { return std::make_unique<KmpSubstringSearcher>(); }},
        {"Rabin-Karp", []() { return std::make_unique<RabinKarpSearcher>(); }},
        {"Z-algorithm", []() { return std::make_unique<ZSubstringSearcher>(); }},
        {"shift-or", []() { return std::make_unique<ShiftOrSubstringSearcher>(); }},
        {"Aho-Corasick", []() { return std::make_unique<AhoCorasickSearcher>(); }},
        {"suffix-tree", []() { return std::make_unique<SuffixTreeSubstringSearcher>(); }},
        {"boyer-moore", []() { return std::make_unique<BoyerMooreSubstringSearcher>(); }},
    };

    AlgorithmList algorithm_list;
    if (algorithms_names.empty()) {
        algorithm_list.reserve(factory_map.size());

        for (const auto& [name, factory] : factory_map) {
            algorithm_list.push_back(factory());
        }
    }

    algorithm_list.reserve(algorithms_names.size());

    for (const auto& name : algorithms_names) {
        auto iterator = factory_map.find(name);
        if (iterator == factory_map.end()) {
            throw std::invalid_argument(name + " is not in list of implemented algorithms");
        }
        algorithm_list.push_back(iterator->second());
    }

    return algorithm_list;
}
