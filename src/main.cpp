#include "Application.h"
#include "Interface.h"

int main() {
    //Interface anInterface;
    //anInterface.run();
    Application app;

    auto vec = app.airportsWithGreatestTrafficCapacity(5);

    for (const auto & i : vec) {
        std::cout << i.getCode() << "\n";
    }
    return 0;
}
