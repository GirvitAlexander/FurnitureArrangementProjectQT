#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Room* room, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow), room(room)
{
    ui->setupUi(this);
    ui->graphicWidget->getParams(room->getParams());
    ui->parametrWidget->getParams(room->getParams());
    connect(ui->conditoinWidget, &ConditionWidget::getLoadFile,
                room, &Room::loadRoom);
    connect(ui->conditoinWidget, &ConditionWidget::getSaveFile,
                room, &Room::saveRoom);
    connect(room, &Room::changeParams,
            ui->graphicWidget, &GraphicWidget::getParams);
    connect(room, &Room::changeParams,
            ui->parametrWidget, &ParametrWidget::getParams);

    connect(ui->parametrWidget, &ParametrWidget::addFurnitureRoom,
            room, &Room::addRoomFurniture);

    connect(ui->parametrWidget, &ParametrWidget::changeFurniture,
            ui->graphicWidget, &GraphicWidget::drawBackSelect);

    connect(ui->parametrWidget, &ParametrWidget::moveFur,
            room, &Room::moveRoomFurniture);

    connect(ui->parametrWidget, &ParametrWidget::rotateFur,
            room, &Room::rotateRoomFurniture);

    connect(ui->parametrWidget, &ParametrWidget::removeFur,
            room, &Room::removeRoomFurniture);
}

MainWindow::~MainWindow()
{
    delete ui;
}

