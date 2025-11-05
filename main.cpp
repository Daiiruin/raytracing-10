#include <iostream>
#include "core/Vec3.hpp"

int main() {
    Vec3 a(1,2,3);
    Vec3 b(4,5,6);
    std::cout << "Dot product: " << a.dot(b) << std::endl;
    return 0;
}
