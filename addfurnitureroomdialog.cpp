#include "addfurnitureroomdialog.h"
#include "ui_addfurnitureroomdialog.h"

#include <QMessageBox>

#include "typesfurnitures.h"

addFurnitureRoomDialog::addFurnitureRoomDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addFurnitureRoomDialog) {

    ui->setupUi(this);
    ui->typeComboBox->addItem("Стул");
    ui->typeComboBox->addItem("Стол");
    ui->typeComboBox->addItem("Кресло");
    ui->typeComboBox->addItem("Диван");
    ui->typeComboBox->addItem("Шкаф");

}

void addFurnitureRoomDialog::accept(){
    angle = ui->angle->value();

    if (angle < 0 || angle >= 360) {
        QMessageBox::warning(this, QStringLiteral("ОШИБКА"), QStringLiteral("Угол должен быть в диапозоне от 0 до 359 !!!"));
        return;
    }
    name = ui->nameLineEdit->text();
    if (name.isEmpty()) {
        QMessageBox::warning(this, QStringLiteral("ОШИБКА"), QStringLiteral("Нет названия мебели!!!"));
        return;
    }

    if (ui->widthFruniture->value() <= 0 || ui->heightFruniture->value() <= 0) {
        QMessageBox::warning(this, QStringLiteral("ОШИБКА"), QStringLiteral("Ширина и длина мебели должны быть положительными числами!!!"));
        return;
    }

    width = ui->widthFruniture->value();
    height = ui->heightFruniture->value();

    center = {ui->xCoord->value(), ui->yCoord->value()};
    if (center.x() < 0 || center.x() < 0) {
        QMessageBox::warning(this, QStringLiteral("ОШИБКА"), QStringLiteral("Координаты центра должны быть не отрицательными числами!!!"));
        return;
    }

    QString typeStr = ui->typeComboBox->currentText();

    if (typeStr == "Стул") {
        type = CHAIR;
    } else if (typeStr == "Стол") {
        type = TABLE;
    } else if (typeStr == "Кресло") {
        type = ARMCHAIR;
    } else if (typeStr == "Диван") {
        type = SOFA;
    } else if (typeStr == "Шкаф") {
        type = CUPBOARD;
    }

    QDialog::accept();
}


addFurnitureRoomDialog::~addFurnitureRoomDialog()
{
    delete ui;
}
