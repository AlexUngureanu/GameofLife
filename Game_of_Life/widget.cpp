#include "widget.h"
#include "ui_widget.h"
#include <cassert>
#include <QTimer>
#include <math.h>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    running = false;
    size = INITIAL_SIZE;
    controller.reset_world_random(size, 0);
    QTimer *timer = new QTimer(this);
    connect (timer, SIGNAL(timeout()), this, SLOT(next_generation()));
    timer->start(1000);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_exitButton_clicked()
{
    qApp->exit();
}

void Widget::on_startButton_clicked()
{
    if(!running) {
        /*if (!selectedCells.is_empty()) {
            for (int i = 0;
                 i < controller.get_world_state().get_number_of_cells(); i++) {
                selectedCells.add(controller.get_world_state().cell_at_index(
                                      i));
            }
            controller.reset_world_with_cells(selectedCells.get_list(), size);
            selectedCells.destroy();
        }*/
        running = true;
        update();
    }
}

void Widget::on_resetButton_clicked()
{
    running = false;
    size = pow(2, ui->spinBox->text().toInt());
    controller.destroy_world_state();
    update();
}

void Widget::on_pauseButton_clicked()
{
    running = false;
    update();
}

void Widget::on_randomizeButton_clicked()
{
    if (!running) {
       int percentage = ui->randomizeBox->text().toInt();
       controller.reset_world_random(size, percentage);
       update();
    }
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    draw_board(p);
    draw_cells(p);
}

void Widget::draw_board(QPainter &p)
{
    p.setPen(Qt::red);
    p.drawRect(board_top_left_x, board_top_left_y, size * cell_length
               , size * cell_length);
}

void Widget::next_generation()
{
    if(running) {
        controller.next_world_state();
        update();
    }
}

void Widget::draw_cells(QPainter &p)
{
    p.setPen(Qt::blue);
    for (int i = 0; i < controller.get_world_state().get_number_of_cells(); i++)
    {

        Point cellCenter =
                controller.get_world_state().cell_at_index(i).get_coordinates();
        cellCenter.set_x(cellCenter.get_x() * cell_length);
        cellCenter.set_y(cellCenter.get_y() * cell_length);
        fill_cell(cellCenter, p);
    }
}

void Widget::fill_cell(Point cellCenter, QPainter &p)
{
    p.setPen(Qt::blue);
    float x_coord = cellCenter.get_x() - cell_length / 2 + 1 + board_top_left_x;
    float y_coord = cellCenter.get_y() - cell_length / 2 + 1 + board_top_left_y;
    QRectF rect = QRectF(x_coord, y_coord, cell_length, cell_length);
    p.drawRect(rect);
    p.fillRect(rect, Qt::blue);
}
