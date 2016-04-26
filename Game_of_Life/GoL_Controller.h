#ifndef GOL_CONTROLLER_H
#define GOL_CONTROLLER_H

#include <iostream>
using namespace std;
#include "Node.h"
#include "WorldState.h"
#include "Cell.h"
#include "Point.h"

enum State { alive, dead };

class GoL_Controller {
public:
    GoL_Controller();

    ~GoL_Controller();

    void reset_world_random(int squareLength, int percentage);

    WorldState &get_world_state();
    void next_world_state();
    void destroy_current_tree();
    void destroy_world_state();

private:
    Node *root;
    Node *next_root;
    WorldState current_world_state;
    int age;
    int size;

    void compute_next_generation(Cell cells[], int numCells);
    void update_world_state(Node *node);
    void build_tree_map(Cell cells[], int population);
    void compute_next_generation_state(Cell cell, State state);
    void post_order_delete(Node *node);
    void insert_cell(Cell cell, Node *node);
    void random_generate_specified_population(int population);
    bool is_cell_in_tree(Cell cell, Node *node);
};

#endif // GOL_CONTROLLER_H
