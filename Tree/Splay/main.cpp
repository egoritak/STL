#include <iostream>

#include "src/tree.cpp"

int main() {
    Splay tree;

    tree.insert(5);
    tree.insert(4);
    tree.insert(3);
    tree.insert(2);
    tree.insert(1);

    tree.print();

    std::cout << "find " << tree.find(1)->data_ << "..." << '\n';

    tree.print();

    return 0;
}
