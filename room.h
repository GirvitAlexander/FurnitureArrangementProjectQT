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
    QMap<QString, FurnitureWall> wallFurnitures;
    QMap<QString, QPoint> wallFurnituresCoords;
    QMap<QString, int> rotateAngleWallFur;

    QMap<QString, FurnitureRoom> roomFurnitures;
    QMap<QString, QPoint> roomFurnituresCoords;
    QMap<QString, int> rotateAngleRoomFur;

    size_t height;
    size_t width;
    size_t width_wall;
};

struct Point {
    double x, y;
};

class Room: public QObject
{
    Q_OBJECT

public:
    Room();

public slots:
    void loadRoom(QString fileName);
    void saveRoom(QString fileName);

    void addRoomFurniture(QString name, size_t width, size_t height, QPoint, int, TYPE_FURNITURE_ROOM);
    void addWallFurniture(QString name, size_t height, QPoint, int, TYPE_FURNITURE_WALL);

    void moveRoomFurniture(QString, QPoint);
    void moveWallFurniture(QString, QPoint);

    void removeRoomFurniture(QString);

    void rotateRoomFurniture(QString, int);
    void rotateWallFurniture(QString, int);

public:
    bool hasName(QString) const;

    ParametrsRoom getParams() const;

signals:
    void changeParams(ParametrsRoom params);

private:
    bool addRoomFurniture_h(QString name, size_t width, size_t height, QPoint, int, TYPE_FURNITURE_ROOM);
    bool addWallFurniture_h(QString name, size_t height, QPoint, int, TYPE_FURNITURE_WALL);

    bool moveRoomFurniture_h(QString, QPoint);
    bool moveWallFurniture_h(QString, QPoint);

    bool rotateRoomFurniture_h(QString, int);
    bool rotateWallFurniture_h(QString, int);

    bool isIntersectAllRoom(QPoint center, int widht, int height, int angle, QString notInterName  = "") const;
    bool isIntersectAllWall(QPoint center, int widht, int angle, QString notInterName = "") const;
    bool isIntersectWallByName(QString name) const;
    bool isIntersectRoomByName(QString name) const;

    bool checkIntersection(const QVector<Point>& rect1Points, const QVector<Point>& rect2Points) const;

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
