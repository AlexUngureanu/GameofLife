/*
 * Node.h
 *
 * Header of the Node class. A node is a square board with 2^k X 2^k size.
 * It allows for the organization of the game board as a QuadTree of square
 * boards. A QuadTree is a tree in which each node has four children. The
 * children of a node (square board) are the four regions (square boards) of the
 * node: the northwest, southwest, northeast and southeast regions. The root of
 * the Quadtree is the game board. The leaves of the Quadtree are 1 X 1 boards
 * (points) of the game board.
 *
 * A node has four children: nw, sw, ne, se (the 4 regions). It has two points
 * that set the position limits of the board, the top-left corner, and the
 * bottom-right corner of the node.
 *
 * The methods of the class allow for the division of a node in its constituent
 * children and manipulation of those children.
 *
 * Alexandru C. Ungureanu
 * April 27th, 2016
 */

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <stdexcept>
#include <map>
using namespace std;

#include "Point.h"
#include "Cell.h"

// enum with the identifiers for the four regions of a node
enum Region { NORTH_WEST, NORTH_EAST, SOUTH_WEST, SOUTH_EAST, NONE };


class Node {
public:
    // constructors of the class, with or without arguments
    Node();
    Node(int node_size, Point top_left_coord, Point bot_right_coord);

    Point get_top_left(); // returns the position of top-left corner of the node
    Point get_bot_right(); // returns the position of bottom-right corner

    // returns the pointer to the child that corresponds to the given identifierS
    Node *get_region(Region reg);
    // returns the length of the side of the square node
    int get_size();
    // returns the identifier of the child where the given point is, or NONE if
    // the given point is node inside the current node (board)
    Region get_region_for_point(Point p);

    // return the limits (positions of corners) for the region (child) of the
    // node that corresponds to the given identifier
    Point get_top_left_region(Region region);
    Point get_bot_right_region(Region region);

    // sets the specified region to point to the given node
    void set_region(Region reg, Node *n);
    // returns true if the node is a leaf or false otherwise
    bool is_leaf();
    // returns the cell that corresponds to the node, if the node is a leaf
    Cell get_cell();
    // sets the cell for a node, if the node is a leaf
    void set_cell(Cell c);

    // return the x-coordinate or y-coordinate of the middles of the board
    int middle_x();
    int middle_y();

private:
    Point top_left; // point that gives the top-left corner of the node
    Point bot_right; // point that gives the bottom-right corner of the node
    int size;   // length of a side of the square board (node)
    Node *nw;   // northwest child
    Node *sw;   // southwest child
    Node *ne;   // northeast child
    Node *se;   // southeast child
    Cell cell;   // cell that corresponds to the node, if the node is a leaf

    // bool search_cell(Cell c, Node *n);
};


#endif // NODE_H
