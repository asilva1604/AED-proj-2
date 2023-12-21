//
// Created by alexandre on 21-12-2023.
//

#ifndef AED_PROJ_2_FILEREADER_H
#define AED_PROJ_2_FILEREADER_H

#include <fstream>
#include <vector>
#include <sstream>
#include <string>


class FileReader {
    std::ifstream file_;
    std::vector<std::vector<std::string>> data_;

public:
    FileReader(const std::string &fName);
    std::vector<std::vector<std::string>> getData();

};


#endif //AED_PROJ_2_FILEREADER_H
