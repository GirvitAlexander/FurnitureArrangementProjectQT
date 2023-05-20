#ifndef GRAPHICWIDGET_H
#define GRAPHICWIDGET_H

#include <QWidget>

namespace Ui {
    class GraphicWidget;
}

class GraphicWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GraphicWidget(QWidget *parent = nullptr);
    ~GraphicWidget();

private:
    Ui::GraphicWidget *ui;
};

#endif // GRAPHICWIDGET_H
