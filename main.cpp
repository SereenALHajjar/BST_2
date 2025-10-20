#include <iostream>
#include <cstdint>
#include <vector>
// using namespace std ;

using byte_array_t = std::vector<uint8_t>;
using key_t = byte_array_t;
using value_t = byte_array_t;

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
    Node root;

    BST()
    {
        root.right = root.left = nullptr;
    }
    void print_inorder(Node *cur_node)
    {
        if (cur_node == nullptr)
            return;
        for (auto x : cur_node->key)
            std::cout << (char)x;
        std::cout << " ";
        for (auto x : cur_node->value)
            std::cout << x;
        std::cout << std::endl;
        print_inorder(cur_node->left);
        std::cout << std::endl;
        print_inorder(cur_node->right);
        std::cout << std::endl;
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
        if(a.size() > b.size()) return 1 ; 
        if(b.size() > a.size()) return -1 ; 
        return 0 ;
    }
    void put(crefkey_t key, crefvalue_t value)
    {
        put_impl(&root, key, value);
    }
    void put_impl(Node *cur_node, crefkey_t key, crefvalue_t value)
    {
        if (cur_node == nullptr)
        {
            Node new_node;
            new_node.key = key;
            new_node.value = value;
            new_node.left = new_node.right = nullptr;
            cur_node = &new_node;
        }
        else if (comparision(cur_node->key, key) == 1)
            put_impl(cur_node->left, key, value);
        else if (comparision(cur_node->key, key) == -1)
            put_impl(cur_node->right, key, value);
        else
            cur_node->value = value;
    }

    value_t get_impl(Node *cur_node , crefkey_t key)
    {
        if(cur_node == nullptr)
        {
            value_t not_found ; 
            return not_found ; 
        }
        else if(comparision(cur_node->key , key) == 1)
            return get_impl(cur_node->left , key) ;
        else if(comparision(cur_node->key , key) == -1)
            return get_impl(cur_node->right , key) ;
        else return cur_node->value ; 
    }
    value_t get(crefkey_t key)
    {
        return get_impl(&root , key) ;
    }

};

byte_array_t from_str(std::string s) {
    return byte_array_t(s.begin(), s.end());
}

int main()
{

    BST tree;

    tree.put(from_str("one"), from_str("one"));
    
    tree.put(from_str("two"), from_str("two"));

    tree.put(from_str("three"), from_str("three"));

    std::cout << "Inorder traversal:\n";
    tree.print_inorder(&tree.root);

    value_t result = tree.get(from_str("two"));

    for (auto b : result)
        std::cout << (int)b << " ";
    std::cout << std::endl;

    return 0;
}