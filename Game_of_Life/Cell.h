#ifndef CELL_H
#define CELL_H

#include <iostream>
using namespace std;
#include "Point.h"

class Cell {
public:
    Cell();
    Cell(int x, int y);
    Cell(Point p);


    bool is_equal(Cell c);
    Point get_coordinates();

private:
    Point coordinates;

};


#endif // CELL_H
