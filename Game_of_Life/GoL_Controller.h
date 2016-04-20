#ifndef GOL_CONTROLLER_H
#define GOL_CONTROLLER_H

#include <iostream>
using namespace std;
#include "Node.h"
#include "WorldState.h"
#include "Cell.h"
#include "Point.h"

class GoL_Controller {
public:
    GoL_Controller(int squareLength);
    GoL_Controller(int squareLength, int percentage);
    GoL_Controller(int squareLength, Cell cells[]);
    ~GoL_Controller();

    void reset_world();
    void reset_world(Cell cells[]);
    void reset_with_random_population();
    void reset_with_new_size(int squareLength);

    WorldState get_world_state();
    WorldState get_next_world_state();
    void destroy_current_tree();

private:
    Node *root;
    Node *next_root;
    WorldState current_world_state;
    int age;

    void compute_next_generation(Cell cells[], int numCells);
    WorldState get_world_state_tree(Node *node);
    void get_tree_map(Cell cells[]);
    void compute_next_generation_state(Cell cell);
    void post_order_delete(Node *node);
    bool insert(Node *parent, Node *node);
    bool insert_cell(Point p);
};


#endif // GOL_CONTROLLER_H
