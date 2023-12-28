//
// Created by alexandre on 21-12-2023.
//

#include "Application.h"
#include <chrono>

Application::Application()
        : airports_(std::make_unique<std::vector<Airport>>()),
          airlines_(std::make_unique<std::vector<Airline>>()),
          flightNetwork_(std::make_unique<Graph>())
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

    for (const auto& airport : *airports_) {
        flightNetwork_->addVertex(airport);
    }

    auto start = std::chrono::high_resolution_clock::now();
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
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << duration.count() << "\n";

}

Airport Application::getAirport(const std::string &code) const {
    for (const auto &airport : *airports_) {
        if (airport.getCode() == code) {
            return airport;
        }
    }
    return {};
}

Airline Application::getAirline(const std::string &code) const {
    for (const auto &airline : *airlines_) {
        if (airline.getCode() == code) {
            return airline;
        }
    }
    return {};
}

const Graph &Application::getGraph() {
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
    auto airport = flightNetwork_->findVertex(airportObj);

    return airport->getAdj().size();
}

size_t Application::airlinesOutboundOfAirport(const std::string &airportCode) {
    auto airportObj = getAirport(airportCode);
    auto airport = flightNetwork_->findVertex(airportObj);

    return airport->getNumDifferentAirlines();
}

std::vector<std::shared_ptr<Vertex>> Application::getAirportsInCity(const std::string &city){
    auto vertexVector = flightNetwork_->getVertexSet();

    std::vector<std::shared_ptr<Vertex>> airportsInCity;

    for (const auto& p : vertexVector) {
        if (p.second->getInfo().getCity() == city) {
            airportsInCity.push_back(p.second);
        }
    }

    return airportsInCity;
}

size_t Application::outboundFlightsPerCity(const std::string &city) {

    std::vector<std::shared_ptr<Vertex>> airportsInCity = getAirportsInCity(city);

    size_t res = 0;

    for (const auto& vertex : airportsInCity) {
        res += vertex->getAdj().size();
    }

    return res;
}

