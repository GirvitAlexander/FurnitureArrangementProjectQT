#ifndef FURNITURE_H
#define FURNITURE_H

#include <cstddef>

#include <QPixmap>
#include <QString>
#include <QPair>

#include "typesfurnitures.h"

using std::size_t;

class Furniture
{
public:
    Furniture(QString _nameFurniture);

    QPixmap getPicture() const;
    QString getName() const;
    virtual ~Furniture();

protected:
    virtual void loadPicture() = 0;
    QString nameFurniture;
    QPixmap picture;
};

class FurnitureWall: public Furniture {
public:
    FurnitureWall() : Furniture("") {}
    FurnitureWall(QString nameFurniture, size_t width, TYPE_FURNITURE_WALL type);
    ~FurnitureWall();

    TYPE_FURNITURE_WALL getType() const;
    size_t getSize() const;

private:
    void loadPicture() override;

    TYPE_FURNITURE_WALL type;
    size_t width;
};

class FurnitureRoom: public Furniture {
public:
    FurnitureRoom() : Furniture("") {}
    FurnitureRoom(QString nameFurniture, size_t width, size_t height, TYPE_FURNITURE_ROOM type);
    ~FurnitureRoom();

    QPair<size_t, size_t> getSize() const;
    TYPE_FURNITURE_ROOM getType() const;

private:
    TYPE_FURNITURE_ROOM type;
    size_t width;
    size_t height;

    void loadPicture() override;
};

#endif // FURNITURE_H
