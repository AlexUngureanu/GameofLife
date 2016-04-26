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
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void on_exitButton_clicked();

    void on_startButton_clicked();

    void on_resetButton_clicked();

    void on_pauseButton_clicked();

    void on_randomizeButton_clicked();

    void next_generation();

private:
    Ui::Widget *ui;
    bool running;
    int size;
    const int INITIAL_SIZE = 128;
    GoL_Controller controller;
    const float board_top_left_x = 60;
    const float board_top_left_y = 120;
    const float cell_length = 5;

    void draw_board(QPainter &p);
    void draw_cells(QPainter &p);
    void fill_cell(Point cellCenter, QPainter &p);
};

#endif // WIDGET_H
