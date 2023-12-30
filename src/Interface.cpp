//
// Created by master on 23-12-2023.
//

#include "Interface.h"
#include "Printer.h"

Interface::Interface()= default;


void Interface::alphabeticSortVector(std::vector<std::wstring> &wstr){
    std::sort(wstr.begin(), wstr.end(), [](const auto& a, const auto& b){
        if (a > b){
            return false;
        }
        else {
            return true;
        }
    });
}

void Interface::getAirportCodes(const std::unordered_map<std::string, Airport>& airports){
    for (const auto& airport : airports){
        airportCodeVector.push_back(airport.second.getWcode());
    }
}

void Interface::getAirlineCodes(const std::unordered_map<std::string, Airline>& airlines){
    for (const auto& airline : airlines){
        airlineCodeVector.push_back(airline.second.getWcode());
    }
}

void Interface::getCities(){
    for (const auto& airport : app->getAirports()){
        if (std::find(citiesVector.begin(), citiesVector.end(), airport.second.getWcity()) == citiesVector.end()){
            citiesVector.push_back(airport.second.getWcity());
        }
    }
}

std::wstring Interface::smooth_string(const std::wstring& w){
    std::wstring sw;
    for (wchar_t c : w) {
        if (!iswspace(c)) {
            c = std::tolower(c);
            switch (c) {
                case L'á':
                case L'à':
                case L'â':
                case L'ä':
                case L'ã':
                case L'Á':
                case L'À':
                case L'Ã':
                case L'Â':
                case L'Ä':
                    sw += L'a';
                    break;
                case L'é':
                case L'è':
                case L'ê':
                case L'ë':
                case L'ẽ':
                case L'Ë':
                case L'É':
                case L'È':
                case L'Ê':
                case L'Ẽ':
                    sw += L'e';
                    break;
                case L'í':
                case L'ì':
                case L'î':
                case L'ï':
                case L'ĩ':
                case L'Í':
                case L'Ì':
                case L'Î':
                case L'Ĩ':
                case L'Ï':
                    sw += L'i';
                    break;
                case L'ó':
                case L'ò':
                case L'ô':
                case L'ö':
                case L'õ':
                case L'Ó':
                case L'Ò':
                case L'Õ':
                case L'Ô':
                case L'Ö':
                    sw += L'o';
                    break;
                case L'ú':
                case L'ù':
                case L'û':
                case L'ü':
                case L'ũ':
                case L'Ú':
                case L'Ù':
                case L'Ũ':
                case L'Û':
                case L'Ü':
                    sw += L'u';
                    break;
                case L'ç':
                    sw += L'c';
                default:
                    if (!ispunct(c)) {
                        sw += c;
                    }
            }
        }
    }
    return sw;
}


