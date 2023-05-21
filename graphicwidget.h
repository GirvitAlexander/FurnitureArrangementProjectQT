#ifndef GRAPHICWIDGET_H
#define GRAPHICWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVector>

#include "room.h"

namespace Ui {
    class GraphicWidget;
}

class GraphicWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GraphicWidget(QWidget *parent = nullptr);
    ~GraphicWidget();

public slots:
    void getParams(ParametrsRoom pr);
    void drawBackSelect(QString name);

private:
    Ui::GraphicWidget *ui;

    QMap<QString, QLabel *> furnitures;
    ParametrsRoom paramsRoom;
    QLabel* back;
};

#endif // GRAPHICWIDGET_H
