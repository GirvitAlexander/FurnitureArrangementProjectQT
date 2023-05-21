#include <QDir>

#include "furniture.h"

Furniture::Furniture(QString nameFurniture)
    : nameFurniture(nameFurniture) {

}

QPixmap Furniture::getPicture() const {
    return picture;
}

QString Furniture::getName() const {
    return nameFurniture;
}

Furniture::~Furniture() {

}

FurnitureWall::FurnitureWall(QString nameFurniture, size_t width, TYPE_FURNITURE_WALL type)
    : Furniture(nameFurniture), type(type), width(width) {
    loadPicture();
}

TYPE_FURNITURE_WALL FurnitureWall::getType() const{
    return type;
}

void FurnitureWall::loadPicture() {
    QString saveFolder = "Signs";
    QString currentPath = PRO_FILE_PWD;
    QString savePath = QDir::toNativeSeparators(currentPath + QDir::separator() + saveFolder + QDir::separator());
    QString fileName = QDir::toNativeSeparators(savePath);

    switch (type) {
    case WINDOW:
        picture = QPixmap(fileName + "Window.png");
        break;
    case DOOR:
        picture = QPixmap(fileName + "Door.png");
        break;
    }
}

size_t FurnitureWall::getSize() const {
    return width;
}

FurnitureWall::~FurnitureWall() {

}

FurnitureRoom::FurnitureRoom(QString nameFurniture, size_t width, size_t height, TYPE_FURNITURE_ROOM type)
    : Furniture(nameFurniture), type(type), width(width), height(height)
{
    loadPicture();
}

TYPE_FURNITURE_ROOM FurnitureRoom::getType() const{
    return type;
};

void FurnitureRoom::loadPicture() {
    QString saveFolder = "Signs";
    QString currentPath = PRO_FILE_PWD;
    QString savePath = QDir::toNativeSeparators(currentPath + QDir::separator() + saveFolder + QDir::separator());
    QString fileName = QDir::toNativeSeparators(savePath);

    switch (type) {

    case CHAIR:

        picture = QPixmap(fileName + "Chair.png");
        break;
    case TABLE:
        picture = QPixmap(fileName + "Table.png");
        break;
    case SOFA:
        picture = QPixmap(fileName + "Sofa.png");
        break;
    case ARMCHAIR:
        picture = QPixmap(fileName + "Armchair.png");
        break;
    case CUPBOARD:
        picture = QPixmap(fileName + "Cupboard.png");
        break;
    }
}

QPair<size_t, size_t> FurnitureRoom::getSize() const {
    return qMakePair(width, height);
}

FurnitureRoom::~FurnitureRoom() {

}
