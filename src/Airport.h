//
// Created by alexandre on 21-12-2023.
//

#ifndef AED_PROJ_2_AIRPORT_H
#define AED_PROJ_2_AIRPORT_H

#include <string>

class Airport {
    std::string code_;
    std::string name_;
    std::string city_;
    std::string country_;
    std::string latitude_;
    std::string longitude_;

public:
    Airport(const std::string &code, const std::string &name, const std::string &city, const std::string &country,
            const std::string &latitude, const std::string &longitude);
    Airport();
    const std::string &getCode() const;

};


#endif //AED_PROJ_2_AIRPORT_H
