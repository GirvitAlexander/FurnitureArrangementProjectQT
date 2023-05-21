#ifndef ROOM_H
#define ROOM_H

#include <cstddef>

#include <QVector>
#include <QPoint>
#include <QString>
#include <QMap>

#include "typesfurnitures.h"
#include "furniture.h"

using std::size_t;

struct ParametrsRoom {
    ParametrsRoom(QMap<QString, FurnitureWall> wallFurnitures, QMap<QString, FurnitureRoom> roomFurnitures)
        : wallFurnitures(wallFurnitures), roomFurnitures(roomFurnitures) {

    }
    QMap<QString, FurnitureWall> wallFurnitures;
    QMap<QString, FurnitureRoom> roomFurnitures;
};

class Room
{
public:
    Room();

    bool addRoomFurniture(QString name, size_t width, size_t height, QPoint, int, TYPE_FURNITURE_ROOM);
    bool addWallFurniture(QString name, size_t height, QPoint, int, TYPE_FURNITURE_WALL);

    bool moveRoomFurniture(QString, QPoint);
    bool moveWallFurniture(QString, QPoint);

    bool rotateRoomFurniture(QString, int);
    bool rotateWallFurniture(QString, int);

    bool loadRoom(QString fileName);
    bool saveRoom(QString fileName);

    bool hasName(QString) const;

    ParametrsRoom getParams() const;

private:

    bool isIntersectAllRoom(QPoint center, int widht, int height, int angle, QString notInterName  = "") const;
    bool isIntersectAllWall(QPoint center, int widht, int angle, QString notInterName = "") const;
    bool isIntersectWallByName(QString name) const;
    bool isIntersectRoomByName(QString name) const;

    void loadDefaultRoom();

    size_t height;
    size_t width;
    size_t width_wall;

    QMap<QString, FurnitureWall> wallFurnitures;
    QMap<QString, QPoint> wallFurnituresCoords;
    QMap<QString, int> rotateAngleWallFur;

    QMap<QString, FurnitureRoom> roomFurnitures;
    QMap<QString, QPoint> roomFurnituresCoords;
    QMap<QString, int> rotateAngleRoomFur;
};

#endif // ROOM_H
