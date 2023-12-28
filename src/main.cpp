#include "Application.h"
#include "Interface.h"

int main() {/*
    Interface anInterface;
    anInterface.run();
    */
    Application app;

    auto start = std::chrono::high_resolution_clock::now();
    for (const auto &trip : app.bestFlightAirportToAirport("YBX", "SRV")){
        for (const auto &airport : trip) {
            std::cout << airport.getCode() << "||";
        }
        std::cout << std::endl;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << duration.count() << "\n";
    return 0;
}
