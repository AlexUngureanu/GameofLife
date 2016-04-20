#include <iostream>
#include "GoL_Controller.h"
using namespace std;

GoL_Controller::GoL_Controller(int squareLength)
{
    root(squareLength);
}

GoL_Controller::GoL_Controller(int squareLength, int population_size)
{
    root(squareLength, population_size);
}

GoL_Controller::GoL_Controller(int squareLength, Cell cells[])
{
    root(squareLength);
    WorldState state(cells, 0);
    current_world_state = state;
}

void GoL_Controller::destroy_current_tree()
{
    post_order_delete(root);
}

void GoL_Controller::post_order_delete(Node *node)
{
    if(node->get_region(NORTH_WEST) != NULL) {
        post_order_delete(node->get_region(NORTH_WEST));
    }
    if(node->get_region(SOUTH_WEST) != NULL) {
        post_order_delete(node->get_region(SOUTH_WEST));
    }
    if(node->get_region(NORTH_EAST) != NULL) {
        post_order_delete(node->get_region(NORTH_EAST));
    }
    if(node->get_region(SOUTH_EAST) != NULL) {
        post_order_delete(node->get_region(SOUTH_EAST));
    }
    delete node;
}

WorldState GoL_Controller::get_next_world_state()
{
    compute_next_generation(current_world_state.get_cells(),
                            current_world_state.get_number_of_cells());
    age ++;
    current_world_state.destroy();
    current_world_state = get_world_state_tree(next_root);
    destroy_current_tree();
    root = next_root;
    next_root = NULL;
    return current_world_state;
}

WorldState GoL_Controller::get_world_state()
{
    return current_world_state;
}

void GoL_Controller::compute_next_generation(Cell cells[], int numCells)
{
    for (int i = 0; i < numCells; i++) {
        compute_next_generation_state(cells[i]);
    }
}
