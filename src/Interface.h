//
// Created by master on 23-12-2023.
//

#ifndef AED_PROJ_2_INTERFACE_H
#define AED_PROJ_2_INTERFACE_H

#endif //AED_PROJ_2_INTERFACE_H

#include <iostream>
#include <codecvt>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <locale>
#include <thread>
#include "Application.h"


//----------------------------------------- Class Stuff ------------------------------------------------------//
class Interface {
public:
    explicit Interface();

    void run();


private:
    //----------------- COLOR SCHEMES --------------------//
    std::wstring bg_light_red = L"\x1b[101m";
    std::wstring end_bg = L"\x1b[0m";
    std::wstring italic = L"\x1b[3m";
    std::wstring end_italic = L"\x1b[0m";
    std::wstring red = L"\033[31m";
    std::wstring bold = L"\033[1m";
    std::wstring underline = L"\033[4m";;
    std::wstring end = L"\033[0m";
    //----------------------------------------------------//

    std::shared_ptr<Application> app;

    int location = 0;
    int earlier_location = 0;

    unsigned int user_input;

    unsigned long selected = 0;

    bool is_done = false;
    bool write_mode = false;

    std::thread appThread;

    std::wstring directory;

    std::vector<std::vector<std::wstring>> options{
            {
                L""
            },
            {
                L"Flights",
                L"Statistics",
                L"Quit"
            },
            {
                L"Global Statistics",
                L"Choose an Airport",
                L"Choose a City",
                L"Main Menu"
            },
            {
                L"Number of Airports",
                L"Number of Available Flights",
                L"Back",
                L"Main Menu"
            },
            {
                L"Back",
                L"Main Menu"
            },
            {
                L"Back",
                L"Main Menu"
            },
    };

    std::vector<std::wstring> helpers{
            L"  You can use 'up arrow', 'down arrow', and 'ENTER' to select the options"
    };

    std::vector<std::wstring> tripInator = {
            L"  ---------------------------------------------------------------------------------------------------------- ",
            L" |        ████████ █████  ██████ █████         ██████ ███    ██   ████  ████████  ████   █████              |",
            L" |           ██    █    █   ██   █    █          ██   ██ █   ██  █    █    ██    █    █  █    █             |",
            L" |           ██    █████    ██   █████   ████    ██   ██  █  ██  ██████    ██   █      █ █████              |",
            L" |           ██    █   █    ██   █               ██   ██   █ ██ █      █   ██    █    █  █   █              |",
            L" |           ██    █    █ ██████ █             ██████ ██    ███ █      █   ██     ████   █    █   3000      |",
            L"  ---------------------------------------------------------------------------------------------------------- ",
            L"\n"
    };

    std::vector<std::wstring> airplaneLoadingScreen = {
            L"   __  _                             ",
            L"  \\ `/ |                            ",
            L"   \\__`|                            ",
            L"    / ,' `-.__________________       ",
            L"    '-'\\_____                LI`-.  ",
            L"        <____()-=O=O=O=O=O=[]====--) ",
            L"          `.___ ,-----,_______...-'  ",
            L"               /    .'               ",
            L"              /   .'                 ",
            L"             /  .'                   ",
            L"             `-'                     "
    };

    //================================================== FUNCTIONS =========================================//

    void inputer();

    void basicInputResponse(unsigned int user_in);
};