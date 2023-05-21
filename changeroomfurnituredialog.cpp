#include "changeroomfurnituredialog.h"
#include "ui_changeroomfurnituredialog.h"

changeRoomFurnitureDialog::changeRoomFurnitureDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changeRoomFurnitureDialog)
{
    ui->setupUi(this);
}

changeRoomFurnitureDialog::~changeRoomFurnitureDialog()
{
    delete ui;
}
