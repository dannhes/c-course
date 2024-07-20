#ifndef ACP_POOL_HPP
#define ACP_POOL_HPP
#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <list>
#include <map>
#include <new>
#include <unordered_map>
#include <vector>

class PoolAllocator {
public:
    PoolAllocator(std::size_t const block_size, std::initializer_list<std::size_t> sizes);

    void* allocate(std::size_t const n);
    void deallocate(const void* ptr);

private:
    std::vector<std::vector<char>> memory;
    // std::vector<std::vector<bool>> is_empty;
    std::map<char*, size_t> memoryMap1;
    std::map<size_t, std::list<char*>> memoryMap;
};

#endif  // ACP_POOL_HPP
