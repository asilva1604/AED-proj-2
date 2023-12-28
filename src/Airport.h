//
// Created by alexandre on 21-12-2023.
//

#ifndef AED_PROJ_2_AIRPORT_H
#define AED_PROJ_2_AIRPORT_H

#include <string>
#include <iostream>

class Airport {
    std::string code_;
    std::string name_;
    std::string city_;
    std::string country_;
    long double latitude_;
    long double longitude_;
    std::wstring wcode_;

    size_t trafficCapacity_ = 0;

public:
    Airport(const std::string &code, const std::string &name, const std::string &city, const std::string &country,
            const std::string &latitude, const std::string &longitude);
    Airport();
    Airport(const std::string &code); //dummy constructor
    const std::string &getCode() const;
    bool operator==(const Airport &other) const;
    friend std::ostream& operator<<(std::ostream &stream, const Airport &airport);
    const std::string &getCity() const;

    const std::string &getCountry() const;

    const std::wstring &getWcode() const;

    bool operator<(const Airport &obj) const;

    void setTrafficCapacity(size_t capacity);

    size_t getTrafficCapacity() const;

    const std::string &getName() const;

    const long double &getLatitude() const;
    const long double &getLongitude() const;

};


#endif //AED_PROJ_2_AIRPORT_H
