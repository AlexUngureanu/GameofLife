/*
 * Point.cpp
 *
 * Source file for the Point class
 *
 * Alexandru C. Ungureanu
 * April 27th, 2016
 */


#include <iostream>
#include "Point.h"
using namespace std;

/*
 * constructor with no arguments that sets the point to (-1, 1)
 */
Point::Point()
{
    x = -1;
    y = -1;
}

/*
 * constructor that sets the points coordinates to the given parameters,
 * x_coord and y_coord
 */
Point::Point(int x_coord, int y_coord)
{
    x = x_coord;
    y = y_coord;
}

/*
 * returns the x-coordinate of the point
 */
int Point::get_x()
{
    return x;
}

/*
 * returns the y-coordinate of the point
 */
int Point::get_y()
{
    return y;
}

/*
 * sets the x-coordinate to the given coordinate, x_coord
 */
void Point::set_x(int x_coord)
{
    x = x_coord;
}

/*
 * sets the y-coordinate to the given coordinate, y_coord
 */
void Point::set_y(int y_coord)
{
    y = y_coord;
}

/*
 * returns true if the point is the same as the given point (parameter p) or
 * false if the two points are not the same
 */
bool Point::is_equal(Point p)
{
    // check if both the horizontal and vertical coordinates are equal to see if
    // the points are the same
    if (x == p.get_x() && y == p.get_y()) {
        return true;
    }

    return false;
}

/*
 * sets the point to point p, given as a paremeter
 */
void Point::set(Point p)
{
    // sets the coordinates of the point to the coordinates of the given point
    x = p.get_x();
    y= p.get_y();
}


