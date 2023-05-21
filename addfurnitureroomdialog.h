#ifndef ADDFURNITUREROOMDIALOG_H
#define ADDFURNITUREROOMDIALOG_H

#include <QDialog>
#include <QVector>

#include "typesfurnitures.h"

namespace Ui {
    class addFurnitureRoomDialog;
}

class addFurnitureRoomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addFurnitureRoomDialog(QWidget *parent = nullptr);
    ~addFurnitureRoomDialog();

    TYPE_FURNITURE_ROOM getType() {
        return type;
    }

    size_t getWidth() {
        return width;
    }

    size_t getHeight() {
        return height;
    }

    int getAngle() {
        return angle;
    }

    QPoint getCenter() {
        return center;
    }

    QString getName() {
        return name;
    }

private:
    Ui::addFurnitureRoomDialog *ui;
    TYPE_FURNITURE_ROOM type;
    size_t width, height;
    int angle;
    QPoint center;
    QString name;

protected:
    void accept() override;

};

#endif // ADDFURNITUREROOMDIALOG_H
