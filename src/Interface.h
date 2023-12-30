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
    std::wstring end_effect = L"\033[0m";
    //----------------------------------------------------//

    std::shared_ptr<Application> app;

    int location = 0;
    int earlier_location = 0;
    int elements_per_page = 10;
    int page = 0;

    unsigned int user_input;

    unsigned long selected = 0;
    unsigned long selected_in_page = 0;

    bool is_done = false;
    bool write_mode = false;
    bool table_mode = false;

    std::thread appThread;

    std::wstring directory;
    std::wstring write;
    std::wstring write_default =  italic + L"  You can write here  " + end_italic;
    std::wstring num_write = L"0";
    std::wstring num_write_default = L"0";
    std::wstring airport_analised;
    std::wstring city_analised;
    std::wstring airline_analised;

    Airport airport_analised_object;
    Airline airline_analised_object;

    std::vector<std::pair<std::pair<Airport, Airport>, int>> furthest_trips;

    std::vector<int> capOfWrite =              {0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 30, 0, 0, 0, 3};
    std::vector<int> locationOfAirportSearch = {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 00, 0, 0, 0, 0};
    std::vector<int> locationHasTable =        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 01, 0, 0, 0, 1};
    std::vector<int> locationOfNumWrite =      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 00, 0, 0, 0, 0};
    std::vector<int> locationOfCitySearch =    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 01, 0, 0, 0, 0};
    std::vector<int> locationOfAirlineSearch = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 00, 0, 0, 0, 1};


    std::vector<Airport> airportsVector;
    std::vector<Airline> airlineVector;
    std::vector<std::wstring> airportCodeVector;
    std::vector<std::wstring> airlineCodeVector;
    std::vector<std::wstring> citiesVector;
    std::vector<std::wstring> filteredWstringVector;



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
                L"Choose an Airline",
                L"Main Menu"
            },
            {
                L"Number of Airports",
                L"Number of Available Flights",
                L"Trip(s) with the Most Number of Stops",
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
            {
                L"Back",
                L"Main Menu"
            },
            {
                L"Search for an Airport code",
                L"Back",
                L"Main Menu"
            },
            {
                L"More Info on This Airport",
                L"Number of Flights Out of this Airport",
                L"Number of Different Airlines Out of this Airport",
                L"Number of Destinations Available",
                L"Number of Destinations Available in a Certain Number Of Stops",
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
            {
                L"Back",
                L"Main Menu"
            },
            {
                L"Number of Airports Available",
                L"Number of Cities Available",
                L"Number of Countries Available",
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
            {
                L"Back",
                L"Main Menu"
            },
            {
                L"Number of Airports Available With Stops",
                L"Number of Cities Available With Stops",
                L"Number of Countries Available With Stops",
                L"Back",
                L"Main Menu"
            },
            {
                L"Number of Stops: " + bold + num_write + end_effect,
                L"Back",
                L"Main Menu"
            },
            {
                L"Number of Stops: " + bold + num_write + end_effect,
                L"Back",
                L"Main Menu"
            },
            {
                L"Number of Stops: " + bold + num_write + end_effect,
                L"Back",
                L"Main Menu"
            },
            {
                L"Search for a City Name",
                L"Back",
                L"Main Menu"
            },
            {
                L"Number of Flights in this City",
                L"Number of Different Countries this City Flies to",
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
            {
                L"Search for an Airline code",
                L"Back",
                L"Main Menu"
            },
            {
                L"More Info on this Airline",
                L"Number of Flights of this Airline",
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
            L"  You can use 'up arrow', 'down arrow', and 'ENTER' to select the options",
            L"  You can use 'tab' to change to the Airport codes table, and 'ENTER' to select one",
            L"  You can use 'n' and 'p' to go to the next and previous page of the table respectively"
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

    void writeOptionDefaulterAirport();

    void inputResponseInWriteMode(wchar_t user_in);

    static wstring smooth_string(const wstring &w);

    vector<wstring> filterSearch(const vector<std::wstring> &wstrings);

    static void alphabeticSortVector(vector<std::wstring> &wstr);

    void getAirportCodes(const vector<Airport>& airports);

    void numeralWriteOptionsDefaulter();

    void getCities();

    void writeOptionDefaulterCity();

    void getAirlineCodes(const vector<Airline> &airlines);

    void writeOptionDefaulterAirline();
};