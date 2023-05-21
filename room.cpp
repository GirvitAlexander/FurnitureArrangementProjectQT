#include <cmath>
#include <algorithm>

#include <QFile>
#include <QDebug>

#include "room.h"
#include "typesfurnitures.h"

namespace {
    struct Point {
        double x, y;
    };

    QVector<Point> turnRectangle(QPoint center, int widht, int height, int angle) {
        QVector<Point> rect = { {(double)-widht / 2, (double)-height / 2},
                          {(double)widht / 2, (double)height / 2},
                          {(double)-widht / 2, (double)height / 2},
                          {(double)widht / 2, (double)-height / 2}};

        auto cos_cur = cos(M_PI * angle / 180), sin_cur = sin(M_PI * angle / 180);

        rect[0] = {rect[0].x * cos_cur - rect[0].y * sin_cur + center.x(), rect[0].x * sin_cur + rect[0].y * cos_cur + center.y()};
        rect[1] = {rect[1].x * cos_cur - rect[1].y * sin_cur + center.x(), rect[1].x * sin_cur + rect[1].y * cos_cur + center.y()};
        rect[2] = {rect[2].x * cos_cur - rect[2].y * sin_cur + center.x(), rect[2].x * sin_cur + rect[2].y * cos_cur + center.y()};
        rect[3] = {rect[3].x * cos_cur - rect[3].y * sin_cur + center.x(), rect[3].x * sin_cur + rect[3].y * cos_cur + center.y()};
        return rect;
    }
}

Room::Room() {
    loadDefaultRoom();
}

bool Room::addRoomFurniture(QString name, size_t width, size_t height, QPoint point, int angle, TYPE_FURNITURE_ROOM type) {
    if (hasName(name) || isIntersectAllRoom(point, width, height, angle)) {
        return false;
    }

    roomFurnitures.insert(name, FurnitureRoom(name, width, height, type));

    roomFurnituresCoords.insert(name, point);
    rotateAngleRoomFur.insert(name, angle);
    return true;
}

bool Room::addWallFurniture(QString name, size_t width, QPoint point, int angle, TYPE_FURNITURE_WALL type) {
    if (hasName(name) || isIntersectAllWall(point, width, angle)) {
        return false;
    }
    wallFurnitures.insert(name, FurnitureWall(name, width, type));
    wallFurnituresCoords.insert(name, point);
    rotateAngleWallFur.insert(name, angle);
    return true;
}

bool Room::moveRoomFurniture(QString name, QPoint newPoint) {
    if (!roomFurnitures.contains(name) || isIntersectRoomByName(name)) {
        return false;
    }
    roomFurnituresCoords[name] = newPoint;
    return true;
}

bool Room::moveWallFurniture(QString name, QPoint newPoint) {
    if (wallFurnitures.contains(name) || isIntersectWallByName(name)) {
        return false;
    }

    wallFurnituresCoords[name] = newPoint;
    return true;
}

bool Room::rotateRoomFurniture(QString name, int angle) {
    if (roomFurnitures.contains(name) || isIntersectRoomByName(name)) {
        return false;
    }
    rotateAngleRoomFur[name] = angle;
    return true;
}

bool Room::rotateWallFurniture(QString name, int angle) {
    if (wallFurnitures.contains(name) || isIntersectWallByName(name)) {
        return false;
    }
    rotateAngleWallFur[name] = angle;
    return true;
}

