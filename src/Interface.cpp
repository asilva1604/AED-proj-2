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
                    Application app;
                    is_done = true;
                });

                while(!is_done){
                    printAnimatedAirplane(airplaneLoadingScreen, 100);
                    printTextLoadingData();
                }

                location = 1;
                break;

            case 1:       //============================= MAIN MENU ===============================//

                printBoldTitle(tripInator);
                printOptions(options[location], selected);
                printHelper(helpers, {0});
                inputer();
                break;
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); //restore old terminal

    system("clear");
}