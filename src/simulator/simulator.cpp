#include "simulator.hpp"

#include <chrono>
#include <iostream>

Simulator::Simulator(std::vector<std::unique_ptr<BaseSubstringSearcher>> algorithms)
    : algorithms_(std::move(algorithms)) {}

void Simulator::Run(const std::string& text, const std::string& substring, std::ostream& os) {
    for (const auto& algorithm : algorithms_) {
        const auto start = std::chrono::high_resolution_clock::now();

        const auto result = algorithm->Contains(text, substring);

        const auto stop = std::chrono::high_resolution_clock::now();
        const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        os << algorithm->getName() << '\n' << diff.count() << "ms\n-----------\n";
    }
}
