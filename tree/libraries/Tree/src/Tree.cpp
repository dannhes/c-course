
#include "tree/Tree.hpp"

struct Splay::Node {
    int key;
    Splay::Node* left;
    Splay::Node* parent;
    Splay::Node* right;
    ~Node() {
        delete left;
        delete right;
    };
    Node(int k) : key(k), left(), parent(), right() {}
};

void rotateLeft(Splay::Node* p) {
    if (p == nullptr) {
        return;
    }
    Splay::Node* v = p->parent;
    Splay::Node* r = p->right;
    if (v != nullptr) {
        if (v->left == p) {
            v->left = r;
        } else {
            v->right = r;
        }
    }
    Splay::Node* tmp = r->left;
    r->left          = p;
    p->right         = tmp;
    p->parent        = r;
    r->parent        = v;
    if (p->right != nullptr) {
        p->right->parent = p;
    }
}

void rotateRight(Splay::Node* p) {
    if (p == nullptr) {
        return;
    }
    Splay::Node* v = p->parent;
    Splay::Node* r = p->left;
    if (v != nullptr) {
        if (v->right == p) {
            v->right = r;
        } else {
            v->left = r;
        }
    }
    Splay::Node* tmp = r->right;
    r->right         = p;
    p->left          = tmp;
    p->parent        = r;
    r->parent        = v;
    if (p->left != nullptr) {
        p->left->parent = p;
    }
}

Splay::Node* splay(Splay::Node* v) {
    while (v->parent != nullptr) {
        if (v == v->parent->left) {
            if (v->parent->parent == nullptr) {
                rotateRight(v->parent);
            } else if (v->parent == v->parent->parent->left) {
                rotateRight(v->parent->parent);
                rotateRight(v->parent);
            } else {
                rotateRight(v->parent);
                rotateLeft(v->parent);
            }
        } else {
            if (v->parent->parent == nullptr) {
                rotateLeft(v->parent);
            } else if (v->parent == v->parent->parent->right) {
                rotateLeft(v->parent->parent);
                rotateLeft(v->parent);
            } else {
                rotateLeft(v->parent);
                rotateRight(v->parent);
            }
        }
    }
    return v;
}

Splay::Node* search(Splay::Node* x, int key) {
    if (x == nullptr) {
        return x;
    }
    if (x->key == key) {
        return x;
    }
    if (key < x->key) {
        if (x->left != nullptr) {
            return search(x->left, key);
        }
    } else {
        if (x->right != nullptr) {
            return search(x->right, key);
        }
    }
    return x;
}

bool Splay::insert(int key) {
    if (root == nullptr) {
        root = new Node(key);
        size_of++;
        return true;
    }
    if (contains(key)) {
        root = splay(search(root, key));
        return false;
    }
    Node* newNode   = new Node(key);
    newNode->parent = search(root, key);
    if (newNode->key > search(root, key)->key) {
        search(root, key)->right = newNode;
    } else if (newNode->key < search(root, key)->key) {
        search(root, key)->left = newNode;
    }
    root = splay(newNode);
    size_of++;
    return true;
}
Splay::Node* maximum(Splay::Node* localRoot) {
    Splay::Node* minim = localRoot;
    while (minim->right != nullptr) {
        minim = minim->right;
    }
    return minim;
}

Splay::Node* merge(Splay::Node* a, Splay::Node* b) {
    if (a == nullptr) {
        return b;
    }
    if (b == nullptr) {
        return a;
    }
    Splay::Node* c = maximum(a);
    if (c != nullptr) {
        a = splay(c);
    }
    if (a != nullptr) {
        a->right         = b;
        a->right->parent = a;
    }
    return a;
}

bool Splay::remove(int key) {
    Node* remove = search(root, key);
    if (remove == nullptr) {
        return false;
    }
    if (remove->key != key) {
        root = splay(remove);
        return false;
    }
    root = splay(remove);
    if (root->left != nullptr) {
        root->left->parent = nullptr;
    }
    if (root->right != nullptr) {
        root->right->parent = nullptr;
    }
    root = merge(root->left, root->right);
    // remove->left  = nullptr;
    // remove->right = nullptr;
    size_of--;
    return true;
}

bool Splay::contains(int value) const noexcept {
    Node* x = search(root, value);
    if (x == nullptr) {
        return false;
    }
    if (x->key != value) {
        root = splay(x);
        return false;
    }
    root = splay(x);
    return true;
}

std::size_t Splay::size() const noexcept {
    return size_of;
}

void collectValues(Splay::Node* node, std::vector<int>& values) {
    if (node != nullptr) {
        collectValues(node->left, values);
        values.push_back(node->key);
        collectValues(node->right, values);
    }
}

std::vector<int> Splay::values() const noexcept {
    std::vector<int> result;
    result.reserve(Splay::size());
    collectValues(root, result);
    return result;
}
bool Splay::empty() const noexcept {
    return Splay::size() == 0;
}
Splay::~Splay() {
    delete root;
};