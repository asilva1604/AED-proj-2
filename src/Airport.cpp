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
    wcode_ = std::wstring(code_.begin(), code_.end());
    wname_ = std::wstring(name_.begin(), name_.end());
    wcity_ = std::wstring(city_.begin(), city_.end());
    wcountry_ = std::wstring(country_.begin(), country_.end());
    wlatitude_ = std::wstring(latitude_.begin(), latitude_.end());
    wlongitude_ = std::wstring(longitude_.begin(), longitude_.end());
}

const std::string &Airport::getCode() const {
    return code_;
}

const std::wstring &Airport::getWname() const {
    return wname_;
}

const std::wstring &Airport::getWcode() const {
    return wcode_;
}

const std::wstring &Airport::getWcity() const {
    return wcity_;
}

const std::wstring &Airport::getWcountry() const {
    return wcountry_;
}

const std::wstring &Airport::getWlatitude() const {
    return wlatitude_;
}

const std::wstring &Airport::getWlongitude() const {
    return wlongitude_;
}

bool Airport::operator==(const Airport &other) const{
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

bool Airport::operator<(const Airport &obj) const{
    return this->code_<obj.code_;
}

void Airport::setTrafficCapacity(size_t capacity) {
    trafficCapacity_ = capacity;
}

size_t Airport::getTrafficCapacity() const {
    return trafficCapacity_;
}

Airport::Airport() = default;
