#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Room* room, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow), room(room)
{
    ui->setupUi(this);
    ui->graphicWidget->getParams(room->getParams());
    connect(ui->conditoinWidget, &ConditionWidget::getLoadFile,
                room, &Room::loadRoom);
    connect(ui->conditoinWidget, &ConditionWidget::getSaveFile,
                room, &Room::saveRoom);
    connect(room, &Room::changeParams,
            ui->graphicWidget, &GraphicWidget::getParams);
}

MainWindow::~MainWindow()
{
    delete ui;
}

