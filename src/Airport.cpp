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

Airport::Airport() = default;
