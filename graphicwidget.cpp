#include "graphicwidget.h"
#include "ui_graphicwidget.h"

#include <QMatrix2x2>
#include <QPixmap>

GraphicWidget::GraphicWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphicWidget) {

    ui->setupUi(this);

}

GraphicWidget::~GraphicWidget() {
    delete ui;
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

