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
}

Airport Application::getAirport(const std::string &code) const {
    for (const auto &airport : *airports_) {
        if (airport.getCode() == code) {
            return airport;
        }
    }
    return Airport();
}

Airline Application::getAirline(const string &code) const {
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
