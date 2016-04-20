#ifndef WORLDSTATE_H
#define WORLDSTATE_H

#include <iostream>
using namespace std;
#include "Cell.h"
#include "Point.h"

class WorldState {
public:
    WorldState(int generation);
    WorldState(Cell alive_cells[], int generation);
    operator=(const Worldstate &source);

    Cell *get_cells();
    Point *get_cells_coordinates();
    int get_age();
    void destroy();
    void get_number_of_cells();
    void add(Cell cell);

private:
    Cell *cells;
    int numCells;
    int age;
    void expand();
    static const int INITIAL_CAPACITY = 10;
    int capacity;

};

#endif // WORLDSTATE_H
