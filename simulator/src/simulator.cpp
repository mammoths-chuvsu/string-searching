#include <chrono>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <simulator/simulator.hpp>

Simulator::Simulator(AlgorithmList algorithms) : algorithms_(std::move(algorithms)) {}

void Simulator::Run(const std::string& text, const std::string& substring, std::ostream& output,
                    int iterations) {
    for (const auto& algorithm : algorithms_) {
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        auto start = std::chrono::high_resolution_clock::now();
        bool result;
        double mean = 0.0;
        double deviation = 0.0;

        for (int iter = 0; iter < iterations; ++iter) {
            result = algorithm->Contains(text, substring);
            const auto stop = std::chrono::high_resolution_clock::now();
            const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            start = stop;
            mean += diff.count();
            deviation += std::pow(diff.count(), 2);
        }

        mean /= iterations;
        deviation = deviation / iterations - std::pow(mean, 2);

        output << "----------------------------\n";
        output << "Timestamp: " << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S") << "\n";
        output << "Algorithm: " << algorithm->GetName() << "\n";
        if (iterations == 1) {
            output << "Duration: " << mean << " ms\n";
        } else {
            output << "Duration mean: " << mean << " ms\n";
            output << "Duration standard deviation: " << deviation << " ms\n";
        }

        if (result) {
            output << "Status: Substring found\n";
        } else {
            output << "Status: Substring not found\n";
        }

        output << "----------------------------\n\n";
    }
}
