#include "algorithms_creator.hpp"

#include <stdexcept>

#include "lib/naive_substring_searcher.hpp"

AlgorithmList AlgorithmsCreator::CreateAlgorithms(
    const std::vector<const std::string>& algorithmsNames) {
    AlgorithmList algorithmList;
    for (const auto& name : algorithmsNames) {
        std::optional<SubstringSearchAlgorithm> algorithm =
            BaseSubstringSearcher::GetAlgorithmByName(name);

        if (algorithm.has_value()) {
            switch (algorithm.value()) {
                case SubstringSearchAlgorithm::kNaive:
                    algorithmList.push_back(std::make_unique<NaiveSubstringSearcher>());
                    break;
            }

        } else {
            throw std::invalid_argument(name + " is not in list of implemented algorithms");
        }
    }

    return algorithmList;
}
