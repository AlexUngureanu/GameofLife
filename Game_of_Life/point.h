/*
 * Point.h
 *
 * This header file defines a Point class.
 *
 * A point in the universe has two integer coordinates: x (horizontal), and y
 * (vertical). The coordinates of a point are mutable.
 *
 * Alexandru C. Ungureanu
 * April 27th, 2016
 */



#ifndef POINT_H
#define POINT_H

#include <iostream>
using namespace std;

class Point {
public:
    Point();   // constructor with no arguments
    Point(int x_coord, int y_coord);   // constructor with coordinates

    int get_x();   // returns the x-coordinate of the point
    int get_y();   // returns the y-coordinate of the point
    void set_x(int x_coord);   // sets the x-coordinate of the point
    void set_y(int y_coord);   // sets the y-coordinate of the point
    void set(Point p);   // copies the contents of a given point to this point
    bool is_equal(Point p);   // checks if the point is the same as a given one

private:
    int x;   // the x-coordinate
    int y;   // the y-coordinate
};

#endif // POINT_H
