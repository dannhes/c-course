
#include "PercolationStats.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <random>

#include "Percolation.hpp"
// clang-format on
PercolationStats::PercolationStats(std::size_t dimension, std::size_t trials)
    : dimension(dimension), trials(trials), mean_value(0), stddev_value(0), confidence_lo(0), confidence_hi(0) {
    execute();
}

double PercolationStats::mean() const {
    return mean_value;
}

double PercolationStats::standardDeviation() const {
    return stddev_value;
}

double PercolationStats::confidenceLow() const {
    return confidence_lo;
}

double PercolationStats::confidenceHigh() const {
    return confidence_hi;
}

void PercolationStats::calculateStats() {
    double sum = std::accumulate(cont.begin(), cont.end(), 0.0);
    mean_value = sum / cont.size();

    double sq_sum = std::inner_product(cont.begin(), cont.end(), cont.begin(), 0.0);
    stddev_value  = std::sqrt(sq_sum / cont.size() - mean_value * mean_value);

    double margin = 1.96 * stddev_value / std::sqrt(trials);
    confidence_lo = mean_value - margin;
    confidence_hi = mean_value + margin;
}

void PercolationStats::execute() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, dimension - 1);

    for (std::size_t t = 0; t < trials; ++t) {
        Percolation perc(dimension);
        while (!perc.hasPercolation()) {
            std::size_t row = dist(gen);
            std::size_t col = dist(gen);
            perc.open(row, col);
        }
        cont.push_back(static_cast<double>(perc.numberOfOpenCells()) / (dimension * dimension));
    }

    calculateStats();
}
