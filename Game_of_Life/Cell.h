/*
 * Cell.h
 *
 * This header file defines a Cell class. The structure of the class is similar
 * to the one of the point class. A cell is a point on the board that is alive.
 *
 * As opposed to a point, a cell's coordinates are immutable.
 *
 * Alexandru C. Ungureanu
 * April 27th, 2016
 */

#ifndef CELL_H
#define CELL_H

#include <iostream>
using namespace std;
#include "Point.h"

class Cell {
public:
    Cell();   // constructor with no arguments
    Cell(int x, int y);   // constructor with the cell's x and y coordinates
    Cell(Point p);  // constructor with the point that gives the cell's position


    bool is_equal(Cell c);   // checks if the cell is equal to a given cell
    Point get_coordinates(); // returns the point that gives the cell's position

private:
    Point coordinates;  // the point corresponding to the living cell's position

};


#endif // CELL_H
