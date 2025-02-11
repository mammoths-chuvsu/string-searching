#include <string-searching/base_substring_searcher.hpp>

std::optional<SubstringSearchAlgorithm> BaseSubstringSearcher::GetAlgorithmByName(
    const std::string& name) {
    if (name == "Naive") {
        return SubstringSearchAlgorithm::kNaive;
    } else if (name == "KMP") {
        return SubstringSearchAlgorithm::kKmp;
    } else if (name == "ZAlgorithm") {
        return SubstringSearchAlgorithm::kZFunction;
    } else if (name == "Rabin-Karp") {
        return SubstringSearchAlgorithm::kRabinKarp;
    } else {
        return std::nullopt;
    }
}
