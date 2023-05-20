#ifndef PARAMETRWIDGET_H
#define PARAMETRWIDGET_H

#include <QWidget>

namespace Ui {
    class ParametrWidget;
}

class ParametrWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ParametrWidget(QWidget *parent = nullptr);
    ~ParametrWidget();

private:
    Ui::ParametrWidget *ui;
};

#endif // PARAMETRWIDGET_H
