#include "graphicwidget.h"
#include "ui_graphicwidget.h"

#include <QMatrix2x2>
#include <QPixmap>
#include <QDir>

GraphicWidget::GraphicWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphicWidget) {
    back = nullptr;
    ui->setupUi(this);
}

GraphicWidget::~GraphicWidget() {
    delete ui;
    for (auto& elem: furnitures) {
        delete elem;
    }
    furnitures.clear();
}

void GraphicWidget::drawBackSelect(QString name) {
    QString saveFolder = "Signs";
    QString currentPath = PRO_FILE_PWD;
    QString savePath = QDir::toNativeSeparators(currentPath + QDir::separator() + saveFolder + QDir::separator());
    QString fileName = QDir::toNativeSeparators(savePath + "Back.png");

    if (back) {
        delete back;
    }

    back = new QLabel(this);
    QPixmap backPicture = QPixmap(fileName);
    if (paramsRoom.roomFurnitures.contains(name)) {
        auto size = paramsRoom.roomFurnitures[name].getSize();
        auto picture = paramsRoom.roomFurnitures[name].getPicture();
        auto angle = paramsRoom.rotateAngleRoomFur[name];
        auto center = paramsRoom.roomFurnituresCoords[name];

        QPixmap scale = backPicture.scaled(QSize(size.first + 2, size.second + 2));
        QPixmap rotate = scale.transformed(QTransform().rotate(angle));

        back->setPixmap(rotate);
        back->setGeometry(center.x() - (size.first + 2) / 2, paramsRoom.height - (center.y() + (size.second + 2) / 2), rotate.width(), rotate.height());

        back->show();
        delete furnitures[name];
        furnitures[name] = new QLabel(this);
        furnitures[name]->setObjectName(name);

        scale = picture.scaled(QSize(size.first, size.second));
        rotate = scale.transformed(QTransform().rotate(angle));

        furnitures[name]->setPixmap(rotate);
        furnitures[name]->setGeometry(center.x() - size.first / 2, paramsRoom.height - (center.y() + size.second / 2), rotate.width(), rotate.height());

        furnitures[name]->show();
    } else {
        auto size = paramsRoom.wallFurnitures[name].getSize();
        auto picture = paramsRoom.wallFurnitures[name].getPicture();
        auto angle = paramsRoom.rotateAngleWallFur[name];
        auto center = paramsRoom.wallFurnituresCoords[name];

        QPixmap scale = backPicture.scaled(QSize(size + 2, paramsRoom.width_wall + 2));
        QPixmap rotate = scale.transformed(QTransform().rotate(angle));

        back->setPixmap(rotate);
        back->setGeometry(center.x() - rotate.width() / 2, paramsRoom.height - (center.y() + rotate.height() / 2), rotate.width(), rotate.height());

        back->show();
        delete furnitures[name];
        furnitures[name] = new QLabel(this);
        furnitures[name]->setObjectName(name);

        scale = picture.scaled(QSize(size, paramsRoom.width_wall));
        rotate = scale.transformed(QTransform().rotate(angle));

        furnitures[name]->setPixmap(rotate);
        furnitures[name]->setGeometry(center.x() - rotate.width() / 2, paramsRoom.height - (center.y() + rotate.height() / 2), rotate.width(), rotate.height());

        furnitures[name]->show();
    }
}

void GraphicWidget::getParams(ParametrsRoom pr) {
    paramsRoom = pr;
    for (auto& elem: furnitures) {
        delete elem;
    }
    furnitures.clear();
    auto keys = paramsRoom.roomFurnitures.keys();
    for (const auto& elem: keys) {
        auto size = paramsRoom.roomFurnitures[elem].getSize();
        auto picture = paramsRoom.roomFurnitures[elem].getPicture();
        auto angle = paramsRoom.rotateAngleRoomFur[elem];
        auto center = paramsRoom.roomFurnituresCoords[elem];

        furnitures[elem] = new QLabel(this);
        furnitures[elem]->setObjectName(elem);

        QPixmap scale = picture.scaled(QSize(size.first, size.second));
        QPixmap rotate = scale.transformed(QTransform().rotate(angle));

        furnitures[elem]->setPixmap(rotate);
        furnitures[elem]->setGeometry(center.x() - size.first / 2, paramsRoom.height - (center.y() + size.second / 2), rotate.width(), rotate.height());

        furnitures[elem]->show();
        qDebug() << elem << furnitures[elem]->geometry();
    }

    keys = paramsRoom.wallFurnitures.keys();
    for (const auto& elem: keys) {
        auto size = paramsRoom.wallFurnitures[elem].getSize();
        auto picture = paramsRoom.wallFurnitures[elem].getPicture();
        auto angle = paramsRoom.rotateAngleWallFur[elem];
        auto center = paramsRoom.wallFurnituresCoords[elem];

        furnitures[elem] = new QLabel(this);
        furnitures[elem]->setObjectName(elem);
        QPixmap scale = picture.scaled(QSize(size, paramsRoom.width_wall));
        QPixmap rotate = scale.transformed(QTransform().rotate(angle));

        furnitures[elem]->setPixmap(rotate);
        furnitures[elem]->setGeometry(center.x() - rotate.width() / 2, paramsRoom.height - (center.y() + rotate.height() / 2), rotate.width(), rotate.height());

        furnitures[elem]->show();
        qDebug() << elem << furnitures[elem]->geometry();

    }
}

