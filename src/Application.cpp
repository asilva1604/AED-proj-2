//
// Created by alexandre on 21-12-2023.
//

#include "Application.h"

Application::Application()
        : airports_(std::make_unique<std::vector<Airport>>()),
          airlines_(std::make_unique<std::vector<Airline>>()),
          flightNetwork_(std::make_unique<Graph<Airport>>())
{
    FileReader airlineData("../dataset/airlines.csv");
    FileReader airportsData("../dataset/airports.csv");
    FileReader flightsData("../dataset/flights.csv");

    for (const auto &line : airportsData.getData()) {
        airports_->emplace_back(line.at(0), line.at(1), line.at(2), line.at(3), line.at(4), line.at(5));
    }
    for (const auto &line : airlineData.getData()) {
        airlines_->emplace_back(line.at(0), line.at(1), line.at(2), line.at(3));
    }

    for (auto airport : *airports_) {
        flightNetwork_->addVertex(airport);
    }

    for (const auto &line : flightsData.getData()) {
        auto sourceAirportCode = line.at(0);
        auto destinationAirportCode = line.at(1);
        auto airlineCode = line.at(2);

        Airport sourceAirport = getAirport(sourceAirportCode);
        Airport destinationAirport = getAirport(destinationAirportCode);
        Airline airline = getAirline(airlineCode);

        flightNetwork_->addEdge(sourceAirport, destinationAirport, 0, airline);
    }

    std::cout << "Constructor has done it's job.\n";
}

Airport Application::getAirport(const std::string &code) const {
    for (const auto &airport : *airports_) {
        if (airport.getCode() == code) {
            return airport;
        }
    }
    return Airport();
}

Airline Application::getAirline(const std::string &code) const {
    for (const auto &airline : *airlines_) {
        if (airline.getCode() == code) {
            return airline;
        }
    }
    return Airline();
}

const Graph<Airport> &Application::getGraph() {
    return *flightNetwork_;
}

const std::vector<Airport> &Application::getAirports() {
    return *airports_;
}

size_t Application::getAirportCount() {
    return airports_->size();
}

size_t Application::getFlightCount() {
    return flightNetwork_->getNumEdge();
}

size_t Application::flightsOutboundOfAirport(const string &airportCode) {
    auto airportObj = getAirport(airportCode);
    auto *airport = flightNetwork_->findVertex(airportObj);

    return airport->getAdj().size();
}

size_t Application::airlinesOutboundOfAirport(const std::string &airportCode) {
    auto airportObj = getAirport(airportCode);
    auto *airport = flightNetwork_->findVertex(airportObj);

    return airport->getNumDifferentAirlines();
}

std::vector<Vertex<Airport> *> Application::getAirportsInCity(const std::string &city){
    auto vertexVector = flightNetwork_->getVertexSet();

    std::vector<Vertex<Airport> *> airportsInCity;

    for (Vertex<Airport> *vertex : vertexVector) {
        if (vertex->getInfo().getCity() == city) {
            airportsInCity.push_back(vertex);
        }
    }

    return airportsInCity;
}

size_t Application::outboundFlightsPerCity(const std::string &city) {

    std::vector<Vertex<Airport> *> airportsInCity = getAirportsInCity(city);

    size_t res = 0;

    for (const Vertex<Airport> *vertex : airportsInCity) {
        res += vertex->getAdj().size();
    }

    return res;
}

size_t Application::inboundFlightsPerCity(const std::string &city) {
    auto vertexVector = flightNetwork_->getVertexSet();

    size_t res = 0;

    for (Vertex<Airport> *vertex : vertexVector) {
        if (vertex->getInfo().getCity() == city) continue;

        for (const Edge<Airport> &e : vertex->getAdj()) {
            if (e.getDest()->getInfo().getCity() == city) ++res;
        }
    }
    return res;
}

size_t Application::totalFlightsPerCity(const std::string &city) {
    return inboundFlightsPerCity(city) + outboundFlightsPerCity(city);
}

size_t Application::flightsPerAirline(const std::string &airlineCode) {
    size_t res = 0;
    auto vertexVector = flightNetwork_->getVertexSet();

    for (Vertex<Airport> *vertex : vertexVector) {
        for (const Edge<Airport> &edge : vertex->getAdj()) {
            if (edge.getAirline().getCode() == airlineCode) ++res;
        }
    }

    return res;
}

size_t Application::numberOfDifferentCountriesAirportFliesTo(const std::string &airportCode) {
    auto airportObj = getAirport(airportCode);
    auto *airport = flightNetwork_->findVertex(airportObj);

    unordered_set<std::string> countries;

    size_t res = 0;

    for (const Edge<Airport>& destinyAirports : airport->getAdj()){
        countries.insert(destinyAirports.getDest()->getInfo().getCountry());
    }

    res += countries.size();

    return res;
}

size_t Application::numberOfDifferentCountriesCityFliesTo(const std::string &city){
    std::vector<Vertex<Airport> *> airportsInCity = getAirportsInCity(city);

    unordered_set<std::string> countries;

    size_t res = 0;

    for (const Vertex<Airport> *airport : airportsInCity) {
        for (const Edge<Airport>& destinyAirports : airport->getAdj()){
            countries.insert(destinyAirports.getDest()->getInfo().getCountry());
        }
    }

    res += countries.size();

    return res;
}

size_t Application::numberOfCitiesFromAirport(const std::string &airportCode){
    auto airportObj = getAirport(airportCode);
    auto *airport = flightNetwork_->findVertex(airportObj);

    unordered_set<std::string> cities;

    for (const Edge<Airport>& edge : airport->getAdj()){
        cities.insert(edge.getDest()->getInfo().getCity());
    }

    return cities.size();
}
