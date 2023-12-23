#include <iostream>
#include "Application.h"
#include "Graph.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Application app;
    std::cout << app.numberOfDifferentCountriesCityFliesTo("Paris");
    return 0;
}
