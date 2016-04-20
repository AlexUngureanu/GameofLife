#include <iostream>
#include "Cell.h"
using namespace std;

Cell::Cell()
{
    state = dead;
    numNeighbors = 0;
    coordinates.set_x(-1);
    coordinates.set_y(-1);
}

Cell::Cell(int x, int y)
{
    state = dead;
    numNeighbors = 0;
    coordinates.set_x(x);
    coordinates.set_y(y);
}

Cell::Cell(Point p)
{
    state = dead;
    numNeighbors = 0;
    coordinates.set(p);
}

void Cell::set_alive()
{
    state = alive;
}

void Cell::set_dead()
{
    state = dead;
}


bool Cell::is_alive()
{
    return (state == alive);
}

Point Cell::get_coordinates()
{
    return coordinates;
}

void Cell::update_generation()
{
    generation ++;
}

void Cell::set_generation(int age)
{
    generation = age;
}
