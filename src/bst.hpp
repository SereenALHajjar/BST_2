#pragma once

#include <iostream>
#include <cstdint>
#include <vector>
#include <mutex>

// Type aliases
using key_t = std::vector<uint8_t>;
using value_t = std::vector<uint8_t>;

using crefkey_t = const key_t&;
using crefvalue_t = const value_t&;

// Node structure
struct Node {
    key_t key;
    value_t value;
    Node* left;
    Node* right;
};

// Binary Search Tree (thread-safe)
class BST {
private:
    Node* root;
    std::mutex mtx;

    void print_inorder_imp(Node* cur_node);
    int comparision(crefkey_t a, crefkey_t b);
    Node* put_impl(Node* cur_node, crefkey_t key, crefvalue_t value);
    value_t get_impl(Node* cur_node, crefkey_t key);

public:
    BST();
    void put(crefkey_t key, crefvalue_t value);
    value_t get(crefkey_t key);
    void print_inorder();
};
