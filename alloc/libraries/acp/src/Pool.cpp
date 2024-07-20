#include "acp/Pool.hpp"

#include <stdexcept>

PoolAllocator::PoolAllocator(std::size_t const block_size_, std::initializer_list<std::size_t> sizes) {
    memory     = std::vector<std::vector<char>>(sizes.size(), std::vector<char>(block_size_));
    memoryMap  = std::map<size_t, std::list<char*>>();
    memoryMap1 = std::map<char*, size_t>();

    size_t index = 0;
    for (auto size : sizes) {
        for (int i = 0; i < block_size_; ++i) {
            memoryMap[size].push_back(&memory[index][i]);
            memoryMap1[&memory[index][i]] = size;
        }
        ++index;
    }
}

void* PoolAllocator::allocate(std::size_t const n) {
    if (memoryMap.find(n) != memoryMap.end() && !memoryMap[n].empty()) {
        auto answ = memoryMap[n].back();
        memoryMap[n].pop_back();
        return answ;
    }
    throw std::bad_alloc();
}

void PoolAllocator::deallocate(const void* ptr) {
    auto it = memoryMap1.find(reinterpret_cast<char*>(const_cast<void*>(ptr)));
    if (it != memoryMap1.end()) {
        size_t size = it->second;
        memoryMap[size].push_back(reinterpret_cast<char*>(const_cast<void*>(ptr)));
    }
}
