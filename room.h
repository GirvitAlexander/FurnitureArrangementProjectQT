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
    QVector<FurnitureWall> wallFurnitures;
    QVector<FurnitureRoom> roomFurnitures;
};

class Room
{
public:
    Room();

    void addRoomFurniture(QString name, size_t width, size_t height, TYPE_FURNITURE_ROOM);
    void addWallFurniture(QString name, size_t height, TYPE_FURNITURE_WALL);

    //void moveRoomFurniture(QString)

    void loadRoom(QString fileName);
    void saveRoom(QString fileName);

    ParametrsRoom getParams();

private:

    void loadDefaultRoom();
    size_t height;
    size_t width;
    QMap<QString, FurnitureWall> wallFurnitures;
    QMap<QString, QPoint> wallFurnituresCoords;

    QMap<QString, FurnitureRoom> roomFurnitures;
    QMap<QString, QPoint> roomFurnituresCoords;

};

#endif // ROOM_H
