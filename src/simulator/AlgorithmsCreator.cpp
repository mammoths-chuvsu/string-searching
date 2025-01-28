#include "AlgorithmsCreator.hpp"

#include <stdexcept>

#include "lib/NaiveSubstringSearcher.hpp"

AlgorithmList AlgorithmsCreator::CreateAlgorithms(const std::vector<std::string>& algorithmsNames) {
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
}
