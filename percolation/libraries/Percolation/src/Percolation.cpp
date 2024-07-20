
#include "Percolation.hpp"

#include <queue>

Percolation::Percolation(std::size_t dimension)
    : dimension(dimension)
    , grid(dimension, std::vector<bool>(dimension, false))
    , full(dimension, std::vector<bool>(dimension, false))
    , open_cells(0) {}

void Percolation::open(std::size_t row, std::size_t column) {
    if (!isOpen(row, column)) {
        grid[row][column] = true;
        ++open_cells;

        if (row == 0 || (row > 0 && isFull(row - 1, column))) {
            fill(row, column);
        } else {
            if (row > 0 && isFull(row - 1, column)) {
                fill(row, column);
            }
            if (row < dimension - 1 && isFull(row + 1, column)) {
                fill(row, column);
            }
            if (column > 0 && isFull(row, column - 1)) {
                fill(row, column);
            }
            if (column < dimension - 1 && isFull(row, column + 1)) {
                fill(row, column);
            }
        }
    }
}

bool Percolation::isOpen(std::size_t row, std::size_t column) const {
    return grid[row][column];
}

bool Percolation::isFull(std::size_t row, std::size_t column) const {
    return full[row][column];
}

std::size_t Percolation::numberOfOpenCells() const {
    return open_cells;
}

bool Percolation::hasPercolation() const {
    for (std::size_t i = 0; i < dimension; ++i) {
        if (full[dimension - 1][i]) {
            return true;
        }
    }
    return false;
}

void Percolation::fill(std::size_t row, std::size_t col) {
    if (row >= dimension || col >= dimension || !isOpen(row, col) || isFull(row, col)) {
        return;
    }

    std::queue<std::pair<std::size_t, std::size_t>> q;
    q.push({row, col});
    full[row][col] = true;

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        if (r > 0 && isOpen(r - 1, c) && !isFull(r - 1, c)) {
            full[r - 1][c] = true;
            q.push({r - 1, c});
        }
        if (r < dimension - 1 && isOpen(r + 1, c) && !isFull(r + 1, c)) {
            full[r + 1][c] = true;
            q.push({r + 1, c});
        }
        if (c > 0 && isOpen(r, c - 1) && !isFull(r, c - 1)) {
            full[r][c - 1] = true;
            q.push({r, c - 1});
        }
        if (c < dimension - 1 && isOpen(r, c + 1) && !isFull(r, c + 1)) {
            full[r][c + 1] = true;
            q.push({r, c + 1});
        }
    }
}
