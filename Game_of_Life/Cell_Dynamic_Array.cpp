#include "Cell_Dynamic_Array.h"


Cell_Dynamic_Array::Cell_Dynamic_Array()
{
    capacity = INITIAL_CAPACITY;
    cellsNumber = 0;
    cells = new Cell[capacity];
}

Cell_Dynamic_Array::~Cell_Dynamic_Array()
{
    //delete [] cells;
}

Cell_Dynamic_Array Cell_Dynamic_Array::operator =(const Cell_Dynamic_Array
                                                  &source)
{
    if (this == &source) {
        return *this;
    }
    Cell *new_cells;
    capacity = source.capacity;
    cellsNumber = source.cellsNumber;
    new_cells = new Cell[capacity];

    for (int i = 0; i < capacity; i++) {
        new_cells[i] = source.cells[i];
    }

    delete [] cells;
    cells = new_cells;

    return *this;
}

int Cell_Dynamic_Array::get_number_of_cells()
{
    return cellsNumber;
}

bool Cell_Dynamic_Array::remove(Cell c)
{
    for (int i = 0; i < cellsNumber; i++) {
        if (cells[i].is_equal(c)) {
            for (int j = i; j < cellsNumber - 1; j++) {
                cells[j] = cells[j + 1];
            }
            cellsNumber--;
            return true;
        }
    }
    return false;
}

void Cell_Dynamic_Array::add(Cell c)
{
    if (!is_in(c)) {
        if (cellsNumber == capacity) {
            expand();
        }

        cells[cellsNumber] = c;
        cellsNumber++;
    }
}

void Cell_Dynamic_Array::expand()
{
    Cell *new_cells = new Cell[capacity * 2];
    for (int i = 0; i < cellsNumber; i++) {
        new_cells[i] = cells[i];
    }
    delete [] cells;
    cells = new_cells;
    capacity *= 2;
}

Cell *Cell_Dynamic_Array::get_list()
{
    return cells;
}

Cell Cell_Dynamic_Array::get_cell_at_index(int index)
{
    return cells[index];
}

bool Cell_Dynamic_Array::is_in(Cell c)
{
    for (int i = 0; i < cellsNumber; i++) {
        if(cells[i].is_equal(c)) {
            return true;
        }
    }
    return false;
}

void Cell_Dynamic_Array::destroy()
{
    delete [] cells;
    capacity = INITIAL_CAPACITY;
    cellsNumber = 0;
    cells = new Cell[capacity];

}

bool Cell_Dynamic_Array::is_empty()
{
    return (cellsNumber == 0);
}