std::vector<std::wstring> Interface::filterSearch(const std::vector<std::wstring>& wstrings){
    int left = 0;
    int right = wstrings.size() - 1;
    int mid;
    std::vector<std::wstring> res;
    if (write.empty() || write == write_default){
        res = wstrings;
    }
    else {
        while (left <= right) {
            mid = (left + right) / 2;
            if (smooth_string(wstrings[mid].substr(0, write.size())) == smooth_string(write)) {
                break;
            } else if (smooth_string(wstrings[mid].substr(0, write.size())) < smooth_string(write)) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        if (mid != 0) {
            while (smooth_string(wstrings[mid - 1].substr(0, write.size())) == smooth_string(write)) {
                mid--;
                if (mid == 0){
                    break;
                }
            }
        }
        while (smooth_string(wstrings[mid].substr(0, write.size())) == smooth_string(write)) {
            res.push_back(wstrings[mid]);
            mid++;
        }
    }
    return res;
}


void Interface::writeOptionDefaulterAirport(){
    if (!write.empty() && write != write_default) {
        options[location][0] = L"Searching for: " + bold + write + end_effect;
    } else {
        options[location][0] = L"Search for an Airport code";
    }
    if (selected == 0 && write.empty() && !table_mode){
        options[location][0] = underline + bold + red + L"Search for an Airport code -> " + end_effect + L"  " + italic + write_default + end_italic;
        write_mode = true;
    }
    else if (selected == 0 && !table_mode){
        options[location][0] = underline + bold + red + L"Search for an Airport code -> " + end_effect + L"  " + write;
        write_mode = true;
    }
}


void Interface::writeOptionDefaulterCity(){
    if (!write.empty() && write != write_default) {
        options[location][0] = L"Searching for: " + bold + write + end_effect;
    } else {
        options[location][0] = L"Search for a City Name";
    }
    if (selected == 0 && write.empty() && !table_mode){
        options[location][0] = underline + bold + red + L"Search for a City Name -> " + end_effect + L"  " + italic + write_default + end_italic;
        write_mode = true;
    }
    else if (selected == 0 && !table_mode){
        options[location][0] = underline + bold + red + L"Search for a City Name -> " + end_effect + L"  " + write;
        write_mode = true;
    }
}


void Interface::writeOptionDefaulterAirline(){
    if (!write.empty() && write != write_default) {
        options[location][0] = L"Searching for: " + bold + write + end_effect;
    } else {
        options[location][0] = L"Search for a Airline Code";
    }
    if (selected == 0 && write.empty() && !table_mode){
        options[location][0] = underline + bold + red + L"Search for a Airline Code -> " + end_effect + L"  " + italic + write_default + end_italic;
        write_mode = true;
    }
    else if (selected == 0 && !table_mode){
        options[location][0] = underline + bold + red + L"Search for a Airline Code -> " + end_effect + L"  " + write;
        write_mode = true;
    }
}


void Interface::numeralWriteOptionsDefaulter(){
    options[location][0] = L"Number of Stops: " + bold + num_write + end_effect;
    if (selected == 0 && !table_mode){
        options[location][0] = underline + bold + red + L"Insert Number of Stops -> " + end_effect + L"  " + num_write;
        write_mode = true;
    }
}


void Interface::basicInputResponse(unsigned int user_in){
    if (locationHasTable[location]){
        if (user_in == '\t'){
            table_mode = !table_mode;
            selected = 0;
            selected_in_page = 0;
        }
        if (user_in == 'n'){
            page ++;
            selected_in_page = 0;
            if (page > filteredWstringVector.size()/elements_per_page) {
                page--;
            }
        }
        if (user_in == 'p'){
            page --;
            selected_in_page = 0;
            if (page < 0){
                page ++;
            }
        }
    }
    if (!table_mode){
        if (user_in == 'A') {
            if (selected > 0) { selected -= 1; }
            else { selected = options[location].size() - 1; }
        }
        if (user_in == 'B') {
            selected ++;
            if (selected >= options[location].size()) {selected = 0;}
        }
    }
    else{
        if (user_in == 'A') {
            if (selected_in_page > 0) { selected_in_page -= 1; }
            else if (page == filteredWstringVector.size()/elements_per_page){
                selected_in_page = filteredWstringVector.size()%elements_per_page - 1;
            }
            else {
                selected_in_page = elements_per_page - 1;
            }
        }
        if (user_in == 'B') {
            selected_in_page ++;
            if (page == filteredWstringVector.size()/elements_per_page){
                if (selected_in_page > filteredWstringVector.size()%elements_per_page - 1){
                    selected_in_page = 0;
                }
            }
            else{
                if (selected_in_page > elements_per_page - 1){
                    selected_in_page = 0;
                }
            }
        }
    }
    if (user_in == 'q') {
        location = -1;
    }
    //========================= ENTER INPUTS ===========================//
    if (user_in == '\n') {
        switch (location) {
            case 1:       //============================= MAIN MENU ===============================//
                switch (selected) {
                    case 0:
                        break;
                    case 1:
                        directory = L"Statistics";
                        selected = 0;
                        location = 2;
                        break;
                    case 2:
                        location = -1;
                        break;
                }
                break;

            case 2:       //============================= STATISTICS ===============================//
                switch (selected) {
                    case 0:
                        directory = L"Statistics > Global Statistics";
                        earlier_location = location;
                        location = 3;
                        break;
                    case 1:
                        directory = L"Statistics > Choose an Airport";
                        earlier_location = location;
                        filteredWstringVector = airportCodeVector;
                        selected = 0;
                        location = 7;
                        break;
                    case 2:
                        directory = L"Statistics > Choose a City";
                        earlier_location = location;
                        filteredWstringVector = citiesVector;
                        selected = 0;
                        location = 20;
                        break;
                    case 3:
                        directory = L"Statistics > Choose an Airline";
                        earlier_location = location;
                        filteredWstringVector = airlineCodeVector;
                        selected = 0;
                        location = 24;
                        break;
                    case 4:
                        directory = L"";
                        selected = 0;
                        location = 1;
                        break;
                }
                break;

            case 3:       //==================== STATISTICS > GLOBAL STATISTICS ====================//
                switch (selected) {
                    case 0:
                        directory = L"Statistics > Global Statistics > Number of Airports";
                        earlier_location = location;
                        location = 4;
                        break;
                    case 1:
                        directory = L"Statistics > Global Statistics > Number of Available Flights";
                        selected = 0;
                        earlier_location = location;
                        location = 5;
                        break;
                    case 2:
                        directory = L"Statistics > Global Statistics > Trip(s) with the Most Number of Stops";
                        if (furthest_trips.empty()) {
                            appThread = std::thread([this]() {
                                furthest_trips = app->tripsWithGreatestNumberOfStops();
                                is_done = true;
                            });
                        }
                        while(furthest_trips.empty() && !is_done){
                            printAnimatedAirplane(airplaneLoadingScreen, 100);
                            printTextLoadingData();
                        }
                        if (is_done){
                            appThread.join();
                            is_done = false;
                        }
                        selected = 0;
                        earlier_location = location;
                        location = 6;
                        break;
                    case 3:
                        directory = L"Statistics";
                        selected = 0;
                        earlier_location = location;
                        location = 2;
                        break;
                    case 4:
                        directory = L"";
                        selected = 0;
                        location = 1;
                        break;
                }
                break;

            case 4:       //========= STATISTICS > GLOBAL STATISTICS > NUMBER OF AIRPORTS ==========//
                switch (selected) {
                    case 0:
                        directory = L"Statistics > Global Statistics";
                        selected = 0;
                        location = 3;
                        break;
                    case 1:
                        directory = L"";
                        selected = 0;
                        location = 1;
                        break;
                }
                break;

            case 5:       //========= STATISTICS > GLOBAL STATISTICS > NUMBER OF AVAILABLE FLIGHTS ==========//
                switch (selected) {
                    case 0:
                        directory = L"Statistics > Global Statistics";
                        selected = 0;
                        location = 3;
                        break;
                    case 1:
                        directory = L"";
                        selected = 0;
                        location = 1;
                        break;
                }
                break;

            case 6:       //========= STATISTICS > GLOBAL STATISTICS > TRIP(S) WITH THE MOST NUMBER OF STOPS ==========//
                switch (selected) {
                    case 0:
                        directory = L"Statistics > Global Statistics";
                        selected = 0;
                        location = 3;
                        break;
                    case 1:
                        directory = L"";
                        selected = 0;
                        location = 1;
                        break;
                }
                break;

            case 7:       //========= STATISTICS > GLOBAL STATISTICS > CHOOSE AN AIRPORT ==========//
                switch (table_mode) {
                    case false:
                        switch (selected) {
                            case 1:
                                directory = L"Statistics";
                                selected = 0;
                                location = 2;
                                break;
                            case 2:
                                directory = L"";
                                selected = 0;
                                location = 1;
                                break;
                        }
                        break;
                    case true:
                        airport_analised = filteredWstringVector[page * elements_per_page + selected_in_page];
                        directory = L"Statistics > Airport " + airport_analised;
                        write = write_default;
                        selected_in_page = 0;
                        selected = 0;
                        page = 0;
                        table_mode = !table_mode;
                        earlier_location = location;
                        location = 8;
                        filteredWstringVector = airportCodeVector;
                        break;
                }
                break;

            case 8:        //========= STATISTICS > AIRPORT (X) ==========//
                switch (selected) {
                    case 0:
                        directory = L"Statistics > Airport " + airport_analised + L" > More Info on This Airport";
                        earlier_location = location;
                        location = 11;
                        selected = 0;
                        break;
                    case 1:
                        directory = L"Statistics > Airport " + airport_analised + L" > Number of Flights Out of this Airport";
                        earlier_location = location;
                        location = 9;
                        selected = 0;
                        break;
                    case 2:
                        directory = L"Statistics > Airport " + airport_analised + L" > Number of Different Airlines Out of this Airport";
                        earlier_location = location;
                        location = 10;
                        selected = 0;
                        break;
                    case 3:
                        directory = L"Statistics > Airport " + airport_analised + L" > Number of Destinations Available";
                        earlier_location = location;
                        location = 12;
                        selected = 0;
                        break;
                    case 4:
                        directory = L"Statistics > Airport " + airport_analised + L" > Number of Destinations Available in a Certain Number of Stops";
                        earlier_location = location;
                        location = 16;
                        selected = 0;
                        break;
                    case 5:
                        if (earlier_location < 15){
                            directory = L"Statistics > Choose an Airport";
                            earlier_location = location;
                            location = 7;
                        }
                        selected = 0;
                        break;
                    case 6:
                        directory = L"";
                        selected = 0;
                        location = 1;
                        break;
                }
                break;

            case 9:
            case 10:
            case 11:
                switch (selected) {
                    case 0:
                        directory = L"Statistics > Airport " + airport_analised;
                        selected = 0;
                        location = 8;
                        break;
                    case 1:
                        directory = L"";
                        selected = 0;
                        location = 1;
                        break;
                }
                break;

            case 12:
                switch (selected) {
                    case 0:
                        directory = L"Statistics > Airport " + airport_analised + L" > Number of Airport Destinations Available";
                        earlier_location = location;
                        location = 13;
                        selected = 0;
                        break;
                    case 1:
                        directory = L"Statistics > Airport " + airport_analised + L" > Number of City Destinations Available";
                        earlier_location = location;
                        location = 14;
                        selected = 0;
                        break;
                    case 2:
                        directory = L"Statistics > Airport " + airport_analised + L" > Number of Country Destinations Available";
                        earlier_location = location;
                        location = 15;
                        selected = 0;
                        break;
                    case 3:
                        directory = L"Statistics > Airport " + airport_analised;
                        selected = 0;
                        location = 8;
                        break;
                    case 4:
                        directory = L"";
                        selected = 0;
                        location = 1;
                        break;
                }
                break;

            case 13:
            case 14:
            case 15:
                switch (selected) {
                    case 0:
                        directory = L"Statistics > Airport " + airport_analised + L" > Number of Destinations Available";
                        selected = 0;
                        location = 12;
                        break;
                    case 1:
                        directory = L"";
                        selected = 0;
                        location = 1;
                        break;
                }
                break;

            case 16:
                switch (selected) {
                    case 0:
                        directory = L"Statistics > Airport " + airport_analised + L" > Number of Airport Destinations Available With Stops";
                        earlier_location = location;
                        location = 17;
                        selected = 0;
                        break;
                    case 1:
                        directory = L"Statistics > Airport " + airport_analised + L" > Number of City Destinations Available With Stops";
                        earlier_location = location;
                        location = 18;
                        selected = 0;
                        break;
                    case 2:
                        directory = L"Statistics > Airport " + airport_analised + L" > Number of Country Destinations Available With Stops";
                        earlier_location = location;
                        location = 19;
                        selected = 0;
                        break;
                    case 3:
                        directory = L"Statistics > Airport " + airport_analised;
                        selected = 0;
                        location = 8;
                        break;
                    case 4:
                        directory = L"";
                        selected = 0;
                        location = 1;
                        break;
                }
                break;

            case 17:
            case 18:
            case 19:
                switch (selected) {
                    case 1:
                        directory = L"Statistics > Airport " + airport_analised + L" > Number of Destinations Available With Steps";
                        selected = 0;
                        location = 16;
                        break;
                    case 2:
                        directory = L"";
                        selected = 0;
                        location = 1;
                        break;
                }
                break;

            case 20:       //========= STATISTICS > GLOBAL STATISTICS > CHOOSE AN AIRPORT ==========//
                switch (table_mode) {
                    case false:
                        switch (selected) {
                            case 1:
                                directory = L"Statistics";
                                selected = 0;
                                location = 2;
                                break;
                            case 2:
                                directory = L"";
                                selected = 0;
                                location = 1;
                                break;
                        }
                        break;
                    case true:
                        city_analised = filteredWstringVector[page * elements_per_page + selected_in_page];
                        directory = L"Statistics > " + city_analised + L" City";
                        write = write_default;
                        selected_in_page = 0;
                        selected = 0;
                        page = 0;
                        table_mode = !table_mode;
                        earlier_location = location;
                        location = 21;
                        filteredWstringVector = citiesVector;
                        break;
                }
                break;

            case 21:
                switch (selected) {
                    case 0:
                        directory = L"Statistics > " + city_analised + L" City > Number of Flights in this City";
                        earlier_location = location;
                        location = 22;
                        selected = 0;
                        break;
                    case 1:
                        directory = L"Statistics > " + city_analised + L" City > Number of Different Countries this City Flies to";
                        earlier_location = location;
                        location = 23;
                        selected = 0;
                        break;
                    case 2:
                        directory = L"Statistics > Choose a City";
                        selected = 0;
                        location = 20;
                        break;
                    case 3:
                        directory = L"";
                        selected = 0;
                        location = 1;
                        break;
                }
                break;

            case 22:
            case 23:
                switch (selected) {
                    case 0:
                        directory = L"Statistics > " + city_analised + L" City";
                        selected = 0;
                        location = 21;
                        break;
                    case 1:
                        directory = L"";
                        selected = 0;
                        location = 1;
                        break;
                }
                break;

            case 24:
                switch (table_mode){
                    case false:
                        switch (selected) {
                            case 1:
                                directory = L"Statistics";
                                selected = 0;
                                location = 2;
                                break;
                            case 2:
                                directory = L"";
                                selected = 0;
                                location = 1;
                                break;
                        }
                        break;
                    case true:
                        airline_analised = filteredWstringVector[page * elements_per_page + selected_in_page];
                        directory = L"Statistics > " + airline_analised + L" Airline";
                        write = write_default;
                        selected_in_page = 0;
                        selected = 0;
                        page = 0;
                        table_mode = !table_mode;
                        earlier_location = location;
                        location = 25;
                        filteredWstringVector = airlineCodeVector;
                        break;
                }
                break;

            case 25:
                switch (selected) {
                    case 0:
                        directory = L"Statistics > " + airline_analised + L" Airline > More Info on this Airline";
                        earlier_location = location;
                        location = 26;
                        selected = 0;
                        break;
                    case 1:
                        directory = L"Statistics > " + airline_analised + L" Airline > Number of Flights of this Airline";
                        earlier_location = location;
                        location = 27;
                        selected = 0;
                        break;
                    case 2:
                        directory = L"Statistics > Choose an Airline";
                        selected = 0;
                        location = 24;
                        break;
                    case 3:
                        directory = L"";
                        selected = 0;
                        location = 1;
                        break;
                }
                break;

            case 26:
            case 27:
                switch (selected) {
                    case 0:
                        directory = L"Statistics > " + airline_analised + L" Airline";
                        selected = 0;
                        location = 25;
                        break;
                    case 1:
                        directory = L"";
                        selected = 0;
                        location = 1;
                        break;
                }
                break;
        }
    }
}


void Interface::inputResponseInWriteMode(wchar_t user_in){
    if (locationOfNumWrite[location]){
        if(isdigit(user_in)){
            if (num_write == num_write_default){
                num_write = L"";
            }
            num_write += user_in;
        }
        if (user_in == 8 || user_in == 127) {
            if (!num_write.empty()) {
                num_write.pop_back();
            }
        }
        if (num_write.empty()){
            num_write = num_write_default;
        }
        if (num_write.size() > capOfWrite[location]) {
            num_write.pop_back();
        }
    }
    else{
        if (isalpha(user_in) || isalnum(user_in) || (user_in >= 128 && user_in <= 255) || (ispunct(user_in))) {
            if (write == write_default) {
                write = L"";
            }
            write += user_in;
        }
        if (user_in == 32 && write != write_default) {
            write += L" ";
        }
        if ((user_in == 8 || user_in == 127) && write != write_default) {
            if (!write.empty()) {
                write.pop_back();
            }
        }
        if (write.empty()) {
            write = write_default;
        }
        if (write.size() > capOfWrite[location] && write != write_default) {
            write.pop_back();
        }
        if (locationOfAirportSearch[location]){
            filteredWstringVector = filterSearch(airportCodeVector);
            page = 0;
        }
        if (locationOfCitySearch[location]){
            filteredWstringVector = filterSearch(citiesVector);
            page = 0;
        }
        if (locationOfAirlineSearch[location]){
            filteredWstringVector = filterSearch(airlineCodeVector);
            page = 0;
        }
    }
}


void Interface::inputer(){
    user_input = getwchar();
    if (!write_mode) {
        if (user_input == 27) {
            user_input = getwchar();
            user_input = getwchar();
        }
        basicInputResponse(user_input);
    }
    else{
        if (user_input == 27){
            user_input = getwchar();
            user_input = getwchar();
            write_mode = false;
            basicInputResponse(user_input);
        }
        else if ((user_input == '\n' || user_input == '\t')){
            write_mode = false;
            table_mode = true;
        }
        else{
            inputResponseInWriteMode(user_input);
        }
    }
}


void Interface::run(){
    setlocale(LC_CTYPE, "en_US.UTF-8"); // enconding to UTF-8 for extended characters such as "ç"

    struct termios oldt{}, newt{};
    tcgetattr(STDIN_FILENO, &oldt); // Get the current terminal settings

    newt = oldt; // Copy the current settings to the new settings

    newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode (line buffering) and echoing

    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Set the new settings

    while(location != -1){

        system("clear");
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

        switch (location){
            case 0:       //============================= LOADING SCREEN ===============================//

                appThread = std::thread([this](){
                    app = std::make_shared<Application>();
                    airportsVector = app->getAirports();
                    getAirportCodes(airportsVector);
                    alphabeticSortVector(airportCodeVector);
                    getCities();
                    alphabeticSortVector(citiesVector);
                    airlineVector = app->getAirlines();
                    getAirlineCodes(airlineVector);
                    alphabeticSortVector(airlineCodeVector);
                    is_done = true;
                });

                while(!is_done){
                    printAnimatedAirplane(airplaneLoadingScreen, 100);
                    printTextLoadingData();
                    printMaximizeWarning();
                }
                is_done = false;
                appThread.join();

                location = 1;
                break;

            case 1:       //============================= MAIN MENU ===============================//

                printBoldTitle(tripInator);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                inputer();
                break;

            case 2:       //============================= STATISTICS ===============================//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                inputer();
                break;

            case 3:       //==================== STATISTICS > GLOBAL STATISTICS ====================//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                inputer();
                break;

            case 4:       //========= STATISTICS > GLOBAL STATISTICS > NUMBER OF AIRPORTS ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                printMonoinformation(L"There are " + bold + std::to_wstring(app->getAirportCount()) + end_effect + L" Airports");
                inputer();
                break;

            case 5:       //========= STATISTICS > GLOBAL STATISTICS > NUMBER OF AVAILABLE FLIGHTS ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                printMonoinformation(L"There are " + bold + std::to_wstring(app->getFlightCount()) + end_effect + L" Flights");
                inputer();
                break;

            case 6:       //========= STATISTICS > GLOBAL STATISTICS > TRIP(S) WITH THE MOST NUMBER OF STOPS ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                printGlobalStatisticsFurthestPathsInformation(furthest_trips);
                inputer();
                break;

            case 7:       //========= STATISTICS > CHOOSE AN AIRPORT ==========//
                printDirectory(directory);
                writeOptionDefaulterAirport();
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0, 1, 2});
                printTableAirportCode(filteredWstringVector, page, elements_per_page, selected_in_page, table_mode);
                inputer();
                break;

            case 8:       //========= STATISTICS > AIRPORT (X) ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                inputer();
                break;

            case 9:       //========= STATISTICS > AIRPORT X > NUMBER OF FLIGHTS OUT ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                printMonoinformation(L"There are " + bold + std::to_wstring(app->flightsOutboundOfAirport(std::string(airport_analised.begin(), airport_analised.end()))) + end_effect + L" Flights out of this Airport");
                inputer();
                break;

            case 10:       //========= STATISTICS > AIRPORT X > NUMBER OF AIRLINES OUT ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                printMonoinformation(L"There are " + bold + std::to_wstring(app->airlinesOutboundOfAirport(std::string(airport_analised.begin(), airport_analised.end()))) + end_effect + L" Airlines out of this Airport");
                inputer();
                break;

            case 11:       //========= STATISTICS > AIRPORT X > MORE INFO ==========//
                airport_analised_object = app->getAirport(std::string(airport_analised.begin(), airport_analised.end()));
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                printMonoinformation(L"The " + bold + airport_analised + end_effect + L" airport is named " + airport_analised_object.getWname() +
                L" and is located in " + airport_analised_object.getWcity() + L", " + airport_analised_object.getWcountry());
                printMonoinformation(L"Its coordinates are " + bold + airport_analised_object.getWlatitude() + L", " + airport_analised_object.getWlongitude() + end_effect);
                inputer();
                break;

            case 12:       //========= STATISTICS > AIRPORT X > NUMBER OF DESTINATIONS AVAILABLE ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                inputer();
                break;

            case 13:       //========= STATISTICS > AIRPORT X > NUMBER OF AIRPORT DESTINATIONS AVAILABLE ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                printMonoinformation(L"There are " + bold +
                std::to_wstring(app->numberOfAirportsFromAirport(std::string(airport_analised.begin(), airport_analised.end())))
                + end_effect + L" airports reachable from this Airport");
                inputer();
                break;

            case 14:       //========= STATISTICS > AIRPORT X > NUMBER OF CITY DESTINATIONS AVAILABLE ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                printMonoinformation(L"There are " + bold +
                                     std::to_wstring(app->numberOfCitiesFromAirport(std::string(airport_analised.begin(), airport_analised.end())))
                                     + end_effect + L" cities reachable from this Airport");
                inputer();
                break;

            case 15:       //========= STATISTICS > AIRPORT X > NUMBER OF COUNTRY DESTINATIONS AVAILABLE ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                printMonoinformation(L"There are " + bold +
                                     std::to_wstring(app->numberOfDifferentCountriesAirportFliesTo(std::string(airport_analised.begin(), airport_analised.end())))
                                     + end_effect + L" countries reachable from this Airport");
                inputer();
                break;

            case 16:       //========= STATISTICS > AIRPORT X > NUMBER OF DESTINATIONS AVAILABLE WITH STEPS ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                inputer();
                break;

            case 17:      //========= STATISTICS > AIRPORT X > NUMBER OF AIRPORT DESTINATIONS AVAILABLE WITH STEPS ==========//
                printDirectory(directory);
                numeralWriteOptionsDefaulter();
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                printMonoinformation(L"There are " + bold +
                                     std::to_wstring(app->numberOfAirportsFromAirportWithStops(std::string(airport_analised.begin(), airport_analised.end()), std::stoi(num_write)))
                                     + end_effect + L" airports reachable from this Airport in within " + num_write + L" stops");
                inputer();
                break;

            case 18:       //========= STATISTICS > AIRPORT X > NUMBER OF CITY DESTINATIONS AVAILABLE WITH STEPS ==========//
                printDirectory(directory);
                numeralWriteOptionsDefaulter();
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                printMonoinformation(L"There are " + bold +
                                     std::to_wstring(app->numberOfCitiesFromAirportWithStops(std::string(airport_analised.begin(), airport_analised.end()), std::stoi(num_write)))
                                     + end_effect + L" cities reachable from this Airport in within " + num_write + L" stops");
                inputer();
                break;

            case 19:       //========= STATISTICS > AIRPORT X > NUMBER OF COUNTRY DESTINATIONS AVAILABLE WITH STEPS ==========//
                printDirectory(directory);
                numeralWriteOptionsDefaulter();
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                printMonoinformation(L"There are " + bold +
                                     std::to_wstring(app->numberOfCountriesFromAirportWithStops(std::string(airport_analised.begin(), airport_analised.end()), std::stoi(num_write)))
                                     + end_effect + L" countries reachable from this Airport in within " + num_write + L" stops");
                inputer();
                break;

            case 20:       //========= STATISTICS > CHOOSE A CITY ==========//
                printDirectory(directory);
                writeOptionDefaulterCity();
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0, 1, 2});
                printTableAirportCode(filteredWstringVector, page, elements_per_page, selected_in_page, table_mode);
                inputer();
                break;

            case 21:       //========= STATISTICS > X CITY ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers,{0});
                inputer();
                break;

            case 22:      //========= STATISTICS > X CITY > NUMBER OF FLIGHTS IN THIS CITY ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                printMonoinformation(L"There are " + bold +
                std::to_wstring(app->totalFlightsPerCity(std::string(city_analised.begin(), city_analised.end()))) +
                end_effect + L" total flights in this city, where " +
                std::to_wstring(app->inboundFlightsPerCity(std::string(city_analised.begin(), city_analised.end()))) +
                L" are inside the city boundaries and " +
                std::to_wstring(app->outboundFlightsPerCity(std::string(city_analised.begin(), city_analised.end()))) +
                L" go outside the city boundaries");
                inputer();
                break;

            case 23:      //========= STATISTICS > X CITY > NUMBER OF DIFFERENT COUNTRIES THIS CITY FLIES TO ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                printMonoinformation(L"This city flies to " + bold +
                                     std::to_wstring(app->numberOfDifferentCountriesCityFliesTo(std::string(city_analised.begin(), city_analised.end()))) +
                                     end_effect + L" different countries");
                inputer();
                break;

            case 24:      //========= STATISTICS > CHOOSE AN AIRLINE ==========//
                printDirectory(directory);
                writeOptionDefaulterAirline();
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0, 1, 2});
                printTableAirportCode(filteredWstringVector, page, elements_per_page, selected_in_page, table_mode);
                inputer();
                break;

            case 25:      //========= STATISTICS > X AIRLINE ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                inputer();
                break;

            case 26:
                airline_analised_object = app->getAirline(converter.to_bytes(airline_analised));
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printMonoinformation(L"The " + bold + airline_analised + end_effect + L" Airline is called " +
                airline_analised_object.getWname() + L", and it's callsign is " + airline_analised_object.getWcallsign());
                printMonoinformation(L"This airline is from " + bold + airline_analised_object.getWcountry() + end_effect);
                printHelper(helpers, {0});
                inputer();
                break;

            case 27:
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printMonoinformation(L"This airline has " + bold + std::to_wstring(app->flightsPerAirline(std::string(
                        airline_analised.begin(), airport_analised.end())))
                         + end_effect + L" flights");
                printHelper(helpers, {0});
                inputer();
                break;
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); //restore old terminal

    system("clear");
}