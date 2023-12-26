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

        auto source = flightNetwork_->findVertex(sourceAirport);
        auto dest = flightNetwork_->findVertex(destinationAirport);

        source->getInfo().setTrafficCapacity(source->getInfo().getTrafficCapacity()+1);
        dest->getInfo().setTrafficCapacity(dest->getInfo().getTrafficCapacity()+1);

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

size_t Application::numberOfAirportsFromAirportWithStops(const std::string &airportCode, int stops){
    auto airportObj = getAirport(airportCode);
    auto *airport = flightNetwork_->findVertex(airportObj);

    return flightNetwork_->bfsWithSteps(airport->getInfo(), stops).size() - 1;
}

size_t Application::numberOfCitiesFromAirportWithStops(const std::string &airportCode, int stops){
    auto airportObj = getAirport(airportCode);
    auto *airport = flightNetwork_->findVertex(airportObj);

    unordered_set<std::string> cities;

    std::vector<Airport> airportsInRange = flightNetwork_->bfsWithSteps(airport->getInfo(), stops);
    airportsInRange.erase(airportsInRange.begin());

    for (const Airport& airport1 : airportsInRange){
        cities.insert(airport1.getCity());
    }

    return cities.size();
}

size_t Application::numberOfCountriesFromAirportWithStops(const std::string &airportCode, int stops){
    auto airportObj = getAirport(airportCode);
    auto *airport = flightNetwork_->findVertex(airportObj);

    unordered_set<std::string> countries;

    std::vector<Airport> airportsInRange = flightNetwork_->bfsWithSteps(airport->getInfo(), stops);
    airportsInRange.erase(airportsInRange.begin());

    for (const Airport& airport1 : airportsInRange){
        countries.insert(airport1.getCountry());
    }

    return countries.size();
}

std::vector<std::pair<std::string, std::string>> Application::tripsWithGreatestNumberOfStops(const std::string &airportCode){
    auto airportObj = getAirport(airportCode);
    auto *airport = flightNetwork_->findVertex(airportObj);

    std::vector<Airport> mostStops = flightNetwork_->bfsFurthestVertices(airport->getInfo());
    std::vector<std::pair<std::string, std::string>> trips;

    for (const Airport& dest_airport : mostStops){
        std::cout << airport->getInfo().getCity() << " " << dest_airport.getCity() << std::endl;
        trips.emplace_back(airport->getInfo().getCode(), dest_airport.getCode());
    }

    return trips;
}

size_t Application::numberOfAirportsFromAirport(const string &airportCode) {
    auto airportObj = getAirport(airportCode);
    auto *airport = flightNetwork_->findVertex(airportObj);

    std::set<Airport> airports;

    for (const Edge<Airport>& edge : airport->getAdj()){
        airports.insert(edge.getDest()->getInfo());
    }

    return airports.size();
}

size_t Application::numberOfCountriesFromAirport(const string &airportCode) {
    auto airportObj = getAirport(airportCode);
    auto *airport = flightNetwork_->findVertex(airportObj);

    std::set<std::string> cities;

    for (const Edge<Airport>& edge : airport->getAdj()){
        cities.insert(edge.getDest()->getInfo().getCity());
    }

    return cities.size();
}

std::vector<Airport> Application::airportsWithGreatestTrafficCapacity(size_t k) const{
    auto copy(flightNetwork_->getVertexSet());

    std::sort(copy.begin(), copy.end(), [](Vertex<Airport> *obj1, Vertex<Airport> *obj2) {
        return obj1->getInfo().getTrafficCapacity() > obj2->getInfo().getTrafficCapacity();
    });

    std::vector<Airport> res;

    for (size_t i = 0; i < k; i++) {
        res.push_back(copy.at(i)->getInfo());
    }

    return res;
}

void dfsArt(Vertex<Airport> *v, int &index, std::set<Airport> &articulationPoints) {
    v->setVisited(true);
    v->setNum(index);
    v->setLow(index);
    index++;

    int children = 0;

    for (auto &e : v->getAdj()) {
        auto w = e.getDest();

        if (!w->isVisited()) {
            children++;
            dfsArt(w, index, articulationPoints);
            v->setLow(min(v->getLow(), w->getLow()));

            if (v->getNum() == 0 && children > 1) {
                // Special case for the root of DFS tree
                articulationPoints.insert(v->getInfo());
            } else if (v->getNum() != 0 && w->getLow() >= v->getNum()) {
                // Regular articulation point
                articulationPoints.insert(v->getInfo());
            }
        } else if (w->getNum() < v->getNum()) {
            // Back edge, update low value
            v->setLow(min(v->getLow(), w->getNum()));
        }
    }
}

std::set<Airport> Application::findArticulationPoints() const{
    std::set<Airport> articulationPoints;
    int index = 0;

    for (auto &v : flightNetwork_->getVertexSet()) {
        v->setVisited(false);
        v->setNum(0);
    }

    for (auto &v : flightNetwork_->getVertexSet()) {
        if (!v->isVisited()) {
            dfsArt(v, index, articulationPoints);
        }
    }

    return articulationPoints;
}

std::set<Airport> Application::essentialAirports() const {
    std::set<Airport> res = findArticulationPoints();
    return res;
}


