//
// Created by student on 22.01.18.
//

#ifndef CHECKERSSERVER_LOGGER_H
#define CHECKERSSERVER_LOGGER_H

#include <cstdio>
#include <string>

using namespace std;

void log(string message)
{
    printf("%s", message.c_str());
    printf("\n");
    fflush(stdout);
}

#endif //CHECKERSSERVER_LOGGER_H