bool Room::loadRoom(QString fileName) {

    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return false;
    }

    QTextStream in(&file);

    QString countStr = in.readLine();
    int count = countStr.toInt();


    for (int i = 0; i < count; ++i) {
        in.readLine().trimmed();
        QString name = in.readLine().trimmed();

        QString object_type = in.readLine().trimmed();

        size_t object_type2 = in.readLine().trimmed().toInt();
        QPoint coordinatePoint;
        int angle;
        size_t  width, height = 0;

        QStringList coordinateStr = in.readLine().trimmed().split(" ");
        if (coordinateStr.size() == 2) {
            coordinatePoint.setX(coordinateStr[0].toInt());
            coordinatePoint.setY(coordinateStr[1].toInt());
        }

        angle = in.readLine().trimmed().toInt();
        width = in.readLine().trimmed().toInt();


        if (object_type=="wall"){
            FurnitureWall furniture_wall(name, width, static_cast<TYPE_FURNITURE_WALL>(object_type2));
            wallFurnitures.insert(name, furniture_wall);

            wallFurnituresCoords.insert(name, coordinatePoint);

            rotateAngleWallFur.insert(name, angle);

        }
        else if (object_type=="room"){
            height = in.readLine().trimmed().toInt();
            FurnitureRoom furniture_room(name, width, height, static_cast<TYPE_FURNITURE_ROOM>(object_type2));
            roomFurnitures.insert(name, furniture_room);

            roomFurnituresCoords.insert(name, coordinatePoint);

            rotateAngleRoomFur.insert(name, angle);

        }
    }
    file.close();
    return true;
}

bool Room::saveRoom(QString fileName){
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        return false;
    }
    QTextStream out(&file);

    int count = wallFurnitures.size() + roomFurnitures.size();
    out << count << Qt::endl<< Qt::endl;


    for (auto it = wallFurnitures.constBegin(); it != wallFurnitures.constEnd(); ++it) {
        const QString& name = it.key();
        FurnitureWall object_type = it.value();
        out << name << Qt::endl;
        out << "wall"<< Qt::endl;
        out << object_type.getType() << Qt::endl;
        out << wallFurnituresCoords[name].x() << " " << wallFurnituresCoords[name].y() << Qt::endl;
        out << rotateAngleWallFur[name] << Qt::endl;
        out << object_type.getSize() << Qt::endl << Qt::endl;
    }
    for (auto it = roomFurnitures.constBegin(); it != roomFurnitures.constEnd(); ++it){
        const QString& name = it.key();
        FurnitureRoom object_type = it.value();
        out << name << Qt::endl;
        out << "room"<< Qt::endl;
        out << object_type.getType() << Qt::endl;
        out << roomFurnituresCoords[name].x() << " " << roomFurnituresCoords[name].y() << Qt::endl;
        out << rotateAngleRoomFur[name] << Qt::endl;
        out << object_type.getSize().first << Qt::endl;
        out << object_type.getSize().second << Qt::endl << Qt::endl;
    }

    return true;
}


bool Room::hasName(QString name) const {
    return wallFurnitures.contains(name) || roomFurnitures.contains(name);
}

ParametrsRoom Room::getParams() const{
    return ParametrsRoom(wallFurnitures, roomFurnitures);
}

void Room::loadDefaultRoom() {
   QFile file("D:\\QT\\Kursach\\MAIN\\FurnitureArrangementProjectQT\\Save\\start.txt");

   if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
   {
       return;
   }

   QTextStream in(&file);
   QString elem_name;
   size_t num, width_window, width_door;
   while (true) {
       in >> elem_name;
       if (elem_name == "end_file") {
           break;
       }
       in >> num;
       if (elem_name == "width_room") {
           width = num;
       } else if (elem_name == "height_room") {
           height = num;
       } else if (elem_name == "width_window") {
           width_window = num;
       } else if (elem_name == "width_door") {
           width_door = num;
       } else if (elem_name == "cnt_window") {
           for (size_t i = 0; i < num; ++i) {
               size_t x, y;
               int angle;
               in >> x >> y >> angle;
               addWallFurniture(QString("Окно №%1").arg(i), width_window, QPoint(x, y), angle, WINDOW);
           }
       } else if (elem_name == "cnt_door") {
           for (size_t i = 0; i < num; ++i) {
               size_t x, y;
               int angle;
               in >> x >> y >> angle;
               addWallFurniture(QString("Дверь №%1").arg(i), width_door, QPoint(x, y), angle, DOOR);
           }
       }
   }

   file.close();
}

