#include <iostream>
#include <cstdlib>
#include <cassert>
#include "GoL_Controller.h"
using namespace std;

GoL_Controller::GoL_Controller()
{
    size = 0;
    age = 0;
    WorldState state(0);
    current_world_state = state;
    root = NULL;
    next_root = NULL;
}


GoL_Controller::~GoL_Controller()
{
    destroy_current_tree();
}

void GoL_Controller::destroy_current_tree()
{
    if (root != NULL) {
        post_order_delete(root);
    }
}

void GoL_Controller::post_order_delete(Node *node)
{
    assert (node != NULL);
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

void GoL_Controller::reset_world_random(int squareLength, int percentage)
{
    Point top_left(0, 0);
    Point bot_right(squareLength - 1, squareLength - 1);
    root = new Node(squareLength, top_left, bot_right);
    size = squareLength;
    WorldState state(0);
    current_world_state = state;
    int area = size * size;
    int population = int((float)percentage / 100 * area);
    random_generate_specified_population(population);
    build_tree_map(current_world_state.get_cells(),
                  current_world_state.get_number_of_cells());
    next_root = new Node(squareLength, top_left, bot_right);
}

void GoL_Controller::next_world_state()
{
    compute_next_generation(current_world_state.get_cells(),
                            current_world_state.get_number_of_cells());
    age ++;
    current_world_state.destroy();
    WorldState state(age);
    current_world_state = state;
    update_world_state(next_root);
    root = next_root;
    Point top_left(0, 0);
    Point bot_right(size - 1, size - 1);
    next_root = new Node(size, top_left, bot_right);
}

WorldState &GoL_Controller::get_world_state()
{
    return current_world_state;
}

void GoL_Controller::compute_next_generation(Cell cells[], int numCells)
{
    for (int i = 0; i < numCells; i++) {
        compute_next_generation_state(cells[i], alive);
    }
}

void GoL_Controller::build_tree_map(Cell cells[], int population)
{
    for (int i = 0; i < population; i++) {
        insert_cell(cells[i], root);
    }
}

void GoL_Controller::insert_cell(Cell cell, Node *node)
{
    if (node->is_leaf() == true) {
        node->set_cell(cell);
    }
    else {
        Point coordinates = cell.get_coordinates();
        Region region = node->get_region_for_point(coordinates);
        if(node->get_region(region) == NULL) {
            Point new_top_left = node->get_top_left_region(region);
            Point new_bot_right = node->get_bot_right_region(region);
            Node *new_node = new Node(node->get_size() / 2, new_top_left,
                                      new_bot_right);
            node->set_region(region, new_node);
        }
        insert_cell(cell, node->get_region(region));
    }
}

void GoL_Controller::compute_next_generation_state(Cell cell, State state)
{
    int numNeighbors = 0;
    int x = cell.get_coordinates().get_x();
    int y = cell.get_coordinates().get_y();
    Cell nw_neighbor(x - 1, y - 1);
    Cell n_neighbor(x, y - 1);
    Cell ne_neighbor(x + 1, y - 1);
    Cell e_neighbor(x + 1, y);
    Cell se_neighbor(x + 1, y + 1);
    Cell s_neighbor(x, y + 1);
    Cell sw_neighbor(x - 1, y + 1);
    Cell w_neighbor(x - 1, y);
    if (is_cell_in_tree(nw_neighbor, root)) {
        numNeighbors ++;
    }
    if (is_cell_in_tree(n_neighbor, root)) {
        numNeighbors ++;
    }
    if (is_cell_in_tree(ne_neighbor, root)) {
        numNeighbors ++;
    }
    if (is_cell_in_tree(e_neighbor, root)) {
        numNeighbors ++;
    }
    if (is_cell_in_tree(se_neighbor, root)) {
        numNeighbors ++;
    }
    if (is_cell_in_tree(s_neighbor, root)) {
        numNeighbors ++;
    }
    if (is_cell_in_tree(sw_neighbor, root)) {
        numNeighbors ++;
    }
    if (is_cell_in_tree(w_neighbor, root)) {
        numNeighbors ++;
    }
    if (is_cell_in_tree(cell, root)) {
        if (numNeighbors == 2 || numNeighbors == 3) {
            if(!is_cell_in_tree(cell, next_root)) {
                insert_cell(cell, next_root);
            }
        }
    }
    else {
        if (numNeighbors == 3) {
            if(!is_cell_in_tree(cell, next_root)) {
                insert_cell(cell, next_root);
            }
        }
    }
    if (state == alive) {
        compute_next_generation_state(nw_neighbor, dead);
        compute_next_generation_state(n_neighbor, dead);
        compute_next_generation_state(ne_neighbor, dead);
        compute_next_generation_state(e_neighbor, dead);
        compute_next_generation_state(se_neighbor, dead);
        compute_next_generation_state(s_neighbor, dead);
        compute_next_generation_state(sw_neighbor, dead);
        compute_next_generation_state(w_neighbor, dead);
    }
}

void GoL_Controller::random_generate_specified_population(int population)
{

    int count = 0;
    while (count != population) {
        int x_coord = rand() % size;
        int y_coord = rand() % size;
        Cell living_cell(x_coord, y_coord);
        if (current_world_state.add(living_cell) == true) {
            count ++;
        }
    }
}

void GoL_Controller::update_world_state(Node *node)
{
    if (node->is_leaf()) {
        current_world_state.add(node->get_cell());
    }
    else {
        if (node->get_region(NORTH_WEST) != NULL) {
            update_world_state(node->get_region(NORTH_WEST));
        }
        if (node->get_region(SOUTH_WEST) != NULL) {
            update_world_state(node->get_region(SOUTH_WEST));
        }
        if (node->get_region(NORTH_EAST) != NULL) {
            update_world_state(node->get_region(NORTH_EAST));
        }
        if (node->get_region(SOUTH_EAST) != NULL) {
            update_world_state(node->get_region(SOUTH_EAST));
        }
    }
}

void GoL_Controller::destroy_world_state()
{
    current_world_state.destroy();
}

bool GoL_Controller::is_cell_in_tree(Cell cell, Node *node)
{
    if (node->is_leaf()) {
        if (node->get_cell().is_equal(cell)) {
            return true;
        }
    }
    Region region = node->get_region_for_point(cell.get_coordinates());
    if (region == NONE) {
        return false;
    }
    if(node->get_region(region) == NULL) {
        return false;
    }
    return is_cell_in_tree(cell, node->get_region(region));
}
