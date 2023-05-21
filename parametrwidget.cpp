#include "parametrwidget.h"
#include "ui_parametrwidget.h"

#include <QMap>

#include "typesfurnitures.h"
#include "addfurnitureroomdialog.h"

ParametrWidget::ParametrWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParametrWidget) {
    ui->setupUi(this);
    connect(ui->changeParamButton, &QPushButton::clicked,
            this, &ParametrWidget::clickedChangeParams);

    connect(ui->addFurnitureButton, &QPushButton::clicked,
            this, &ParametrWidget::addNewFurnitureRoom);

    connect(ui->selectFunitureComboBox, &QComboBox::currentTextChanged,
            this, &ParametrWidget::changeComboBox);
}

void ParametrWidget::changeComboBox(QString name) {
    if (name != "")
        emit changeFurniture(name);
}

void ParametrWidget::clickedChangeParams() {
}

void ParametrWidget::addNewFurnitureRoom() {
    addFurnitureRoomDialog dialog;
    if (dialog.exec() == QDialog::Accepted) {
        auto type = dialog.getType();
        auto width = dialog.getWidth();
        auto height = dialog.getHeight();
        auto angle = dialog.getAngle();
        auto center = dialog.getCenter();
        auto name = dialog.getName();

        emit addFurnitureRoom(name, width, height, center, angle, type);
    }
}

void ParametrWidget::getParams(ParametrsRoom pr) {
    paramsRoom = pr;
    QMap<TYPE_FURNITURE_ROOM, int> countTypesRoom;
    countTypesRoom[CHAIR] = 0;
    countTypesRoom[TABLE] = 0;
    countTypesRoom[CUPBOARD] = 0;
    countTypesRoom[SOFA] = 0;
    countTypesRoom[ARMCHAIR] = 0;

    QMap<TYPE_FURNITURE_WALL, int> countTypesWall;
    countTypesWall[WINDOW] = 0;
    countTypesWall[DOOR] = 0;

    for (const auto& elem: paramsRoom.roomFurnitures) {
        countTypesRoom[elem.getType()] += 1;
    }

    for (const auto& elem: paramsRoom.wallFurnitures) {
        countTypesWall[elem.getType()] += 1;
    }
    ui->chairCnt->setText(QString::number(countTypesRoom[CHAIR]));
    ui->tableCnt->setText(QString::number(countTypesRoom[TABLE]));
    ui->cupboardCnt->setText(QString::number(countTypesRoom[CUPBOARD]));
    ui->sofaCnt->setText(QString::number(countTypesRoom[SOFA]));
    ui->armChairCnt->setText(QString::number(countTypesRoom[ARMCHAIR]));

    ui->windowCnt->setText(QString::number(countTypesWall[WINDOW]));
    ui->doorsCnt->setText(QString::number(countTypesWall[DOOR]));

    ui->widthRoom->setText(QString::number(paramsRoom.width));
    ui->heightRoom->setText(QString::number(paramsRoom.height));
    ui->widthRoomWall->setText(QString::number(paramsRoom.width_wall));

    auto keysRoom = paramsRoom.roomFurnitures.keys(),
         keysWall = paramsRoom.wallFurnitures.keys();
    ui->selectFunitureComboBox->clear();
    ui->selectFunitureComboBox->addItems(keysRoom);
    ui->selectFunitureComboBox->addItems(keysWall);
}

ParametrWidget::~ParametrWidget() {
    delete ui;
}
