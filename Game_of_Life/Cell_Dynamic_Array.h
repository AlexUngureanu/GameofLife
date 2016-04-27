/*
 * Cell_Dynamic_Array.h
 *
 * A dynamic array of live cells, that grows as needed. The Cell_Dynamic_Array
 * class's methods allow for insertion and deletion of cells, as well as for
 * returning all or single cells and verifying if a cell is already in the
 * array.
 *
 * The dynamic array has a capacity and a size (cellsNumber). Once the size
 * becomes equal to the capacity, the array expands to provide enough space for
 * other cells to be inserted.
 *
 * Alexandru C. Ungureanu
 * April 27th, 2016
 */



#ifndef CELL_DYNAMIC_ARRAY_H
#define CELL_DYNAMIC_ARRAY_H

#include "Cell.h"

class Cell_Dynamic_Array {
public:
    // constructor and destructor of the class
    Cell_Dynamic_Array();
    ~Cell_Dynamic_Array();

    // assignment overload of the class
    Cell_Dynamic_Array operator =(const Cell_Dynamic_Array &source);

    // adds a cell to the array
    void add(Cell c);

    // removes a cell from the array, if it is in
    bool remove(Cell c);

    // returns the number of cells in the array
    int get_number_of_cells();

    // returns the array of cells currently inside the dynamic array
    Cell *get_list();

    // returns the cell at the specified index in the list
    Cell get_cell_at_index(int index);

    // checks if a specified cell is in the array
    bool is_in(Cell c);

    // frees the space allocated for the array (empties it)
    void destroy();

    // checks if the array is empty
    bool is_empty();

private:
    static const int INITIAL_CAPACITY = 10;   // the initial capacity
    int capacity;   // the current capacity
    int cellsNumber;   // the number of cells in the array
    Cell *cells;   // pointer to the first element in the array

    void expand();   // allows for the expansion of the array
};


#endif // CELL_DYNAMIC_ARRAY_H