size_t Application::inboundFlightsPerCity(const std::string &city) {
    auto vertexVector = flightNetwork_->getVertexSet();

    size_t res = 0;

    for (auto p : vertexVector) {
        if (p.second->getInfo().getCity() == city) continue;

        for (const Edge &e : p.second->getAdj()) {
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

    for (auto p : vertexVector) {
        for (const Edge &edge : p.second->getAdj()) {
            if (edge.getAirline().getCode() == airlineCode) ++res;
        }
    }

    return res;
}

size_t Application::numberOfDifferentCountriesAirportFliesTo(const std::string &airportCode) {
    auto airportObj = getAirport(airportCode);
    auto airport = flightNetwork_->findVertex(airportObj);

    unordered_set<std::string> countries;

    size_t res = 0;

    for (const Edge& destinyAirports : airport->getAdj()){
        countries.insert(destinyAirports.getDest()->getInfo().getCountry());
    }

    res += countries.size();

    return res;
}

size_t Application::numberOfDifferentCountriesCityFliesTo(const std::string &city){
    std::vector<std::shared_ptr<Vertex>> airportsInCity = getAirportsInCity(city);

    unordered_set<std::string> countries;

    size_t res = 0;

    for (const auto& airport : airportsInCity) {
        for (const Edge& destinyAirports : airport->getAdj()){
            countries.insert(destinyAirports.getDest()->getInfo().getCountry());
        }
    }

    res += countries.size();

    return res;
}

size_t Application::numberOfCitiesFromAirport(const std::string &airportCode){
    auto airportObj = getAirport(airportCode);
    auto airport = flightNetwork_->findVertex(airportObj);

    unordered_set<std::string> cities;

    for (const Edge& edge : airport->getAdj()){
        cities.insert(edge.getDest()->getInfo().getCity());
    }

    return cities.size();
}

size_t Application::numberOfAirportsFromAirportWithStops(const std::string &airportCode, int stops){
    ++stops;
    auto airportObj = getAirport(airportCode);
    auto airport = flightNetwork_->findVertex(airportObj);

    return flightNetwork_->bfsWithSteps(airport->getInfo(), stops).size() - 1;
}

size_t Application::numberOfCitiesFromAirportWithStops(const std::string &airportCode, int stops){
    ++stops;
    auto airportObj = getAirport(airportCode);
    auto airport = flightNetwork_->findVertex(airportObj);

    unordered_set<std::string> cities;

    std::vector airportsInRange = flightNetwork_->bfsWithSteps(airport->getInfo(), stops);
    airportsInRange.erase(airportsInRange.begin());

    for (const Airport& airport1 : airportsInRange){
        cities.insert(airport1.getCity());
    }

    return cities.size();
}

size_t Application::numberOfCountriesFromAirportWithStops(const std::string &airportCode, int stops){
    ++stops;
    auto airportObj = getAirport(airportCode);
    auto airport = flightNetwork_->findVertex(airportObj);

    unordered_set<std::string> countries;

    std::vector airportsInRange = flightNetwork_->bfsWithSteps(airport->getInfo(), stops);
    airportsInRange.erase(airportsInRange.begin());

    for (const Airport& airport1 : airportsInRange){
        countries.insert(airport1.getCountry());
    }

    return countries.size();
}

std::vector<std::pair<std::pair<std::string, std::string>, int>> Application::tripsWithGreatestNumberOfStopsFromAirport(const std::string &airportCode){
    auto airportObj = getAirport(airportCode);
    auto airport = flightNetwork_->findVertex(airportObj);

    std::vector<std::pair<Airport, int>> mostStops = flightNetwork_->bfsFurthestVertices(airport->getInfo());
    std::vector<std::pair<std::pair<std::string, std::string>, int>> trips;

    trips.reserve(mostStops.size());
    for (const auto& dest_airport : mostStops){
        trips.push_back({{airportCode, dest_airport.first.getCode()}, dest_airport.second});
    }
    return trips;
}

std::vector<std::pair<std::pair<std::string, std::string>, int>> Application::tripsWithGreatestNumberOfStops(){
    int max_length = INT8_MIN;

    std::vector<std::pair<std::pair<std::string, std::string>, int>> longest_trips;

    for (const auto& vertex : flightNetwork_->getVertexSet()){
        std::vector<std::pair<std::pair<std::string, std::string>, int>> trips = tripsWithGreatestNumberOfStopsFromAirport(vertex.second->getInfo().getCode());
        if (trips[0].second > max_length){
            max_length = trips[0].second;
            longest_trips.clear();
        }
        if (trips[0].second == max_length){
            for (const auto& trip : trips){
                longest_trips.push_back(trip);
            }
        }
    }
    return longest_trips;
}

size_t Application::numberOfAirportsFromAirport(const string &airportCode) {
    auto airportObj = getAirport(airportCode);
    auto airport = flightNetwork_->findVertex(airportObj);

    std::set<Airport> airports;

    for (const Edge& edge : airport->getAdj()){
        airports.insert(edge.getDest()->getInfo());
    }

    return airports.size();
}

size_t Application::numberOfCountriesFromAirport(const string &airportCode) {
    auto airportObj = getAirport(airportCode);
    auto airport = flightNetwork_->findVertex(airportObj);

    std::set<std::string> cities;

    for (const Edge& edge : airport->getAdj()){
        cities.insert(edge.getDest()->getInfo().getCity());
    }

    return cities.size();
}


std::vector<Airport> Application::airportsWithGreatestTrafficCapacity(size_t k) const{
    auto copyMap(flightNetwork_->getVertexSet());
    vector<std::shared_ptr<Vertex>> copy;

    copy.reserve(copyMap.size());
    for (const auto& p : copyMap) copy.push_back(p.second);

    std::sort(copy.begin(), copy.end(), [](const std::shared_ptr<Vertex>& obj1, const std::shared_ptr<Vertex>& obj2) {
        return obj1->getInfo().getTrafficCapacity() > obj2->getInfo().getTrafficCapacity();
    });

    std::vector<Airport> res;

    for (size_t i = 0; i < k; i++) {
        res.push_back(copy.at(i)->getInfo());
    }

    return res;
}

void dfsArt(const std::shared_ptr<Vertex>& v, int &index, std::set<Airport> &articulationPoints) {
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
        v.second->setVisited(false);
        v.second->setNum(0);
    }

    for (auto &v : flightNetwork_->getVertexSet()) {
        if (!v.second->isVisited()) {
            dfsArt(v.second, index, articulationPoints);
        }
    }

    return articulationPoints;
}

std::set<Airport> Application::essentialAirports() const {
    std::set res = findArticulationPoints();
    return res;
}

