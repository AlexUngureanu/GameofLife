#ifndef CELL_DYNAMIC_ARRAY_H
#define CELL_DYNAMIC_ARRAY_H

#include "Cell.h"

class Cell_Dynamic_Array {
public:
    Cell_Dynamic_Array();
    ~Cell_Dynamic_Array();
    Cell_Dynamic_Array operator =(const Cell_Dynamic_Array &source);

    void add(Cell c);
    bool remove(Cell c);
    int get_number_of_cells();
    Cell *get_list();
    Cell get_cell_at_index(int index);
    bool is_in(Cell c);
    void destroy();
    bool is_empty();

private:
    static const int INITIAL_CAPACITY = 10;
    int capacity;
    int cellsNumber;
    Cell *cells;

    void expand();
};


#endif // CELL_DYNAMIC_ARRAY_H
