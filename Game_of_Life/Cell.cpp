/*
 * Cell.cpp
 *
 * Source file for the Cell class
 *
 * Alexandru C. Ungureanu
 * April 27th, 2016
 */

#include <iostream>
#include "Cell.h"
using namespace std;

/*
 * constructor with no arguments; sets the cell's location to point (-1, 1)
 */
Cell::Cell()
{
    coordinates.set_x(-1);
    coordinates.set_y(-1);
}

/*
 * constructor with arguments x and y, that give the horizontal and vertical
 * coordinates of the cell
 */
Cell::Cell(int x, int y)
{
    coordinates.set_x(x);
    coordinates.set_y(y);
}

/*
 * constructor with argument p, the point that gives the cell's location
 */
Cell::Cell(Point p)
{
    coordinates.set(p);
}

/*
 * returns the point that gives the location of the cell
 */
Point Cell::get_coordinates()
{
    return coordinates;
}

/*
 * returns true if the cell is the same as the given cell (parameter c) or false
 * if not
 */
bool Cell::is_equal(Cell c)
{
    // two live cells are the same if they have the same board location (point)
    if (coordinates.is_equal(c.get_coordinates())) {
        return true;
    }
    return false;
}
