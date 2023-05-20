#include "parametrwidget.h"
#include "ui_parametrwidget.h"

ParametrWidget::ParametrWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParametrWidget)
{
    ui->setupUi(this);
}

ParametrWidget::~ParametrWidget()
{
    delete ui;
}
