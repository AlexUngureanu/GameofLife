#include <iostream>
#include "Cell.h"
using namespace std;

Cell::Cell()
{
    coordinates.set_x(-1);
    coordinates.set_y(-1);
}

Cell::Cell(int x, int y)
{
    coordinates.set_x(x);
    coordinates.set_y(y);
}

Cell::Cell(Point p)
{
    coordinates.set(p);
}

Point Cell::get_coordinates()
{
    return coordinates;
}

bool Cell::is_equal(Cell c)
{
    if (coordinates.is_equal(c.get_coordinates())) {
        return true;
    }
    return false;
}
