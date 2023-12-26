#include "Application.h"
#include "Interface.h"

int main() {
    //Interface anInterface;
    //anInterface.run();
    Application app;

    auto vec = app.essentialAirports();

    std::cout << vec.size();
    return 0;
}
