#include <simulator/algorithms_creator.hpp>
#include <stdexcept>
#include <string-searching/naive_substring_searcher.hpp>

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
            }

        } else {
            throw std::invalid_argument(name + " is not in list of implemented algorithms");
        }
    }

    return algorithm_list;
}
