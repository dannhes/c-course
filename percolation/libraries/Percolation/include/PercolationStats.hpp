
#ifndef PERCOLATIONSTATS_HPP
#define PERCOLATIONSTATS_HPP
#include <cstddef>
#include <cstdint>
#include <vector>

class PercolationStats {
private:
    std::size_t dimension;
    std::size_t trials;
    std::vector<double> thresholds;
    double mean_value;
    double stddev_value;
    double confidence_lo;
    double confidence_hi;

    void calculateStats();

public:
    PercolationStats(std::size_t dimension, std::size_t trials);

    [[nodiscard]] double mean() const;

    [[nodiscard]] double standardDeviation() const;

    [[nodiscard]] double confidenceLow() const;

    [[nodiscard]] double confidenceHigh() const;

    void execute();
};

#endif  // PERCOLATIONSTATS_HPP
