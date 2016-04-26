#include <iostream>
#include "WorldState.h"
using namespace std;

WorldState::WorldState()
{

}

WorldState::WorldState(int generation)
{
    age = generation;
}

WorldState::WorldState(Cell alive_cells[], int generation, Cell sentinel)
{
    int numCells = 0;

    while (!alive_cells[numCells].get_coordinates().is_equal
           (sentinel.get_coordinates())) {
        cellsDA.add(alive_cells[numCells]);
        numCells++;
    }

    age = generation;
}

WorldState::~WorldState()
{

}

Cell *WorldState::get_cells()
{
    return cellsDA.get_list();
}

//Point *WorldState::get_cells_coordinates()
//{
//    Point points[numCells];
//    for (int i = 0; i < numCells; i++) {
//        points[i] = cells[i].get_coordinates();
//    }
//    return points;
//}

int WorldState::get_age()
{
    return age;
}

void WorldState::destroy()
{
    cellsDA.destroy();
}

int WorldState::get_number_of_cells()
{
    return cellsDA.get_number_of_cells();
}

WorldState WorldState::operator =(const WorldState &source)
{
    if(this != &source) {
        return *this;
    }

    age = source.age;
    destroy();

    cellsDA = source.cellsDA;

    return *this;
}

bool WorldState::add(Cell cell)
{
    if (is_in(cell)) {
        return false;
    }
    cellsDA.add(cell);
    return true;
}

bool WorldState::is_in(Cell cell)
{
    if (cellsDA.is_in(cell)) {
        return true;
    }
    else {
        return false;
    }
}

Cell WorldState::cell_at_index(int i)
{
    return cellsDA.get_cell_at_index(i);
}
