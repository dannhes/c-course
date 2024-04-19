#ifndef TREE_HPP
#define TREE_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

class Splay {
public:
    struct Node;

    [[nodiscard]] bool contains(int value) const noexcept;
    bool insert(int value);
    bool remove(int value);

    [[nodiscard]] std::size_t size() const noexcept;
    [[nodiscard]] bool empty() const noexcept;

    [[nodiscard]] std::vector<int> values() const noexcept;
    ~Splay();

private:
    mutable Node* root          = nullptr;
    mutable std::size_t size_of = 0;
};

#endif
