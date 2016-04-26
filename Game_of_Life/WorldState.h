#ifndef WORLDSTATE_H
#define WORLDSTATE_H

#include <iostream>
using namespace std;
#include "Cell.h"
#include "Point.h"
#include "Cell_Dynamic_Array.h"

class WorldState {
public:
    WorldState();
    WorldState(int generation);
    WorldState(Cell alive_cells[], int generation, Cell sentinel);
    ~WorldState();
    WorldState operator =(const WorldState &source);

    Cell *get_cells();
    Cell cell_at_index(int i);
    Point *get_cells_coordinates();
    int get_age();
    void destroy();
    int get_number_of_cells();
    bool add(Cell cell);

private:
    Cell_Dynamic_Array cellsDA;
    int age;

    bool is_in(Cell cell);
};


#endif // WORLDSTATE_H