bool Room::isIntersectAllRoom(QPoint center, int widht, int height, int angle, QString notInterName) const {
    QVector<Point> rect = turnRectangle(center, widht, height, angle);

    if (rect[0].x < width_wall || rect[1].x < width_wall ||
        rect[2].x < width_wall || rect[3].x < width_wall ||
        rect[0].y < width_wall || rect[1].y < width_wall ||
        rect[2].y < width_wall || rect[3].y < width_wall ||
        rect[0].x > this->width - width_wall || rect[1].x > this->width - width_wall ||
        rect[2].x > this->width - width_wall || rect[3].x > this->width - width_wall ||
        rect[0].y > this->height - width_wall || rect[1].y > this->height - width_wall ||
        rect[2].y > this->height - width_wall || rect[3].y > this->height - width_wall) {
        return false;
    }

    auto x_min_1 = std::min({rect[0].x, rect[1].x, rect[2].x, rect[3].x});
    auto x_max_1 = std::max({rect[0].x, rect[1].x, rect[2].x, rect[3].x});
    auto y_min_1 = std::min({rect[0].y, rect[1].y, rect[2].y, rect[3].y});
    auto y_max_1 = std::max({rect[0].y, rect[1].y, rect[2].y, rect[3].y});

    for (const auto& elem: roomFurnitures) {
        auto size = elem.getSize();
        auto name_elem = elem.getName();
        if (notInterName == name_elem) {
            continue;
        }
        QVector<Point> rect_elem = turnRectangle(wallFurnituresCoords[name_elem], size.first, size.second, rotateAngleWallFur[name_elem]);

        auto x_min_2 = std::min({rect_elem[0].x, rect_elem[1].x, rect_elem[2].x, rect_elem[3].x});
        auto x_max_2 = std::max({rect_elem[0].x, rect_elem[1].x, rect_elem[2].x, rect_elem[3].x});
        auto y_min_2 = std::min({rect_elem[0].y, rect_elem[1].y, rect_elem[2].y, rect_elem[3].y});
        auto y_max_2 = std::max({rect_elem[0].y, rect_elem[1].y, rect_elem[2].y, rect_elem[3].y});

        if (x_min_1 <= x_max_2 && x_max_1 >= x_min_2 && y_min_1 <= y_max_2 && y_max_1 >= y_min_2) {
            return true;
        }
    }

    return false;
}

bool Room::isIntersectAllWall(QPoint center, int widht, int angle, QString notInterName) const {
    QVector<Point> rect = turnRectangle(center, widht, width_wall, angle);

    auto x_min_1 = std::min({rect[0].x, rect[1].x, rect[2].x, rect[3].x});
    auto x_max_1 = std::max({rect[0].x, rect[1].x, rect[2].x, rect[3].x});
    auto y_min_1 = std::min({rect[0].y, rect[1].y, rect[2].y, rect[3].y});
    auto y_max_1 = std::max({rect[0].y, rect[1].y, rect[2].y, rect[3].y});

    for (const auto& elem: wallFurnitures) {
        auto size = elem.getSize();
        auto name_elem = elem.getName();
        if (notInterName == name_elem) {
            continue;
        }
        QVector<Point> rect_elem = turnRectangle(wallFurnituresCoords[name_elem], size, width_wall, rotateAngleWallFur[name_elem]);

        auto x_min_2 = std::min({rect_elem[0].x, rect_elem[1].x, rect_elem[2].x, rect_elem[3].x});
        auto x_max_2 = std::max({rect_elem[0].x, rect_elem[1].x, rect_elem[2].x, rect_elem[3].x});
        auto y_min_2 = std::min({rect_elem[0].y, rect_elem[1].y, rect_elem[2].y, rect_elem[3].y});
        auto y_max_2 = std::max({rect_elem[0].y, rect_elem[1].y, rect_elem[2].y, rect_elem[3].y});

        if (x_min_1 <= x_max_2 && x_max_1 >= x_min_2 && y_min_1 <= y_max_2 && y_max_1 >= y_min_2) {
            return true;
        }
    }

    return false;
}

bool Room::isIntersectWallByName(QString name) const {
    auto size = wallFurnitures[name].getSize();
    return isIntersectAllWall(wallFurnituresCoords[name], size, rotateAngleWallFur[name], name);
}

bool Room::isIntersectRoomByName(QString name) const {
    auto size = roomFurnitures[name].getSize();
    return isIntersectAllRoom(roomFurnituresCoords[name], size.first, size.second, rotateAngleRoomFur[name], name);
}

