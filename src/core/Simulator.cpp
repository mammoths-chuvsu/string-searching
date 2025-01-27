#include "Simulator.hpp"

#include <chrono>
#include <iostream>

Simulator::Simulator(std::vector<std::unique_ptr<BaseSubstringSearcher>> algorithms)
    : algorithms_(std::move(algorithms)) {}

void Simulator::Run(const std::string& text, const std::string& substring, std::ostream& os) {
    for (const auto& algorithm : algorithms_) {
        auto start = std::chrono::high_resolution_clock::now();

        auto result = algorithm->Contains(text, substring);

        auto stop = std::chrono::high_resolution_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        os << algorithm->getName() << '\n' << diff.count() << "ms\n-----------\n";
    }
}
