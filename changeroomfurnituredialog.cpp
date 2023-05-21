#include "changeroomfurnituredialog.h"
#include "ui_changeroomfurnituredialog.h"

changeRoomFurnitureDialog::changeRoomFurnitureDialog(QPoint center_old, int angle_old, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changeRoomFurnitureDialog) {
    ui->setupUi(this);
    ui->angle->setValue(angle_old);

    ui->xCoord->setValue(center_old.x());
    ui->yCoord->setValue(center_old.y());
}

void changeRoomFurnitureDialog::accept(){
    angle = ui->angle->value();

    center = {ui->xCoord->value(), ui->yCoord->value()};

    QDialog::accept();
}

changeRoomFurnitureDialog::~changeRoomFurnitureDialog() {
    delete ui;
}
