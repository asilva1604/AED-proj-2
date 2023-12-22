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
#include <memory>

/**
 * The  Application  class for using  and managing our system
 */
class Application {
    std::unique_ptr<std::vector<Airport>> airports_;
    std::unique_ptr<std::vector<Airline>> airlines_;
    std::unique_ptr<Graph<Airport>> flightNetwork_;

public:
    Application();
    Airport getAirport(const std::string &code) const;
    Airline getAirline(const std::string &code) const;
    const Graph<Airport> &getGraph();
    const std::vector<Airport> &getAirports();
    size_t getAirportCount();
    size_t getFlightCount();

    //3.2
    size_t flightsOutboundOfAirport(const std::string &airportCode);
    size_t airlinesOutboundOfAirport(const std::string &airportCode);

    //3.3
    size_t outboundFlightsPerCity(const std::string &city);
    size_t inboundFlightsPerCity(const std::string &city);
};


#endif //AED_PROJ_2_APPLICATION_H
