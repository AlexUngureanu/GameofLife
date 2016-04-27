#include <iostream>
#include "WorldState.h"
using namespace std;

/*
 * constructor with no arguments (nothing needed)
 */
WorldState::WorldState()
{

}

/*
 * constructor that sets the age (generation) of the worldstate
 */
WorldState::WorldState(int generation)
{
    age = generation;
}

/*
 * constructor that sets the age of the worldstate and the list of live cells
 * to be the one given in the array parameter; has a sentil parameter, a cell
 * which marks the end of the array of live cells and is not to be added to the
 * worldstate
 */
WorldState::WorldState(Cell alive_cells[], int generation, Cell sentinel)
{
    // size of the worldstate (number of cells)
    int numCells = 0;

    while (!alive_cells[numCells].get_coordinates().is_equal
           (sentinel.get_coordinates())) {
        // while sentinel (end of array) not reached, insert the current element
        // of the given array of cells in the dynamic array of the worldstate
        cellsDA.add(alive_cells[numCells]);
        numCells++;
    }

    age = generation;
}

/*
 * destructor (nothing needed)
 */
WorldState::~WorldState()
{

}

/*
 * returns the array (list) of live cells in the state of the world at this age
 */
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

/*
 * returns the age (generation) of the worldstate
 */
int WorldState::get_age()
{
    return age;
}

/*
 * empties the worldstate by freeing the space allocated for its dynamic array
 * of cells and resetting it
 */
void WorldState::destroy()
{
    cellsDA.destroy();
}

/*
 * returns the number of live cells in this worldstate
 */
int WorldState::get_number_of_cells()
{
    // the size of the worldstate is the number of cells in the array
    return cellsDA.get_number_of_cells();
}

/*
 * assignment overload needed to prevent shallow copying; a source-worldstate
 * is given as the parameter and its contents are being copied to this
 * worldstate; returns the new worldstate
 */
WorldState WorldState::operator =(const WorldState &source)
{
    // if the worldstates are the same, no copying needed
    if(this != &source) {
        return *this;
    }

    // copy the age
    age = source.age;

    // free the space allocated for the old dynamic array
    destroy();

    // update the pointer to point to the first element of the new array
    cellsDA = source.cellsDA;

    return *this;
}

/*
 * attempts to add a new cell to the worldstate and returns true if successful;
 * returns false if not successful (cell already in the worldstate)
 */
bool WorldState::add(Cell cell)
{
    // if the cell is already in the worldstate, do not add it
    if (is_in(cell)) {
        return false;
    }

    // else add it in the dynamic array of live cells
    cellsDA.add(cell);
    return true;
}

/*
 * returns true if the given cell is in the worldstate or false if not
 */
bool WorldState::is_in(Cell cell)
{
    // the cell is in the worldstate if it is in the dynamic array of cells
    if (cellsDA.is_in(cell)) {
        return true;
    }
    else {
        return false;
    }
}

/*
 * returns the cell at the specified position in the worldstate
 */
Cell WorldState::cell_at_index(int i)
{
    return cellsDA.get_cell_at_index(i);
}
