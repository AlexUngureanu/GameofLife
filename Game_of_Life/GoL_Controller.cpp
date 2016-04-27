/*
 * GoL_Controller.cpp
 *
 * Source file for the GoL_Controller class
 *
 * Alexandru C. Ungureanu
 * April 27th, 2016
 */
#include <iostream>
#include <cstdlib>
#include <cassert>
#include "GoL_Controller.h"
using namespace std;

/*
 * constructor of the class that creates an empty board and worldstate
 */
GoL_Controller::GoL_Controller()
{
    // board and live cells uninitialized yet
    size = 0;
    age = 0;
    WorldState state(0);
    current_world_state = state;

    // empty current and next-generation boards
    root = NULL;
    next_root = NULL;
}

/*
 * destructor that empties the current tree
 */
GoL_Controller::~GoL_Controller()
{
    destroy_current_tree();
}

/*
 * deletes the node of the current tree
 */
void GoL_Controller::destroy_current_tree()
{
    // if the board is not empty, use the helper function to delete the nodes
    // of the tree with root root
    if (root != NULL) {
        post_order_delete(root);
    }
}

/*
 * helper function that deletes the nodes of the tree with the given root (node)
 * deletion is done recursively by using a post-order traversal of the tree
 */
void GoL_Controller::post_order_delete(Node *node)
{
    assert (node != NULL);
    if(node->get_region(NORTH_WEST) != NULL) {
        // if the northwest child exists, delete the subtree that has this child
        // as its root
        post_order_delete(node->get_region(NORTH_WEST));
    }
    if(node->get_region(SOUTH_WEST) != NULL) {
        // if the southwest child exists, delete the subtree that has this child
        // as its root
        post_order_delete(node->get_region(SOUTH_WEST));
    }
    if(node->get_region(NORTH_EAST) != NULL) {
        // if the northeast child exists, delete the subtree that has this child
        // as its root
        post_order_delete(node->get_region(NORTH_EAST));
    }
    if(node->get_region(SOUTH_EAST) != NULL) {
        // if the southeast child exists, delete the subtree that has this child
        // as its root
        post_order_delete(node->get_region(SOUTH_EAST));
    }
    // once the children's subtrees are deleted, remove the node
    delete node;
}

/*
 * resets the current board to restart the game; the board will have the given
 * side-length (squareLength); initializes the worldstate of the beginning of
 * the game; the intial live cells will be randomly generated; the given
 * percentage will be the percentage of the board covered with live cells
 */
void GoL_Controller::reset_world_random(int squareLength, int percentage)
{
    // initializes the top-left and bottom-right corner of the game board
    Point top_left(0, 0);
    Point bot_right(squareLength - 1, squareLength - 1);
    // creates the root (game board) with the given side-length and corners
    root = new Node(squareLength, top_left, bot_right);
    size = squareLength;
    // creates a new empty worldstate to be initialized
    WorldState state(0);
    current_world_state = state;
    int area = size * size;
    // the initial population (number of living cells) is the given percentage
    // of the total number of possible cells of the board
    int population = int((float)percentage / 100 * area);
    // initialize the worldstate at the beginning of the game by randomly
    // generating the set of live cells
    random_generate_specified_population(population);
    // create the intial tree associated with the initial worldstate
    build_tree_map(current_world_state.get_cells(),
                  current_world_state.get_number_of_cells());
    // create the root of the tree for the next generation
    next_root = new Node(squareLength, top_left, bot_right);
}

/*
 * computes the next state of the game in the next generation by updating the
 * worldstate and the tree-game board
 */
void GoL_Controller::next_world_state()
{
    // creates the next-generation's tree from the worldstate of the current
    // generation (the list of live cells of this generation)
    compute_next_generation(current_world_state.get_cells(),
                            current_world_state.get_number_of_cells());
    // increase the "age" of the game
    age ++;
    // empties the worldstate for this generation and creates a new empty one
    // for the new age
    current_world_state.destroy();
    WorldState state(age);
    current_world_state = state;
    // creates the worldstate of the new generation from the next generation
    // board computed previously
    update_world_state(next_root);
    // updates the current tree for the current state to depict the board for
    // the next state
    root = next_root;
    // generate a new root for the next generation since the current one has
    // been updated to the following generation
    Point top_left(0, 0);
    Point bot_right(size - 1, size - 1);
    next_root = new Node(size, top_left, bot_right);
}

/*
 * returns the current worldstate of the board
 */
WorldState &GoL_Controller::get_world_state()
{
    return current_world_state;
}

/*
 * computes the next generation state of each of the cells that are alive in the
 * cuurent generation; also takes the number of live cells of the worldstate to
 * loop through the list of cells
 */
void GoL_Controller::compute_next_generation(Cell cells[], int numCells)
{
    for (int i = 0; i < numCells; i++) {
        // for each alive cell, compute the state of this cell in the next
        // generation
        compute_next_generation_state(cells[i], alive);
    }
}

/*
 * creates the tree for the current worldstate using the list of live cells
 * and the number of live cells; the tree contains only nodes that contain at
 * least a living cell on their boards
 */
void GoL_Controller::build_tree_map(Cell cells[], int population)
{
    for (int i = 0; i < population; i++) {
        // insert only the live cells in the tree for the current game board
        insert_cell(cells[i], root);
    }
}

/*
 * inserts a given live cell in the tree with the given root (node)
 */
