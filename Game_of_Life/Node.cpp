#include "Node.h"
#include <iostream>
using namespace std;

Node::Node()
{
    size = 0;
    nw = NULL;
    sw = NULL;
    ne = NULL;
    se = NULL;
}

Node::Node(int node_size, int top_left_coord, int bot_right_coord)
{
    size = node_size;
    nw = NULL;
    sw = NULL;
    ne = NULL;
    se = NULL;
    top_left.set(top_left_coord);
    bot_right.set(bot_right_coord);
    if (node_size == 1) {
        cell = Cell(top_left);
    }
}


Point Node::get_top_left()
{
    return top_left;
}

Point Node::get_bot_right()
{
    return bot_right;
}

Node *Node::get_region(Region reg)
{
    if (reg == NORTH_WEST) {
        return nw;
    }

    else if (reg == SOUTH_WEST) {
        return sw;
    }

    else if (reg == NORTH_EAST) {
        return ne;
    }

    else {
        return se;
    }
}

int Node::get_size()
{
    return size;
}


void Node::set_region(Region reg, Node *n)
{
    if (reg == NORTH_WEST) {
        nw = n;
    }

    else if (reg == SOUTH_WEST) {
        sw = n;
    }

    else if (reg == NORTH_EAST) {
        ne = n;
    }

    else {
        se = n;
    }
}

bool Node::is_leaf()
{
    if (size == 1) {
        return true;
    }

    return false;
}

Region *Node::get_available_regions()
{
    static Region regions[4] = {};
    int pos = 0;
    if (nw != NULL) {
        regions[pos] = NORTH_WEST;
        pos++;
    }
    if (sw != NULL) {
        regions[pos] = SOUTH_WEST;
        pos++;
    }
    if (ne != NULL) {
        regions[pos] = NORTH_EAST;
        pos++;
    }
    if (se != NULL) {
        regions[pos] = SOUTH_EAST;
        pos++;
    }
    return regions;
}

Cell Node::get_cell()
{
    if (size == 1) {
        return cell;
    }
    else {
        throw "The node is not a leaf(cell)!";
    }
}

Region Node::get_region_for_point(Point p)
{
    if (p.get_x() <= middle(x) and p.get_y() <= middle_y()) {
        return SOUTH_WEST;
    }
    else if (p.get_x() <= middle(x)) {
        return NORTH_WEST;
    }
    else if (p.get_y() <= middle_y()) {
        return SOUTH_EAST;
    }
    else {
        return NORTH_EAST;
    }
}

int Node::middle_x()
{
    return (top_left.get_x() + bot_right.get_x()) / 2;
}

int Node::middle_y()
{
    return (top_left.get_y() + bot_right.get_y()) / 2;
}
