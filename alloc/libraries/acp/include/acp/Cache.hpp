#ifndef ACP_CACHE_HPP
#define ACP_CACHE_HPP
#include <cstddef>
#include <list>
#include <new>
#include <ostream>
#include <utility>
template <class Key, class KeyProvider, class Allocator>
class Cache {
public:
    template <class... AllocArgs>
    Cache(const std::size_t cache_size, AllocArgs &&...alloc_args)
        : m_max_size(cache_size), m_alloc(std::forward<AllocArgs>(alloc_args)...) {}

    //    ~Cache() {
    //        for (auto el : que) {
    //            m_alloc.template destroy<KeyProvider>(el);
    //        }
    //    }

    std::size_t size() const { return que.size(); }

    bool empty() const { return que.empty(); }

    template <class T>
    T &get(const Key &key);

    std::ostream &print(std::ostream &strm) const;

    friend std::ostream &operator<<(std::ostream &strm, const Cache &cache) { return cache.print(strm); }

private:
    const std::size_t m_max_size;
    std::list<std::pair<KeyProvider *, bool>> que;
    Allocator m_alloc;
};

template <class Key, class KeyProvider, class Allocator>
template <class T>
inline T &Cache<Key, KeyProvider, Allocator>::get(const Key &key) {
    for (auto &entry : que) {
        if (*entry.first == key) {
            entry.second = true;
            return *static_cast<T *>(entry.first);
        }
    }

    if (que.size() >= m_max_size) {
        bool removed = false;
        while (!removed) {
            auto last_entry = que.back();
            que.pop_back();
            if (last_entry.second) {
                que.push_front(last_entry);
                que.front().second = false;
            } else {
                m_alloc.template destroy<KeyProvider>(last_entry.first);
                removed = true;
            }
        }
    }
    que.push_front(std::make_pair(m_alloc.template create<T>(key), false));
    return *static_cast<T *>(que.front().first);
}

template <class Key, class KeyProvider, class Allocator>
inline std::ostream &Cache<Key, KeyProvider, Allocator>::print(std::ostream &strm) const {
    return strm << "<empty>\n";
}

#endif  // ACP_CACHE_HPP