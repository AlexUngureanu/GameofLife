#include <iostream>
#include "Point.h"
using namespace std;

Point::Point()
{
    x = -1;
    y = -1;
}

Point::Point(int x_coord, int y_coord)
{
    x = x_coord;
    y = y_coord;
}

int Point::get_x()
{
    return x;
}

int Point::get_y()
{
    return y;
}

void Point::set_x(int x_coord)
{
    x = x_coord;
}

void Point::set_y(int y_coord)
{
    y = y_coord;
}

bool Point::is_equal(Point p)
{
    if (x == p.get_x() && y == p.get_y()) {
        return true;
    }

    return false;
}

void Point::set(Point p)
{
    x = p.get_x();
    y= p.get_y();
}


