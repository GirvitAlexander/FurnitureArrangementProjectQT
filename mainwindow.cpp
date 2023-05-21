#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Room* room, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow), room(room)
{
    ui->setupUi(this);
    ui->graphicWidget->getParams(room->getParams());
}

MainWindow::~MainWindow()
{
    delete ui;
}

