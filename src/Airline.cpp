//
// Created by alexandre on 21-12-2023.
//

#include "Airline.h"

Airline::Airline(const std::string &code, const std::string &name, const std::string &callsign,
                 const std::string &country) {
    code_ = code;
    name_ = name;
    callsign_ = callsign;
    country_ = country;
}

const std::string &Airline::getCode() const {
    return code_;
}

bool Airline::operator==(const Airline &other) const{
    return other.getCode() == code_;
}

Airline::Airline() = default;
