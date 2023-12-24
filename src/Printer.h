//
// Created by master on 24-12-2023.
//

#ifndef AED_PROJ_2_PRINTER_H
#define AED_PROJ_2_PRINTER_H

#endif //AED_PROJ_2_PRINTER_H

#include <iostream>
#include <vector>
#include "Util.h"

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

std::vector<std::vector<std::wstring>> loadingDataAnimation = {
        {
                L"█   ████  ██  ███  ███ ██  █ ███ ████    ███   ██  ███  ██              ",
                L"█   █  █ █__█ █  █  █  █ █ █  █  █  _    █  █ █__█  █  █__█   █         ",
                L"███ ████ █  █ ███  ███ █  ██ ███ ████    ███  █  █  █  █  █      █  █  █",
        },
        {
                L"█   ████  ██  ███  ███ ██  █ ███ ████    ███   ██  ███  ██              ",
                L"█   █  █ █__█ █  █  █  █ █ █  █  █  _    █  █ █__█  █  █__█      █       ",
                L"███ ████ █  █ ███  ███ █  ██ ███ ████    ███  █  █  █  █  █   █     █  █",
        },
        {
                L"█   ████  ██  ███  ███ ██  █ ███ ████    ███   ██  ███  ██              ",
                L"█   █  █ █__█ █  █  █  █ █ █  █  █  _    █  █ █__█  █  █__█         █   ",
                L"███ ████ █  █ ███  ███ █  ██ ███ ████    ███  █  █  █  █  █   █  █     █",
        },
        {
                L"█   ████  ██  ███  ███ ██  █ ███ ████    ███   ██  ███  ██              ",
                L"█   █  █ █__█ █  █  █  █ █ █  █  █  _    █  █ █__█  █  █__█            █",
                L"███ ████ █  █ ███  ███ █  ██ ███ ████    ███  █  █  █  █  █   █  █  █   ",
        },
        {
                L"█   ████  ██  ███  ███ ██  █ ███ ████    ███   ██  ███  ██              ",
                L"█   █  █ █__█ █  █  █  █ █ █  █  █  _    █  █ █__█  █  █__█             ",
                L"███ ████ █  █ ███  ███ █  ██ ███ ████    ███  █  █  █  █  █   █  █  █  █",
        },
        {
                L"█   ████  ██  ███  ███ ██  █ ███ ████    ███   ██  ███  ██              ",
                L"█   █  █ █__█ █  █  █  █ █ █  █  █  _    █  █ █__█  █  █__█             ",
                L"███ ████ █  █ ███  ███ █  ██ ███ ████    ███  █  █  █  █  █   █  █  █  █",
        },
        {
                L"█   ████  ██  ███  ███ ██  █ ███ ████    ███   ██  ███  ██              ",
                L"█   █  █ █__█ █  █  █  █ █ █  █  █  _    █  █ █__█  █  █__█             ",
                L"███ ████ █  █ ███  ███ █  ██ ███ ████    ███  █  █  █  █  █   █  █  █  █",
        },
        {
                L"█   ████  ██  ███  ███ ██  █ ███ ████    ███   ██  ███  ██              ",
                L"█   █  █ █__█ █  █  █  █ █ █  █  █  _    █  █ █__█  █  █__█             ",
                L"███ ████ █  █ ███  ███ █  ██ ███ ████    ███  █  █  █  █  █   █  █  █  █",
        }
};

int space_size_for_animation = 0;

int space_size_increaser = 8;

int frame = 0;

void printAnimatedAirplane(const std::vector<std::wstring>& draw, int sleep){
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
    system("clear");
    for (const std::wstring& title_segment : draw){
        if (getTerminalWidth() - space_size_for_animation + draw[0].size() <= draw[0].size()) {
            std::wcout << wstring(space_size_for_animation - draw[0].size(), L' ');
            std::wcout << bold << title_segment.substr(0, getTerminalWidth() + draw[0].size() - space_size_for_animation)
            << end_effect << std::endl;
        }
        else if (draw[0].size() >= space_size_for_animation){
            std::wcout << bold
            << title_segment.substr(draw[0].size() - space_size_for_animation - 1, space_size_for_animation)
            << end_effect << std::endl;
        }
        else{
            std::wcout << wstring(space_size_for_animation - draw[0].size(), L' ');
            std::wcout << bold << title_segment << end_effect << std::endl;
        }
    }
    space_size_for_animation += space_size_increaser;
    if (space_size_for_animation >= getTerminalWidth() + draw[0].size()){
        space_size_for_animation = 0;
    }
}


void printBoldTitle(const std::vector<std::wstring>& title){
    for (const std::wstring& title_segment : title){
        std::wcout << bold << title_segment << end_effect << std::endl;
    }
}

void printTitle(const std::vector<std::wstring>& title, size_t spaces = 0){
    for (const std::wstring& title_segment : title){
        std::wcout << wstring(spaces, L' ');
        std::wcout << bold << title_segment << end_effect << std::endl;
    }
}

void printTextLoadingData(){
    std::wcout << L"\n\n\n" << std::endl;
    printTitle(loadingDataAnimation[frame], getTerminalWidth()/2 - loadingDataAnimation[0][0].size() / 2);
    frame ++;
    if (frame > loadingDataAnimation.size() - 1){frame = 0;}
}

void printOptions(const std::vector<std::wstring>& options, unsigned long selected){
    for(const std::wstring& s : options){
        if (s == options[selected]){
            std::wcout << "< " << underline << bold << red << s << end_effect << L" >" << std::endl << L"\n";
        }
        else{
            std::wcout << bold << L"  " << s << end_effect << std::endl << L"\n";
        }
    }
}

void printHelper(std::vector<std::wstring> helpers, const std::vector<int>& selections){
    std::wcout << L"\n" << std::endl;
    for (int selection : selections){
        std::wcout << italic << helpers[selection] << end_italic << std::endl;
    }
}
