/*
 * widget.h
 *
 * Header file for the Widget class that I overrode in order to create the GUI
 * of the game.
 *
 * Contains a timer (how many timeas a second to compute the next generation),
 * a paint event (draw the state of the board once an update was made), and the
 * methods for each button's press operation.
 *
 * Alexandru C. Ungureanu
 * April 27th, 2016
 */


#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QTextEdit>
#include "../Conway_Game_of_Life/GoL_Controller.h"
#include "../Conway_Game_of_Life/WorldState.h"
#include "../Conway_Game_of_Life/Point.h"
#include "../Conway_Game_of_Life/Cell.h"
#include "../Conway_Game_of_Life/Cell_Dynamic_Array.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);   // constructor of the class
    ~Widget();   // destructor of the class

protected:
    void paintEvent(QPaintEvent *);   // paint event that draws the game board

private slots:
    // operations to be done when pressing Exit
    void on_exitButton_clicked();

    // operations to be done when pressing Start
    void on_startButton_clicked();

    // operations to be done when pressing Reset
    void on_resetButton_clicked();

    // operations to be done when pressing Pause
    void on_pauseButton_clicked();

    // operations to be done when pressing Randomize
    void on_randomizeButton_clicked();

    // operations to be done when the timer signals that the next generation
    // needs to be computed
    void next_generation();

private:
    Ui::Widget *ui;   // widget UI
    bool running;   // true if game is running or false otherwise
    int size;   // side-length of the board
    const int INITIAL_SIZE = 128;   // initial side-length of the board
    GoL_Controller controller;   // controller that performs the algorithm
    const float board_top_left_x = 60;   // top-left corner of the board
    const float board_top_left_y = 120;   // bottom-right corner of the board
    const float cell_length = 3;   // side-length of a cell

    void draw_board(QPainter &p);   // draws the game board
    void draw_cells(QPainter &p);   // draws the live cells of the game
    void fill_cell(Point cellCenter, QPainter &p);   // fills a cell on board
};

#endif // WIDGET_H
