#include <iostream>
#include "GetDataSet.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    GetDataSet g("../dataset/stops.csv");
    g.getStops();
    return 0;
}
