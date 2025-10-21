#include "bst.hpp"

BST::BST() {
    root = nullptr;
}

void BST::put(crefkey_t key, crefvalue_t value) {
    std::lock_guard<std::mutex> lock(mtx);
    root = put_impl(root, key, value);
}

value_t BST::get(crefkey_t key) {
    std::lock_guard<std::mutex> lock(mtx);
    return get_impl(root, key);
}

void BST::print_inorder() {
    std::lock_guard<std::mutex> lock(mtx);
    print_inorder_imp(root);
}

int BST::comparision(crefkey_t a, crefkey_t b) {
    size_t mn = std::min(a.size(), b.size());
    for (size_t i = 0; i < mn; i++) {
        if (a[i] > b[i]) return 1;
        else if (b[i] > a[i]) return -1;
    }
    if (a.size() > b.size()) return 1;
    if (b.size() > a.size()) return -1;
    return 0;
}

Node* BST::put_impl(Node* cur_node, crefkey_t key, crefvalue_t value) {
    if (cur_node == nullptr) {
        Node* new_node = new Node;
        new_node->key = key;
        new_node->value = value;
        new_node->left = new_node->right = nullptr;
        return new_node;
    }

    if (comparision(cur_node->key, key) == 1) {
        cur_node->left = put_impl(cur_node->left, key, value);
    } else if (comparision(cur_node->key, key) == -1) {
        cur_node->right = put_impl(cur_node->right, key, value);
    } else {
        cur_node->value = value;
    }
    return cur_node;
}

value_t BST::get_impl(Node* cur_node, crefkey_t key) {
    if (cur_node == nullptr) {
        value_t not_found;
        return not_found;
    } else if (comparision(cur_node->key, key) == 1) {
        return get_impl(cur_node->left, key);
    } else if (comparision(cur_node->key, key) == -1) {
        return get_impl(cur_node->right, key);
    } else {
        return cur_node->value;
    }
}

void BST::print_inorder_imp(Node* cur_node) {
    if (cur_node == nullptr)
        return;
    std::cout << std::endl;
    for (auto x : cur_node->key)
        std::cout << x;
    std::cout << " ";
    for (auto x : cur_node->value)
        std::cout << x;
    print_inorder_imp(cur_node->left);
    print_inorder_imp(cur_node->right);
}
