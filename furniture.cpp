#include "furniture.h"

Furniture::Furniture(QString nameFurniture)
    : nameFurniture(nameFurniture) {

}

QPixmap Furniture::getPicture() {
    return picture;
}

QString Furniture::getName() {
    return nameFurniture;
}

Furniture::~Furniture() {

}

FurnitureWall::FurnitureWall(QString nameFurniture, size_t width, TYPE_FURNITURE_WALL type)
    : Furniture(nameFurniture), type(type), width(width)
{
    loadPicture();
}


void FurnitureWall::loadPicture() {
    switch (type) {
    case WINDOW:
        picture = QPixmap("D:\\QT\\Kursach\\MAIN\\FurnitureArrangementProjectQT\\Window.png");
        break;
    case DOOR:
        picture = QPixmap("D:\\QT\\Kursach\\MAIN\\FurnitureArrangementProjectQT\\Door.png");
        break;
    }
}

size_t FurnitureWall::getSize() {
    return width;
}

FurnitureWall::~FurnitureWall() {

}

FurnitureRoom::FurnitureRoom(QString nameFurniture, size_t width, size_t height, TYPE_FURNITURE_ROOM type)
    : Furniture(nameFurniture), type(type), width(width), height(height)
{
    loadPicture();
}

void FurnitureRoom::loadPicture() {
    switch (type) {
    case CHAIR:
        picture = QPixmap("D:\\QT\\Kursach\\MAIN\\FurnitureArrangementProjectQT\\Chair.png");
        break;
    case TABLE:
        picture = QPixmap("D:\\QT\\Kursach\\MAIN\\FurnitureArrangementProjectQT\\Table.png");
        break;
    case SOFA:
        picture = QPixmap("D:\\QT\\Kursach\\MAIN\\FurnitureArrangementProjectQT\\Sofa.png");
        break;
    case ARMCHAIR:
        picture = QPixmap("D:\\QT\\Kursach\\MAIN\\FurnitureArrangementProjectQT\\Armchair.png");
        break;
    case CUPBOARD:
        picture = QPixmap("D:\\QT\\Kursach\\MAIN\\FurnitureArrangementProjectQT\\Cupboard.png");
        break;
    }
}

QPair<size_t, size_t> FurnitureRoom::getSize() {
    return qMakePair(width, height);
}

FurnitureRoom::~FurnitureRoom() {

}
