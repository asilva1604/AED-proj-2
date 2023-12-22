//
// Created by alexandre on 21-12-2023.
//

#ifndef AED_PROJ_2_APPLICATION_H
#define AED_PROJ_2_APPLICATION_H

#include "FileReader.h"
#include <vector>
#include "Airline.h"
#include "Airport.h"
#include "Graph.h"
#include <algorithm>

/**
 * The  Application  class for using  and managing our system
 */
class Application {
    std::vector<Airport> airports_;
    std::vector<Airline> airlines_;
    Graph<Airport> flightNetwork_;

public:
    Application();
    Airport getAirport(const std::string &code) const;
    Airline getAirline(const std::string &code) const;
};


#endif //AED_PROJ_2_APPLICATION_H
