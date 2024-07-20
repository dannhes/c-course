#include "iostream"
#include "../libraries/Tree/include/tree/Tree.hpp"
#include "../libraries/Tree/src/Tree.cpp"
int main() {
    Splay tree = Splay();
    std::cout << tree.empty() << std::endl;
    std::cout << tree.insert(0) << std::endl;
    std::cout << tree.insert(1)<< std::endl;
    std::cout << tree.insert(2) << std::endl;
    std::cout << tree.contains(123)<< std::endl;
    for(int i = 0;i<10;i++){
        tree.insert(i);
    }
    for(int i = 0;i<10;i++){
        tree.remove(i);
        //std::cout << tree.contains(i)<< std::endl;
    }
    std::cout << tree.empty() << std::endl;
    return 0;
}
