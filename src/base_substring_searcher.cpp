#include <string-searching/base_substring_searcher.hpp>

std::optional<SubstringSearchAlgorithm> BaseSubstringSearcher::GetAlgorithmByName(
    const std::string& name) {
    if (name == "Naive") {
        return SubstringSearchAlgorithm::kNaive;
    } else {
        return std::nullopt;
    }
}
