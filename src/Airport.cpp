//
// Created by alexandre on 21-12-2023.
//

#include "Airport.h"

Airport::Airport(const std::string &code, const std::string &name, const std::string &city, const std::string &country,
                 const std::string &latitude, const std::string &longitude) {
    code_ = code;
    name_ = name;
    city_ = city;
    country_ = country;
    latitude_ = latitude;
    longitude_ = longitude;
}

const std::string &Airport::getCode() const {
    return code_;
}

bool Airport::operator==(const Airport &other) {
    if (other.getCode() == code_) return true;
    return false;
}

std::ostream &operator<<(std::ostream &stream, const Airport &airport) {
    stream << airport.code_;
    return stream;
}

const std::string &Airport::getCity() const {
    return city_;
}

const std::string &Airport::getCountry() const {
    return country_;
}

Airport::Airport() = default;
