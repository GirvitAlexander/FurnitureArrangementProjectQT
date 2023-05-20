#include "graphicwidget.h"
#include "ui_graphicwidget.h"

GraphicWidget::GraphicWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphicWidget)
{
    ui->setupUi(this);
}

GraphicWidget::~GraphicWidget()
{
    delete ui;
}
