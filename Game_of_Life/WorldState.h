/*
 * WorldState.h
 *
 * Header of the WorldState class. A WorldState is responsible for storing the
 * list of live cells at a specific generation. It has a dynamic array of cells
 * cellsDA that contains the live cells in generation age.
 *
 * It has an add method that allows for adding a cell to the worldstate if the
 * cell is alive in that generation. The methods of the class also allow for
 * returning the list of cells or a cell at a given position.
 *
 * The WorldState is a set of live cells, so repeats are not allowed.
 *
 * Alexandru C. Ungureanu
 * April 27th, 2016
 */


#ifndef WORLDSTATE_H
#define WORLDSTATE_H

#include <iostream>
using namespace std;
#include "Cell.h"
#include "Point.h"
#include "Cell_Dynamic_Array.h"

class WorldState {
public:
    // constructor with no arguments
    WorldState();
    // constructor with the generation as an argument
    WorldState(int generation);
    // constructor that allows for initialization of a WorldState with a given
    // list of live cells and generation
    WorldState(Cell alive_cells[], int generation, Cell sentinel);
    ~WorldState();  // destructor
    WorldState operator =(const WorldState &source);   // assignment overload

    Cell *get_cells();   // returns the array of live cells in the WorldState
    Cell cell_at_index(int i);   // returns the cell at a specified position
    Point *get_cells_coordinates(); // returns the array of cell positions
    int get_age();  // returns the generation (age) of the WorldState
    void destroy();   // empties the worldstate (the dynamic array of cells)
    int get_number_of_cells();   // returns the number of live cells in this age
    bool add(Cell cell);   // adds a new live cell to the WorldState of this age

private:
    Cell_Dynamic_Array cellsDA;   // the dynamic array that stores the cells
    int age;   // the generation of the WorldState

    bool is_in(Cell cell);   // checks if a given cell is part of the worldstate
};


#endif // WORLDSTATE_H
