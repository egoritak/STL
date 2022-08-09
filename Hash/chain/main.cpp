#include <cmath>
#include <iostream>
#include <vector>

#include "headers/hash.h"

int main() {
    Hash<int> h_(10);

    h_.set("1", 1);
    h_.set("2", 6);
    h_.set("3", 8);
    h_.set("3", 5);
    h_.set("3", 17);
    h_.set("4", 2);
    h_.set("5", 3);

    std::cout << h_.get("1") << std::endl;
    std::cout << h_.get("2") << std::endl;
    std::cout << h_.get("3") << std::endl;
    std::cout << h_.get("4") << std::endl;
    std::cout << h_.get("5") << std::endl;

    return 0;
}
