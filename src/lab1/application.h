#ifndef A_DS_APPLICATION_H
#define A_DS_APPLICATION_H

#include <iostream>
#include <ctime>
#include <fstream>
#include "list.h"
#include "array.h"
#include "station.h"



class application {
public:
    void showMenu();

    void interactionMenu();

    void editMenu();

    void fillMenu();

    void arrayApplication();

    void listApplication();

    void stationApplication();
};



#endif