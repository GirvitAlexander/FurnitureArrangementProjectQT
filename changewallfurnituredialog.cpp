#include "changewallfurnituredialog.h"
#include "ui_changewallfurnituredialog.h"

changeWallFurnitureDialog::changeWallFurnitureDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changeWallFurnitureDialog)
{
    ui->setupUi(this);
}

changeWallFurnitureDialog::~changeWallFurnitureDialog()
{
    delete ui;
}
