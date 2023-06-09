#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "room.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Room* room, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Room* room;
};
#endif // MAINWINDOW_H
