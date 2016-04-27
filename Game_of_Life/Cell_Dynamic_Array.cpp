/*
 * Cell_Dynamic_Array.cpp
 *
 * Source file for the Cell_Dynamic_Array class
 *
 * Alexandru C. Ungureanu
 * April 27th, 2016
 */


#include "Cell_Dynamic_Array.h"

/*
 * constructor of the class that sets the initial capacity
 */
Cell_Dynamic_Array::Cell_Dynamic_Array()
{
    capacity = INITIAL_CAPACITY;
    cellsNumber = 0;   // empty array at first
    cells = new Cell[capacity];   // allocates space for the array
}

/*
 * destructor
 */
Cell_Dynamic_Array::~Cell_Dynamic_Array()
{
    //delete [] cells;
}

/*
 * assignment overload needed to allow for copying the contents of another
 * specified source-dynamic array, without keeping the duplicates (to avoid
 * issues like double - deallocation of the same memory location)
 * returns the new dynamic array
 */
Cell_Dynamic_Array Cell_Dynamic_Array::operator =(const Cell_Dynamic_Array
                                                  &source)
{
    // no copying is needed if the arrays are the same
    if (this == &source) {
        return *this;
    }

    Cell *new_cells;

    // copies the capacity and size of the given dynamic array
    capacity = source.capacity;
    cellsNumber = source.cellsNumber;
    new_cells = new Cell[capacity];

    // copies the contents of the given source-dynamic array in the new array
    for (int i = 0; i < capacity; i++) {
        new_cells[i] = source.cells[i];
    }

    // frees the space allocated for the old array and updates it to point to
    // the first element of the new one
    delete [] cells;
    cells = new_cells;

    return *this;
}

/*
 * returns the current number of cells (size) of the dynamic array
 */
int Cell_Dynamic_Array::get_number_of_cells()
{
    return cellsNumber;
}

/*
 * attempts to remove the given cell c (parameter) from the dynamic array and
 * returns true if successful or false if not
 */
bool Cell_Dynamic_Array::remove(Cell c)
{
    for (int i = 0; i < cellsNumber; i++) {
        if (cells[i].is_equal(c)) {
            // if cell is in the array, move all the elements positioned after
            // the cell by 1 position to the left to remove the given cell
            for (int j = i; j < cellsNumber - 1; j++) {
                cells[j] = cells[j + 1];
            }
            // the size of the array decreases by 1
            cellsNumber--;
            return true;
        }
    }
    // if cell is not in the array, return false
    return false;
}

/*
 * adds the given cell c (parameter) at the end of the array
 */
void Cell_Dynamic_Array::add(Cell c)
{
    if (!is_in(c)) {
        // if maximum capacity is reached, expand the array
        if (cellsNumber == capacity) {
            expand();
        }
        // add the cell after the last cell of the array and update the size
        cells[cellsNumber] = c;
        cellsNumber++;
    }
}

/*
 * expands the array by doubling its capacity
 */
void Cell_Dynamic_Array::expand()
{
    // create a new array with double capacity
    Cell *new_cells = new Cell[capacity * 2];
    // copy the elements from the old array to the new one
    for (int i = 0; i < cellsNumber; i++) {
        new_cells[i] = cells[i];
    }
    // free the space allocated for the old array
    delete [] cells;
    // update the pointer to point to the first element of the new array
    cells = new_cells;
    // update the capacity of the array (double)
    capacity *= 2;
}

/*
 * returns the array of cells (pointer to the first element)
 */
Cell *Cell_Dynamic_Array::get_list()
{
    return cells;
}

/*
 * returns the cell positioned at the given index
 */
Cell Cell_Dynamic_Array::get_cell_at_index(int index)
{
    return cells[index];
}

/*
 * returns true if the cell given as a parameter is in the array or false if not
 */
bool Cell_Dynamic_Array::is_in(Cell c)
{
    // loop through and check if any of the cells is the same as the given cell
    for (int i = 0; i < cellsNumber; i++) {
        if(cells[i].is_equal(c)) {
            // return true if cell is found
            return true;
        }
    }
    // return false if cell is not found
    return false;
}

/*
 * frees the space allocated for the array and allocates space for a new array
 * of size 0 (empty) and initial capacity
 */
void Cell_Dynamic_Array::destroy()
{
    delete [] cells;
    capacity = INITIAL_CAPACITY;
    cellsNumber = 0;
    cells = new Cell[capacity];

}

/*
 * returns true if the array is empty (size is 0) or false if not
 */
bool Cell_Dynamic_Array::is_empty()
{
    return (cellsNumber == 0);
}
