#include "Application.h"
#include "Interface.h"

int main() {/*
    Interface anInterface;
    anInterface.run();
    */
    Application app;

    auto start = std::chrono::high_resolution_clock::now();
    for (const auto &airline : app.airlinesAvailableForFlight(Airport("OPO"), Airport("LIS"))){

    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << duration.count() << "\n";
    return 0;
}
