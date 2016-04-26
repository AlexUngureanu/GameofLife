#include "Node.h"

#include <iostream>
#include <cassert>
using namespace std;

Node::Node()
{
    size = 0;
    nw = NULL;
    sw = NULL;
    ne = NULL;
    se = NULL;
}

Node::Node(int node_size, Point top_left_coord, Point bot_right_coord)
{
    size = node_size;
    nw = NULL;
    sw = NULL;
    ne = NULL;
    se = NULL;
    top_left.set(top_left_coord);
    bot_right.set(bot_right_coord);
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

int Node::get_size()
{
    return size;
}


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

bool Node::is_leaf()
{
    if (size == 1) {
        return true;
    }

    return false;
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
    if (p.get_x() <= middle_x() && p.get_y() <= middle_y() && p.get_x() >=
            top_left.get_x() && p.get_y() >= top_left.get_y()) {
        return NORTH_WEST;
    }
    else if (p.get_x() <= middle_x() && p.get_y() > middle_y() && p.get_x()
             >= top_left.get_x() && p.get_y() <= bot_right.get_y()) {
        return SOUTH_WEST;
    }
    else if (p.get_x() > middle_x() && p.get_x() <= bot_right.get_x() &&
             p.get_y() <= middle_y() && p.get_y() >= top_left.get_y()) {
        return NORTH_EAST;
    }
    else if (p.get_x() > middle_x() && p.get_x() <= bot_right.get_x() &&
             p.get_y() > middle_y() && p.get_y() <= bot_right.get_y()) {
        return SOUTH_EAST;
    }
    else {
        return NONE;
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

void Node::set_cell(Cell c)
{
    cell = c;
}

Point Node::get_top_left_region(Region region)
{
    Point p;
    if (region == NORTH_WEST) {
        p.set(top_left);
    }
    else if (region == SOUTH_WEST) {
        p.set_x(top_left.get_x());
        p.set_y((top_left.get_y() + bot_right.get_y() - 1) / 2);
    }
    else if (region == NORTH_EAST) {
        p.set_x((top_left.get_x() + bot_right.get_x() + 1) / 2);
        p.set_y(top_left.get_y());
    }
    else if (region == SOUTH_EAST) {
        p.set_x((top_left.get_x() + bot_right.get_x() + 1) / 2);
        p.set_y((top_left.get_y() + bot_right.get_y() - 1) / 2);
    }
    return p;
}

Point Node::get_bot_right_region(Region region)
{
    Point p;
    if (region == NORTH_WEST) {
        p.set_x((top_left.get_x() + bot_right.get_x() - 1) / 2);
        p.set_y((top_left.get_y() + bot_right.get_y() + 1) / 2);
    }
    else if (region == SOUTH_WEST) {
        p.set_x((top_left.get_x() + bot_right.get_x() - 1) / 2);
        p.set_y(bot_right.get_y());
    }
    else if (region == NORTH_EAST) {
        p.set_x(bot_right.get_x());
        p.set_y((top_left.get_y() + bot_right.get_y() + 1) / 2);
    }
    else if (region == SOUTH_EAST){
        p.set(bot_right);
    }
    return p;
}

