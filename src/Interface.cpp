//
// Created by master on 23-12-2023.
//

#include "Interface.h"
#include "Printer.h"

Interface::Interface()= default;


void Interface::basicInputResponse(unsigned int user_in){
    if (user_in == 'A') {
        if (selected > 0) { selected -= 1; }
        else { selected = options[location].size() - 1; }
    }
    if (user_in == 'B') {
        selected ++;
        if (selected >= options[location].size()) {selected = 0;}
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
                        earlier_location = location;
                        location = 3;
                        break;
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
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
                        directory = L"Statistics";
                        selected = 0;
                        earlier_location = location;
                        location = 2;
                        break;
                    case 3:
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

        switch (location){
            case 0:       //============================= LOADING SCREEN ===============================//

                appThread = std::thread([this](){
                    app = std::make_shared<Application>();
                    is_done = true;
                });

                while(!is_done){
                    printAnimatedAirplane(airplaneLoadingScreen, 100);
                    printTextLoadingData();
                    printMaximizeWarning();
                }

                appThread.join();

                location = 1;
                break;

            case 1:       //============================= MAIN MENU ===============================//

                printBoldTitle(tripInator);
                printOptions(options[location], selected);
                printHelper(helpers, {0});
                inputer();
                break;

            case 2:       //============================= STATISTICS ===============================//
                printDirectory(directory);
                printOptions(options[location], selected);
                printHelper(helpers, {0});
                inputer();
                break;

            case 3:       //==================== STATISTICS > GLOBAL STATISTICS ====================//
                printDirectory(directory);
                printOptions(options[location], selected);
                printHelper(helpers, {0});
                inputer();
                break;

            case 4:       //========= STATISTICS > GLOBAL STATISTICS > NUMBER OF AIRPORTS ==========//
                printDirectory(directory);
                printOptions(options[location], selected);
                printHelper(helpers, {0});
                printMonoinformation(L"There are " + bold + std::to_wstring(app->getAirportCount()) + end_effect + L" Airports");
                inputer();
                break;
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); //restore old terminal

    system("clear");
}