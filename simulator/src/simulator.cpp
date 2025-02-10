#include "simulator.hpp"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <ctime>

Simulator::Simulator(AlgorithmList algorithms) : algorithms_(std::move(algorithms)) {}

void Simulator::Run(const std::string& text, const std::string& substring, std::ostream& output) {
    for (const auto& algorithm : algorithms_) {
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        const auto start = std::chrono::high_resolution_clock::now();

        const auto result = algorithm->Contains(text, substring);

        const auto stop = std::chrono::high_resolution_clock::now();
        const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        output << "----------------------------\n";
        output << "Timestamp: " << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S") << "\n";
        output << "Algorithm: " << algorithm->GetName() << "\n";
        output << "Duration: " << diff.count() << " ms\n";

        if (result) {
            output << "Status: Substring found\n";
        } else {
            output << "Status: Substring not found\n";
        }

        output << "----------------------------\n\n";
    }
}
