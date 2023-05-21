#ifndef PARAMETRWIDGET_H
#define PARAMETRWIDGET_H

#include <QWidget>

#include "room.h"

namespace Ui {
    class ParametrWidget;
}

class ParametrWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ParametrWidget(QWidget *parent = nullptr);
    ~ParametrWidget();

public slots:
    void getParams(ParametrsRoom pr);
    void clickedChangeParams();
    void addNewFurnitureRoom();
    void changeComboBox(QString);

signals:
    void addFurnitureRoom(QString name, size_t width, size_t height, QPoint, int, TYPE_FURNITURE_ROOM);
    void changeFurniture(QString name);

private:
    Ui::ParametrWidget *ui;
    ParametrsRoom paramsRoom;

};

#endif // PARAMETRWIDGET_H
