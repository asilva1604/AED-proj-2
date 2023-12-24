//
// Created by master on 24-12-2023.
//

#ifndef AED_PROJ_2_UTIL_H
#define AED_PROJ_2_UTIL_H

#endif //AED_PROJ_2_UTIL_H

#include <iostream>
#include <sys/ioctl.h>
#include <cstdio>
#include <unistd.h>

int getTerminalWidth() {
    struct winsize w{};
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}
