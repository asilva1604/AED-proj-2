#include "Application.h"
#include "Interface.h"

int main() {
    //Interface anInterface;
    //anInterface.run();
    Application app;

    auto start = std::chrono::high_resolution_clock::now();
    auto vec = app.airportsWithGreatestTrafficCapacity(10);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << duration.count() << "\n";

    for (const auto & p : vec)  {
        std::cout << p.getCode() << "\n";
    }
    return 0;
}
