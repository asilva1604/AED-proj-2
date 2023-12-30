#include "Application.h"
#include "Interface.h"

int main() {
    Interface anInterface;
    anInterface.run();

    /*
    Application app;

    auto start = std::chrono::high_resolution_clock::now();
    for (auto trip : app.tripsWithGreatestNumberOfStops()){
        std::cout << trip.second << " " << trip.first.first << " " << trip.first.second << std::endl;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << duration.count() << "\n";
    return 0;*/
}
