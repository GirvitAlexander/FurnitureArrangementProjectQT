#include <cmath>
#include <algorithm>

#include <QFile>
#include <QDebug>
#include <QDir>
#include <QMessageBox>

#include "room.h"
#include "typesfurnitures.h"

namespace {

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

bool Room::addRoomFurniture_h(QString name, size_t width, size_t height, QPoint point, int angle, TYPE_FURNITURE_ROOM type) {
    if (hasName(name) || isIntersectAllRoom(point, width, height, angle)) {
        return false;
    }

    roomFurnitures.insert(name, FurnitureRoom(name, width, height, type));

    roomFurnituresCoords.insert(name, point);
    rotateAngleRoomFur.insert(name, angle);
    emit changeParams(getParams());
    return true;
}

bool Room::addWallFurniture_h(QString name, size_t width, QPoint point, int angle, TYPE_FURNITURE_WALL type) {
    if (hasName(name) || isIntersectAllWall(point, width, angle)) {
        return false;
    }
    wallFurnitures.insert(name, FurnitureWall(name, width, type));
    wallFurnituresCoords.insert(name, point);
    rotateAngleWallFur.insert(name, angle);
    emit changeParams(getParams());
    return true;
}

bool Room::moveRoomFurniture_h(QString name, QPoint newPoint) {
    if (!roomFurnitures.contains(name) || isIntersectRoomByName(name)) {
        return false;
    }
    roomFurnituresCoords[name] = newPoint;
    emit changeParams(getParams());
    return true;
}

bool Room::moveWallFurniture_h(QString name, QPoint newPoint) {
    if (!wallFurnitures.contains(name) || isIntersectWallByName(name)) {
        return false;
    }

    wallFurnituresCoords[name] = newPoint;
    emit changeParams(getParams());
    return true;
}

bool Room::rotateRoomFurniture_h(QString name, int angle) {
    if (!roomFurnitures.contains(name) || isIntersectRoomByName(name)) {
        return false;
    }
    rotateAngleRoomFur[name] = angle;
    emit changeParams(getParams());
    return true;
}

bool Room::rotateWallFurniture_h(QString name, int angle) {
    if (!wallFurnitures.contains(name) || isIntersectWallByName(name)) {
        return false;
    }
    rotateAngleWallFur[name] = angle;
    emit changeParams(getParams());
    return true;
}

void Room::addRoomFurniture(QString name, size_t width, size_t height, QPoint point, int angle, TYPE_FURNITURE_ROOM type) {
    if (!addRoomFurniture_h( name, width, height, point, angle, type)) {
        QMessageBox::warning(nullptr, QStringLiteral("ОШИБКА"), QStringLiteral("Имя уже существует или произошло пересечение!!!"));
    }
}

void Room::addWallFurniture(QString name, size_t width, QPoint point, int angle, TYPE_FURNITURE_WALL type) {
    if (!addWallFurniture_h( name, width, point, angle, type)) {
        QMessageBox::warning(nullptr, QStringLiteral("ОШИБКА"), QStringLiteral("Имя уже существует или произошло пересечение!!!"));
    }
}

void Room::moveRoomFurniture(QString name, QPoint newPoint) {
    if (!moveRoomFurniture_h(name, newPoint)) {
        QMessageBox::warning(nullptr, QStringLiteral("ОШИБКА"), QStringLiteral("Неверное имя или произошло пересечение!!!"));
    }
}

void Room::moveWallFurniture(QString name, QPoint newPoint) {
    if (!moveWallFurniture_h(name, newPoint)) {
        QMessageBox::warning(nullptr, QStringLiteral("ОШИБКА"), QStringLiteral("Неверное имя или произошло пересечение!!!"));
    }
}

void Room::rotateRoomFurniture(QString name, int angle) {
    if (!rotateRoomFurniture_h(name, angle)) {
        QMessageBox::warning(nullptr, QStringLiteral("ОШИБКА"), QStringLiteral("Неверное имя или произошло пересечение!!!"));
    }
}

void Room::rotateWallFurniture(QString name, int angle) {
    if (!rotateWallFurniture_h(name, angle)) {
        QMessageBox::warning(nullptr, QStringLiteral("ОШИБКА"), QStringLiteral("Неверное имя или произошло пересечение!!!"));
    }
}

void Room::loadRoom(QString fileName) {

    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Can`t open file loadRoom()!";
        return;
    }

    QTextStream in(&file);

    QString countStr = in.readLine();
    int count = countStr.toInt();

    wallFurnitures.clear();
    wallFurnituresCoords.clear();
    rotateAngleWallFur.clear();

    roomFurnitures.clear();
    roomFurnituresCoords.clear();
    rotateAngleRoomFur.clear();

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
    emit changeParams(getParams());
    return;
}

void Room::removeRoomFurniture(QString name) {
    if (!roomFurnitures.contains(name)) {
        QMessageBox::warning(nullptr, QStringLiteral("ОШИБКА"), QStringLiteral("Такой мебели не существует!!!"));
    }
    roomFurnitures.erase(roomFurnitures.find(name));

    rotateAngleRoomFur.erase(rotateAngleRoomFur.find(name));

    roomFurnituresCoords.erase(roomFurnituresCoords.find(name));

    emit changeParams(getParams());
    return;
}

void Room::saveRoom(QString fileName){
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Can`t open file saveRoom()!";
        return;
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

    return;
}


bool Room::hasName(QString name) const {
    return wallFurnitures.contains(name) || roomFurnitures.contains(name);
}

ParametrsRoom Room::getParams() const{
    return {wallFurnitures, wallFurnituresCoords, rotateAngleWallFur,
            roomFurnitures, roomFurnituresCoords, rotateAngleRoomFur,
            height, width, width_wall};
}

void Room::loadDefaultRoom() {
    QString load_folder = "start.txt";
    QString saveFolder = "Save";
    QString currentPath = PRO_FILE_PWD;
    QString savePath = QDir::toNativeSeparators(currentPath + QDir::separator() + saveFolder + QDir::separator());
    QString fileName = QDir::toNativeSeparators(savePath + load_folder);
    QFile file(fileName);

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
       } else if (elem_name == "width_wall") {
           width_wall = num;
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

bool Room::checkIntersection(const QVector<Point>& rect1Points, const QVector<Point>& rect2Points) const{
    for (int i = 0; i < 4; ++i) {
        Point axis;
        if (i < 3) {
            axis = {rect1Points[i + 1].x - rect1Points[i].x, rect1Points[i + 1].y - rect1Points[i].y};
        } else {
            axis = {rect1Points[0].x - rect1Points[3].x, rect1Points[0].y - rect1Points[3].y};
        }

        double axisLength = std::sqrt(axis.x * axis.x + axis.y * axis.y);
        axis.x /= axisLength;
        axis.y /= axisLength;

        double minProjection1 = rect1Points[0].x * axis.x + rect1Points[0].y * axis.y;
        double maxProjection1 = minProjection1;
        for (const auto& point : rect1Points) {
            double projection = point.x * axis.x + point.y * axis.y;
            minProjection1 = std::min(minProjection1, projection);
            maxProjection1 = std::max(maxProjection1, projection);
        }

        double minProjection2 = rect2Points[0].x * axis.x + rect2Points[0].y * axis.y;
        double maxProjection2 = minProjection2;
        for (const auto& point : rect2Points) {
            double projection = point.x * axis.x + point.y * axis.y;
            minProjection2 = std::min(minProjection2, projection);
            maxProjection2 = std::max(maxProjection2, projection);
        }

        if (maxProjection1 < minProjection2 || maxProjection2 < minProjection1) {

            return false;
        }
    }

    return true;
}


bool Room::isIntersectAllRoom(QPoint center, int widht, int height, int angle, QString notInterName) const {


    QVector<Point> rect1 = turnRectangle(center, widht, height, angle);


    if (rect1[0].x < width_wall || rect1[1].x < width_wall ||
        rect1[2].x < width_wall || rect1[3].x < width_wall ||
        rect1[0].y < width_wall || rect1[1].y < width_wall ||
        rect1[2].y < width_wall || rect1[3].y < width_wall ||
        rect1[0].x > this->width - width_wall || rect1[1].x > this->width - width_wall ||
        rect1[2].x > this->width - width_wall || rect1[3].x > this->width - width_wall ||
        rect1[0].y > this->height - width_wall || rect1[1].y > this->height - width_wall ||
        rect1[2].y > this->height - width_wall || rect1[3].y > this->height - width_wall) {
        return true;
    }
    for (const auto& elem: roomFurnitures) {
        auto size = elem.getSize();
        auto name_elem = elem.getName();
        qDebug() << name_elem;
        if (notInterName == name_elem) {
            continue;
        }

        QVector<Point> rect2 = turnRectangle(roomFurnituresCoords[name_elem], size.first, size.second, rotateAngleRoomFur[name_elem]);
        if (checkIntersection(rect1, rect2)) {
            return true; // Прямоугольники пересекаются
        }
    }
    return false;


}


bool Room::isIntersectAllWall(QPoint center, int widht, int angle, QString notInterName) const {
    QVector<Point> rect1 = turnRectangle(center, widht, width_wall, angle);


    for (const auto& elem: wallFurnitures) {
        auto size = elem.getSize();
        auto name_elem = elem.getName();
        if (notInterName == name_elem) {
            continue;
        }
        QVector<Point> rect2 = turnRectangle(wallFurnituresCoords[name_elem], size, width_wall, rotateAngleWallFur[name_elem]);

        if (checkIntersection(rect1, rect2)) {
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

