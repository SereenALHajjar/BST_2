#include<iostream>
#include<bst.hpp>
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