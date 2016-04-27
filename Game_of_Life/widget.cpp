/*
 * widget.cpp
 *
 * Source file for the widget class
 *
 * Alexandru C. Ungureanu
 * April 27th, 2016
 */

#include "widget.h"
#include "ui_widget.h"
#include <cassert>
#include <QTimer>
#include <math.h>

/*
 * constructor of the class
 * initializes the timer and side-length of the board, as well as the controller
 */
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);   // sets up the graphical interface
    running = false;   // the game is not running until Start is pressed
    size = INITIAL_SIZE;   // initialize the side-length of the board
    // reset the world (empty)
    controller.reset_world_random(size, 0);
    QTimer *timer = new QTimer(this);   // timer for next generation computation
    connect (timer, SIGNAL(timeout()), this, SLOT(next_generation()));
    // set the desired number of ms for the timer's signal
    timer->start(1000);
}

/*
 * destructor of the class
 */
Widget::~Widget()
{
    delete ui;
}

/*
 * when Exit pressed, close the application
 */
void Widget::on_exitButton_clicked()
{
    qApp->exit();
}

/*
 * when Start pressed, run the game
 */
void Widget::on_startButton_clicked()
{
    if(!running) {
        // game is running, and update the paint event
        running = true;
        update();
    }
}

/*
 * resets the board and stops the game if running
 */
void Widget::on_resetButton_clicked()
{
    running = false;
    // get the new size of the board from the corresponding Text Box
    size = pow(2, ui->spinBox->text().toInt());
    // reset the controller (empty its components)
    controller.destroy_world_state();
    // update the paint event to regenerate the initial state
    update();
}

/*
 * when Pause pressed, pause the game so that it is not running anymore
 */
void Widget::on_pauseButton_clicked()
{
    running = false;
    // update the paint event
    update();
}

/*
 * when Randomize pressed, generate the initial state of the board if
 * game is not running
 */
void Widget::on_randomizeButton_clicked()
{
    if (!running) {
        // get the percentage of cells that are alive from the corresponding
        // Text Box
       int percentage = ui->randomizeBox->text().toInt();
       // reset the controller with the appropriate size and percentage of live
       // cells
       controller.reset_world_random(size, percentage);
       // update the paint event such that it draws the cells
       update();
    }
}

/*
 * paint event that draws the state of the game and is called by an update
 */
void Widget::paintEvent(QPaintEvent *)
{
    QPainter p(this);   // painter
    draw_board(p);   // draw the board margins
    draw_cells(p);   // draw the live cells
}

/*
 * responsible for drawing the margins of the board
 */
void Widget::draw_board(QPainter &p)
{
    p.setPen(Qt::red);   // red color
    // draw a rectangle with the given corners and side-lengths (square)
    p.drawRect(board_top_left_x, board_top_left_y, size * cell_length
               , size * cell_length);
}

/*
 * responsible for computing the enxt generation from the controller
 * is called periodically by the timer's signal
 */
void Widget::next_generation()
{
    // compute next generation only if game is running
    if(running) {
        // get the next generation's state from the controller
        controller.next_world_state();
        // update the paint event so it displays the new generation
        update();
    }
}

/*
 * draws the live cells on the board
 */
void Widget::draw_cells(QPainter &p)
{
    p.setPen(Qt::blue);   // blue color
    for (int i = 0; i < controller.get_world_state().get_number_of_cells(); i++)
    {
        // get the center of each cell in the controller's worldstate
        Point cellCenter =
                controller.get_world_state().cell_at_index(i).get_coordinates();
        cellCenter.set_x(cellCenter.get_x() * cell_length);   // scale cell size
        cellCenter.set_y(cellCenter.get_y() * cell_length);   // scale cell size
        // fill the cell with the desired center
        fill_cell(cellCenter, p);
    }
}

/*
 * fills a cell on the board with the given center
 */
void Widget::fill_cell(Point cellCenter, QPainter &p)
{
    p.setPen(Qt::blue);   // blue color
    // compute the coordinates of the top-left corner of the square to be drawn
    float x_coord = cellCenter.get_x() - cell_length / 2 + 1 + board_top_left_x;
    float y_coord = cellCenter.get_y() - cell_length / 2 + 1 + board_top_left_y;
    // draw the cell on the board as a rectangle with equal sides (square)
    QRectF rect = QRectF(x_coord, y_coord, cell_length, cell_length);
    p.drawRect(rect);
    // fill the interior of the cell-square with blue color
    p.fillRect(rect, Qt::blue);
}
