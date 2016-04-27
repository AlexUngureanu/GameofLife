/*
 * GoL_Controller.h
 *
 * Header for the GoL_Controller class. A controller that uses the tree
 * representation of the game board and the worldstate of living cell to
 * compute the state of the game in the next generation.
 *
 * The controller has two trees, depicted by their two roots: root for the
 * tree associated with the current state of the game, and next_root for the
 * tree associated with the next generation's state of the game. The game's
 * algorithm is contained in the methods of this class.
 *
 * Using the world state of the current generation, the controller creates the
 * tree associated with it. It then uses the tree and worldstate to compute the
 * next_root - tree, the tree for the next generation. Once the next-generation
 * tree is computed, it updates the worldstate so that it contains the state of
 * live cells for the next generation.
 *
 * Alexandru C. Ungureanu
 * April 27th, 2016
 */


#ifndef GOL_CONTROLLER_H
#define GOL_CONTROLLER_H

#include <iostream>
using namespace std;
#include "Node.h"
#include "WorldState.h"
#include "Cell.h"
#include "Point.h"

enum State { alive, neighbor };

class GoL_Controller {
public:
    GoL_Controller();   // constructor of the class

    ~GoL_Controller();   // destructor of the class

    // resets the state of the board to restart the game from scratch
    void reset_world_random(int squareLength, int percentage);

    // returns the worldstate associated with the current board
    WorldState &get_world_state();
    // computes the next generation board state
    void next_world_state();
    // empties the tree associated with the curret state
    void destroy_current_tree();
    // empties the worldstate associated with the current state
    void destroy_world_state();

private:
    Node *root;   // root of the current generation's board
    Node *next_root;   // root of the next generation's board
    WorldState current_world_state;   // current worldstate of the board
    int age;   // current age (generation) for the game
    int size;   // the side-length of the board

    // computes the next generation using the list of live cells of the current
    // generation and the number of live cells
    void compute_next_generation(Cell cells[], int numCells);
    // updates the worldstate from the tree with the given root
    void update_world_state(Node *node);
    // builds the tree associated with the current state using the list of live
    // cells
    void build_tree_map(Cell cells[], int population);
    // computes the state of the cell for the next generation (alive or dead)
    void compute_next_generation_state(Cell cell, State state);
    // empties the tree using a post-order traversal
    void post_order_delete(Node *node);
    // inserts a live cell in the tree with the given root
    void insert_cell(Cell cell, Node *node);
    // randomly generates a set of live cells on the board; the set will have
    // the specified size (population)
    void random_generate_specified_population(int population);
    // checks if the given cell is in the tree with the given root
    bool is_cell_in_tree(Cell cell, Node *node);
};

#endif // GOL_CONTROLLER_H
