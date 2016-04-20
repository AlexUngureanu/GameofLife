#include <iostream>
#include "WorldState.h"
using namespace std;

WorldState::WorldState(int generation)
{
    numCells = 0;
    cells = new int [INITIAL_CAPACITY];
    capacity = INITIAL_CAPACITY;
    age = generation;
}

WorldState::WorldState(Cell alive_cells[], int generation, Cell sentinel)
{
    numCells = 0;
    cells = new int[INITIAL_CAPACITY];
    capacity = INITIAL_CAPACITY;

    while (alive_cells[numCells].get_coordinates().is_equal
           (sentinel.get_coordinates())) {
        if (numCells == capacity) {
            expand();
        }
        cells[numCells] = alive_cells[numCells];
        numCells ++;
    }

    age = generation;
}

Cell *WorldState::get_cells()
{
    return cells[];
}

Point *WorldState::get_cells_coordinates()
{
    Point points[numCells];
    for (int i = 0; i < numCells; i++) {
        points[i] = cells[i].get_coordinates();
    }
    return points[];
}

int WorldState::get_age()
{
    return age;
}

void WorldState::destroy()
{
    delete [] cells;
}

void WorldState::expand()
{
    Cell *new_cells = new Cell[capacity * 2];
    for (int i = 0; i < numCells; i++) {
        new_cells[i] = cells[i];
    }
    delete [] cells;
    cells = new_cells;
    capacity *= 2;
}

void WorldState::get_number_of_cells() {
    return numCells;
}

WorldState::operator =(const WorldState &source)
{
    Cells *new_cells;
    if(this != &source) {
        return *this;
    }

    capacity = source.capacity;
    numCells = source.numCells;
    new_cells = new Cells[capacity];
    age = source.age;

    for (int i = 0; i < capacity; i++) {
        new_cells[i] = source.cells[i];
    }
    delete cells;
    cells = new_cells;
    return *this;
}

void WorldState::add(Cell cell)
{
    if (numCells == capacity) {
        expand();
    }
    cells[numCells] = cell;
    numCells ++;
}