void GoL_Controller::insert_cell(Cell cell, Node *node)
{
    if (node->is_leaf() == true) {
        // if the node is a leaf, we found the position for the cell
        node->set_cell(cell);
    }
    else {
        // get the point that gives the cell's position
        Point coordinates = cell.get_coordinates();
        // get the region where the cell should be positioned based on its
        // coordinates
        Region region = node->get_region_for_point(coordinates);
        if(node->get_region(region) == NULL) {
            // if this region (child) was not previously created, create it
            // get the top-left and bottom-right corners corresponding to
            // the region that will be created
            Point new_top_left = node->get_top_left_region(region);
            Point new_bot_right = node->get_bot_right_region(region);
            // create the new region (child)
            Node *new_node = new Node(node->get_size() / 2, new_top_left,
                                      new_bot_right);
            node->set_region(region, new_node);
        }
        // insert the cell in the corresponding region (child)
        insert_cell(cell, node->get_region(region));
    }
}

/*
 * computes the state of the cell in the next generation
 * if the cell is alive in the next generation, insert in the next-generation
 * tree; for each live cell we compute the state for, compute the state for
 * its neighbors too (they could be alive in the next generation)
 * parameters - cell, the cell we compute the next-generation's state for
 *            - state, could be either: alive (signaling we are computing
 * the next generation for a live cell in the current worldstate), or neighbor
 * (signaling we are computing the next generation for a neighbor of a live cell
 * in the current worldstate
 */
void GoL_Controller::compute_next_generation_state(Cell cell, State state)
{
    int numNeighbors = 0;   // number of living neighbors
    int x = cell.get_coordinates().get_x();
    int y = cell.get_coordinates().get_y();
    // crete the cells that correspond to the current cell's neighbors
    Cell nw_neighbor(x - 1, y - 1);
    Cell n_neighbor(x, y - 1);
    Cell ne_neighbor(x + 1, y - 1);
    Cell e_neighbor(x + 1, y);
    Cell se_neighbor(x + 1, y + 1);
    Cell s_neighbor(x, y + 1);
    Cell sw_neighbor(x - 1, y + 1);
    Cell w_neighbor(x - 1, y);
    // for each neighbor, check if it is alive; it is alive if it is in the
    // current tree of the game board (because we inserted only the living cells
    // in the current tree)
    // if the neighbor is alive, increment the number of living neighbors
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
        // if the cell is alive, it stays alive only if it has 2 or 3 live
        // neighbors; if it stays alive, insert it in the tree for the next
        // generation
        if (numNeighbors == 2 || numNeighbors == 3) {
            // if it stays alive, insert it only if it is not already in the
            // next tree
            if(!is_cell_in_tree(cell, next_root)) {
                insert_cell(cell, next_root);
            }
        }
    }
    else {
        // if the cell is not currently alive (not in the current tree), it
        // becomes a living cell in the next generation only if the number of
        // live neigbors is exactly 3
        if (numNeighbors == 3) {
            // if it becomes alive, insert it only if it is not already in the
            // next tree
            if(!is_cell_in_tree(cell, next_root)) {
                insert_cell(cell, next_root);
            }
        }
    }
    // if the current cell is part of the worldstate (it is a live cell), also
    // compute the state of its neighbors
    // if the current cell is a neighbor of a live cells, no need to compute
    // the next generation state for its neighbors; even if its neighbors should
    // be alive in the next state, they will be set alive when this method is
    // callsed for worldstate cells that have those neighbors
    if (state == alive) {
        compute_next_generation_state(nw_neighbor, neighbor);
        compute_next_generation_state(n_neighbor, neighbor);
        compute_next_generation_state(ne_neighbor, neighbor);
        compute_next_generation_state(e_neighbor, neighbor);
        compute_next_generation_state(se_neighbor, neighbor);
        compute_next_generation_state(s_neighbor, neighbor);
        compute_next_generation_state(sw_neighbor, neighbor);
        compute_next_generation_state(w_neighbor, neighbor);
    }
}

/*
 * randomly generates the live cells at the beginning of the game and creates
 * the worldstate that contains those cells
 * parameter - population, the number of living cells at the beginning of the
 * game
 */
void GoL_Controller::random_generate_specified_population(int population)
{

    int count = 0;
    // generate until the desired population is reached
    while (count != population) {
        // randomly generates the coordinates of the cell
        int x_coord = rand() % size;
        int y_coord = rand() % size;
        Cell living_cell(x_coord, y_coord);
        // if not already in the worldstate, add it and update the number of
        // live cells
        if (current_world_state.add(living_cell) == true) {
            count ++;
        }
    }
}

/*
 * adds the live cells in the given node to the worldstate
 * uses a pre-order traversal of the tree
 */
void GoL_Controller::update_world_state(Node *node)
{
    if (node->is_leaf()) {
        // if the node is a leaf, add the cell in it to the worldstate
        current_world_state.add(node->get_cell());
    }
    else {
        // else go to each of its non-empty children and recursively add the
        // live cells in these regions to the worldstate
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

/*
 * empties the current worldstate
 */
void GoL_Controller::destroy_world_state()
{
    current_world_state.destroy();
}

/*
 *  returns true if the given cell is a live cell in the given node or false
 *  otherwise
 */
bool GoL_Controller::is_cell_in_tree(Cell cell, Node *node)
{
    if (node->is_leaf()) {
        // if the node is a leaf, the cell is in the node if it is the same as
        // the node's cell
        if (node->get_cell().is_equal(cell)) {
            return true;
        }
    }
    // else compute the region where the cell should be
    Region region = node->get_region_for_point(cell.get_coordinates());
    if (region == NONE) {
        // if it is outside the node's boundaries, it is not in the node
        return false;
    }
    if(node->get_region(region) == NULL) {
        // if the region where it should be is empty, it is not in the node
        return false;
    }
    // search it in the region where it should be
    return is_cell_in_tree(cell, node->get_region(region));
}
