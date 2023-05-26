#include <iostream>
#include "src/MyClass.h"


int main() {
    std::cout << "Hello, World!";

    auto r = dayan3847::MyClass::hello();
    std::cout << r;

    return 0;
}
