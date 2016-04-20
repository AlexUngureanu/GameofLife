#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <stdexcept>
#include <map>
using namespace std;

#include "Point.h"
#include "Cell.h"


enum Region { NORTH_WEST, NORTH_EAST, SOUTH_WEST, SOUTH_EAST };

class Node {
public:
    Node();
    Node(int node_size, int top_left_coord, int bot_right_coord);
    Point get_top_left();
    Point get_bot_right();
    Node *get_region(Region reg);
    int get_size();
    Region *get_available_regions();
    Region get_region_for_point(Point p);

    void set_region(Region reg, Node *n);
    bool is_leaf();
    Cell get_cell();
    int middle_x();
    int middle_y();



private:
    Point top_left;
    Point bot_right;
    int size;
    Node *nw;
    Node *sw;
    Node *ne;
    Node *se;
    Cell cell;

};


#endif // NODE_H
