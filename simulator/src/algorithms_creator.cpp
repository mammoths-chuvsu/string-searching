#include <simulator/algorithms_creator.hpp>
#include <stdexcept>
#include <string-searching/kmp_substring_searcher.hpp>
#include <string-searching/naive_substring_searcher.hpp>
#include <string-searching/rabin_karp_substring_searcher.hpp>
#include <string-searching/z_substring_searcher.hpp>

AlgorithmList AlgorithmsCreator::CreateAlgorithms(
    const std::vector<std::string>& algorithms_names) {
    AlgorithmList algorithm_list;
    for (const auto& name : algorithms_names) {
        std::optional<SubstringSearchAlgorithm> algorithm =
            BaseSubstringSearcher::GetAlgorithmByName(name);

        if (algorithm.has_value()) {
            switch (algorithm.value()) {
                case SubstringSearchAlgorithm::kNaive:
                    algorithm_list.push_back(std::make_unique<NaiveSubstringSearcher>());
                    break;
                case SubstringSearchAlgorithm::kZFunction:
                    algorithm_list.push_back(std::make_unique<ZSubstringSearcher>());
                    break;
                case SubstringSearchAlgorithm::kKmp:
                    algorithm_list.push_back(std::make_unique<KmpSubstringSearcher>());
                    break;
                case SubstringSearchAlgorithm::kRabinKarp:
                    algorithm_list.push_back(std::make_unique<RabinKarpSearcher>());
                    break;
            }
        } else {
            throw std::invalid_argument(name + " is not in list of implemented algorithms");
        }
    }

    return algorithm_list;
}
