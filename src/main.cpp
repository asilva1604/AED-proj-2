#include <iostream>
#include "Application.h"
#include "Graph.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Application app;
    for (const auto &airport : app.getGraph().getVertexSet()) {
        for (const auto &e : airport->getAdj()) {
            std::cout << airport->getInfo() << " " << e.getDest()->getInfo() << " " << e.getAirline().getCode() << "\n";
        }
    }

    return 0;
}
