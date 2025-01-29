#include "simulator.hpp"

#include <chrono>
#include <iostream>

Simulator::Simulator(AlgorithmList algorithms) : algorithms_(std::move(algorithms)) {}

void Simulator::Run(const std::string& text, const std::string& substring, std::ostream& output) {
    for (const auto& algorithm : algorithms_) {
        const auto start = std::chrono::high_resolution_clock::now();

        const auto result = algorithm->Contains(text, substring);

        const auto stop = std::chrono::high_resolution_clock::now();
        const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        output << algorithm->getName() << '\n' << diff.count() << "ms\n-----------\n";
    }
}
