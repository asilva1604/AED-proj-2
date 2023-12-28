//
// Created by alexandre on 21-12-2023.
//

#ifndef AED_PROJ_2_AIRLINE_H
#define AED_PROJ_2_AIRLINE_H

#include <string>

class Airline {
    std::string code_;
    std::string name_;
    std::string callsign_;
    std::string country_;
public:
    Airline(const std::string &code, const std::string &name, const std::string &callsign, const std::string &country);
    const std::string &getCode() const;
    Airline();
    bool operator==(const Airline &other) const;
};


#endif //AED_PROJ_2_AIRLINE_H
