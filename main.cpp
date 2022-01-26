#include <iostream>
#include "GetDataSet.h"
#include "InfoSTCP.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    InfoSTCP oi;
    oi.readLines("../dataset/lines.csv");
    GetDataSet g("../dataset/stops.csv");
    g.getStops();

    return 0;
}
