#include <iostream>
#include <cstdint>
#include <vector>
// using namespace std ;

using key_t = std::vector<uint8_t>;
using value_t = std::vector<uint8_t>;

using crefkey_t = const key_t &;
using crefvalue_t = const value_t &;

struct Node
{
    key_t key;
    value_t value;

    Node *right;
    Node *left;
};
class BST
{
public:
    Node *root;

    BST()
    {
        root = nullptr;
    }
    void print_inorder()
    {
        print_inorder_imp(root);
    }
    void print_inorder_imp(Node *cur_node)
    {
        if (cur_node == nullptr)
            return;
        for (auto x : cur_node->key)
            std::cout << int(x);
        std::cout << " ";
        for (auto x : cur_node->value)
            std::cout << int(x);
        std::cout << std::endl;
        print_inorder_imp(cur_node->left);
        std::cout << std::endl;
        print_inorder_imp(cur_node->right);
    }

    int comparision(crefkey_t a, crefkey_t b)
    {
        size_t mn = std::min(a.size(), b.size());
        for (int i = 0; i < mn; i++)
        {
            if (a[i] > b[i])
                return 1;
            else if (b[i] > a[i])
                return -1;
        }
        if (a.size() > b.size())
            return 1;
        if (b.size() > a.size())
            return -1;
        return 0;
    }
    void put(crefkey_t key, crefvalue_t value)
    {
        root = put_impl(root, key, value);
    }

    Node *put_impl(Node *cur_node, crefkey_t key, crefvalue_t value)
    {
        if (cur_node == nullptr)
        {
            Node *new_node = new Node;
            new_node->key = key;
            new_node->value = value;
            new_node->left = new_node->right = nullptr;
            return new_node;
        }

        if (comparision(cur_node->key, key) == 1)
        {
            cur_node->left = put_impl(cur_node->left, key, value);
        }
        else if (comparision(cur_node->key, key) == -1)
        {
            cur_node->right = put_impl(cur_node->right, key, value);
        }
        else
        {
            cur_node->value = value;
        }
        return cur_node;
    }
    value_t get_impl(Node *cur_node, crefkey_t key)
    {
        if (cur_node == nullptr)
        {
            value_t not_found;
            return not_found;
        }
        else if (comparision(cur_node->key, key) == 1)
            return get_impl(cur_node->left, key);
        else if (comparision(cur_node->key, key) == -1)
            return get_impl(cur_node->right, key);
        else
            return cur_node->value;
    }
    value_t get(crefkey_t key)
    {
        return get_impl(root, key);
    }
};
int main()
{

    BST tree;

    key_t key1 = {1, 2, 3};
    value_t value1 = {10, 20};

    key_t key2 = {4, 5, 6};
    value_t value2 = {30, 40};

    key_t key3 = {2, 3, 4};
    value_t value3 = {50, 60};

    tree.put(key1, value1);
    tree.put(key2, value2);
    tree.put(key3, value3);

    std::cout << "Inorder traversal:\n";
    tree.print_inorder();

    key_t get_key = {4, 5, 6};
    value_t result = tree.get(get_key);

    std::cout << "\nGet value for key {4,5,6}: ";
    for (auto b : result)
        std::cout << (int)b << " ";
    std::cout << std::endl;

    return 0;
}