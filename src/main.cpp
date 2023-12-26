#include "Application.h"
#include "Interface.h"

int main() {
    //Interface anInterface;
    //anInterface.run();
    Application app;

    std::cout << app.getAirportCount() << "\n" << app.numberOfAirportsFromAirportWithStops("OPO", 0);
    return 0;
}
