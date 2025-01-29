#include <iostream>

#include "argument_parser.hpp"
#include "simulator/algorithms_creator.hpp"
#include "simulator/simulator.hpp"
#include "simulator/utils.hpp"

int main(int argc, char** argv) {
    ArgumentParser parser(argc, argv);

    std::vector<std::string> algorithm_names = parser.GetAlgorithmsNames();
    std::string substring = parser.GetSubstring();
    std::string text = parser.GetText();

    if (algorithm_names.empty() || substring.empty() || text.empty()) {
        std::cerr << "Missing required arguments. Use --help for more information.\n";
        return 1;
    }

    AlgorithmList algorithms = AlgorithmsCreator::CreateAlgorithms(algorithm_names);

    Simulator simulator(std::move(algorithms));

    simulator.Run(text, substring, std::cout);

    return 0;
}