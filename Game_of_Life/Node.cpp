/*
 * Node.cpp
 *
 * Source file for the Node class
 *
 * Alexandru C. Ungureanu
 * April 27th, 2016
 */
#include "Node.h"

#include <iostream>
#include <cassert>
using namespace std;

// no-arguments constructor; the default (uninitialized) size of a node is 0
Node::Node()
{
    size = 0;
    nw = NULL;
    sw = NULL;
    ne = NULL;
    se = NULL;
}

// constructor that sets the size and corners of the board to the given
// parameters; the children are initialized as NULL pointers (currently empty)
Node::Node(int node_size, Point top_left_coord, Point bot_right_coord)
{
    size = node_size;
    nw = NULL;
    sw = NULL;
    ne = NULL;
    se = NULL;
    // set the top-left and bottom-right corners to the given points
    top_left.set(top_left_coord);
    bot_right.set(bot_right_coord);
}

/*
 * returns the point that corresponds to the top-left corner of the node
 */
Point Node::get_top_left()
{
    return top_left;
}

/*
 * returns the point that corresponds to the bottom-right corner of the node
 */
Point Node::get_bot_right()
{
    return bot_right;
}

/*
 * returns a pointer to the children associated with the given parameter (enum)
 */
Node *Node::get_region(Region reg)
{
    if (reg == NORTH_WEST) {
        return nw;
    }
    if (reg == NORTH_EAST) {
        return ne;
    }
    if (reg == SOUTH_WEST) {
        return sw;
    }
    if (reg == SOUTH_EAST) {
        return se;
    }
}

/*
 * returns the side length of the square board associated with the node
 */
int Node::get_size()
{
    return size;
}

/*
 * sets the region (child) associated with the specified identifier to point
 * to node n, given as a parameter
 */
void Node::set_region(Region reg, Node *n)
{
    if (reg == NORTH_WEST) {
        nw = n;
    }
    if (reg == NORTH_EAST) {
        ne = n;
    }
    if (reg == SOUTH_WEST) {
        sw = n;
    }
    if(reg == SOUTH_EAST) {
        se = n;
    }
}

/*
 * returns true of the node is a leaf or false if it is not a leaf
 */
bool Node::is_leaf()
{
    // the node is a leaf when the side length of the board is 1 (a point)
    if (size == 1) {
        return true;
    }

    return false;
}

/*
 * returns the cell associated with the node if the node is a leaf
 */
Cell Node::get_cell()
{
    if (size == 1) {
        return cell;
    }
    else {
        // throw exception if the node is not a leaf
        throw "The node is not a leaf(cell)!";
    }
}

/*
 * returns the child (region) where point p, given as a parameter, is situated,
 * or NONE if the point is not inside the square board associated with the node
 */
Region Node::get_region_for_point(Point p)
{
    // the corners of the northwest region are the top-left corner of the node
    // and the middle point (center of the board)
    if (p.get_x() <= middle_x() && p.get_y() <= middle_y() && p.get_x() >=
            top_left.get_x() && p.get_y() >= top_left.get_y()) {
        return NORTH_WEST;
    }

    // the corners of the southwest region are the middle of the left side of
    // the board and the middle of the bottom side of the board
    else if (p.get_x() <= middle_x() && p.get_y() > middle_y() && p.get_x()
             >= top_left.get_x() && p.get_y() <= bot_right.get_y()) {
        return SOUTH_WEST;
    }

    // the corners of the northeast region are the middle of the top side of the
    // board and the middle of the right side of the board
    else if (p.get_x() > middle_x() && p.get_x() <= bot_right.get_x() &&
             p.get_y() <= middle_y() && p.get_y() >= top_left.get_y()) {
        return NORTH_EAST;
    }

    // the corners of the southeast region are the middle point (center of the
    // board) and the bottom-right corner of the board
    else if (p.get_x() > middle_x() && p.get_x() <= bot_right.get_x() &&
             p.get_y() > middle_y() && p.get_y() <= bot_right.get_y()) {
        return SOUTH_EAST;
    }

    else {
        // if the given point is not in any of the regions, return NONE
        return NONE;
    }
}

/*
 * returns the x-coordinate of the middle of the board
 */
int Node::middle_x()
{
    return (top_left.get_x() + bot_right.get_x()) / 2;
}

/*
 * returns the y-coordinate of the middle of the board
 */
int Node::middle_y()
{
    return (top_left.get_y() + bot_right.get_y()) / 2;
}

/*
 * sets the cell associated with the node to be the given cell c (parameter)
 */
void Node::set_cell(Cell c)
{
    cell = c;
}

/*
 * returns the top-left corner of the specified region
 */
Point Node::get_top_left_region(Region region)
{
    Point p;
    if (region == NORTH_WEST) {
        // top-left corner of northwest region is the top-left corner of the
        // node
        p.set(top_left);
    }
    else if (region == SOUTH_WEST) {
        // top-left corner of the southwest region is the middle of the left
        // side of the board
        p.set_x(top_left.get_x());
        p.set_y((top_left.get_y() + bot_right.get_y() - 1) / 2);
    }
    else if (region == NORTH_EAST) {
        // top-left corner of the northeast region is the middle of the top side
        // of the board
        p.set_x((top_left.get_x() + bot_right.get_x() + 1) / 2);
        p.set_y(top_left.get_y());
    }
    else if (region == SOUTH_EAST) {
        // top-left corner of the southeast region is the center of the board
        p.set_x((top_left.get_x() + bot_right.get_x() + 1) / 2);
        p.set_y((top_left.get_y() + bot_right.get_y() - 1) / 2);
    }
    return p;
}

/*
 * returns the bottom-right corner for the specified region of the node
 */
Point Node::get_bot_right_region(Region region)
{
    Point p;
    if (region == NORTH_WEST) {
        // bottom-right corner of the northwest region is the center of the
        // board
        p.set_x((top_left.get_x() + bot_right.get_x() - 1) / 2);
        p.set_y((top_left.get_y() + bot_right.get_y() + 1) / 2);
    }
    else if (region == SOUTH_WEST) {
        // bottom-right corner of the southwest region is the middle of the
        // bottom side of the board
        p.set_x((top_left.get_x() + bot_right.get_x() - 1) / 2);
        p.set_y(bot_right.get_y());
    }
    else if (region == NORTH_EAST) {
        // bottom-right corner of the northeast region is the middle of the
        // right side of the board
        p.set_x(bot_right.get_x());
        p.set_y((top_left.get_y() + bot_right.get_y() + 1) / 2);
    }
    else if (region == SOUTH_EAST){
        // bottom-right corner of the southeast region is the bottom-right
        // corner of the board
        p.set(bot_right);
    }
    return p;
}

