#include <iostream>
#include "InfoSTCP.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    InfoSTCP oi;
    oi.readLines("../dataset/lines.csv");
    return 0;
}
