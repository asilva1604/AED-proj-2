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
#include <set>

/**
 * The  Application  class for using  and managing our system
 */
class Application {
    std::unique_ptr<std::vector<Airport>> airports_;
    std::unique_ptr<std::vector<Airline>> airlines_;
    std::unique_ptr<Graph> flightNetwork_;

public:
    Application();
    Airport getAirport(const std::string &code) const;
    Airport getAirportByName(const std::string &name) const;
    Airline getAirline(const std::string &code) const;
    const Graph &getGraph();
    const std::vector<Airport> &getAirports();

    //3.1
    size_t getAirportCount();
    size_t getFlightCount();

    //3.2
    size_t flightsOutboundOfAirport(const std::string &airportCode);
    size_t airlinesOutboundOfAirport(const std::string &airportCode);

    //3.3
    size_t outboundFlightsPerCity(const std::string &city);
    size_t inboundFlightsPerCity(const std::string &city);
    size_t totalFlightsPerCity(const std::string &city);
    size_t flightsPerAirline(const std::string &airlineCode);

    //3.4
    size_t numberOfDifferentCountriesAirportFliesTo(const string &airportCode);
    size_t numberOfDifferentCountriesCityFliesTo(const string &city);
    vector<std::shared_ptr<Vertex>> getAirportsInCity(const string &city);

    //3.5
    size_t numberOfCitiesFromAirport(const string &airportCode);
    size_t numberOfAirportsFromAirport(const string &airportCode);
    size_t numberOfCountriesFromAirport(const string &airportCode);

    //3.6
    size_t numberOfAirportsFromAirportWithStops(const string &airportCode, int steps);
    size_t numberOfCitiesFromAirportWithStops(const string &airportCode, int stops);
    size_t numberOfCountriesFromAirportWithStops(const string &airportCode, int stops);

    //3.7
    std::vector<std::pair<std::pair<std::string, std::string>, int>> tripsWithGreatestNumberOfStopsFromAirport(const string &airportCode);
    std::vector<std::pair<std::pair<std::string, std::string>, int>> tripsWithGreatestNumberOfStops();

    //3.8
    std::vector<Airport> airportsWithGreatestTrafficCapacity(size_t k) const;

    //3.9
    std::set<Airport> essentialAirports() const;
    std::set<Airport> findArticulationPoints() const;

    //4.1
    std::vector<std::vector<Airport>> bestFlightAirportToAirport(const std::string &airport1,
                                                                                   const std::string &airport2);
};


#endif //AED_PROJ_2_APPLICATION_H
