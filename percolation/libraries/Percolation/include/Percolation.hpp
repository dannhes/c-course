
#ifndef PERCOLATION_HPP
#define PERCOLATION_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

class Percolation {
private:
    std::size_t dimension;
    std::vector<std::vector<bool>> grid;
    std::vector<std::vector<bool>> full;
    std::size_t open_cells;

    void fill(std::size_t row, std::size_t col);

public:
    Percolation(std::size_t dimension);

    void open(std::size_t row, std::size_t column);

    [[nodiscard]] bool isOpen(std::size_t row, std::size_t column) const;

    [[nodiscard]] bool isFull(std::size_t row, std::size_t column) const;

    [[nodiscard]] std::size_t numberOfOpenCells() const;

    [[nodiscard]] bool hasPercolation() const;
};

#endif  // PERCOLATION_HPP
