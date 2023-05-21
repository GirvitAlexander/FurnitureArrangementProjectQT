#ifndef CONDITIONWIDGET_H
#define CONDITIONWIDGET_H

#include <QWidget>

namespace Ui {
    class ConditionWidget;
}

class ConditionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConditionWidget(QWidget *parent = nullptr);
    ~ConditionWidget();
public slots:

    void clickedSaveButton();
    void clickedLoadButton();

signals:
    void getSaveFile(QString);
    void getLoadFile(QString);

private:
    Ui::ConditionWidget *ui;
};

#endif // CONDITIONWIDGET_H
