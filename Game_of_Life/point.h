#ifndef POINT_H
#define POINT_H

#include <iostream>
using namespace std;

class Point {
public:
    Point();
    Point(int x_coord, int y_coord);

    int get_x();
    int get_y();
    void set_x(int x_coord);
    void set_y(int y_coord);
    void set(Point p);
    bool is_equal(Point p);

private:
    int x;
    int y;
};

#endif // POINT_H
