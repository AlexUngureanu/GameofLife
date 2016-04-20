#ifndef CELL_H
#define CELL_H

#include <iostream>
using namespace std;
#include "Point.h"

enum State { alive, dead };

class Cell {
public:
    Cell();
    Cell(int x, int y);
    Cell(Point p);

    void set_alive();
    void set_dead();
    void update_generation();
    void set_generation();

    bool is_alive();

    Point get_coordinates();

private:
    State state;
    Point coordinates;
    int generation;

};

#endif // CELL_H
