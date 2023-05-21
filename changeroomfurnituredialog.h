#ifndef CHANGEROOMFURNITUREDIALOG_H
#define CHANGEROOMFURNITUREDIALOG_H

#include <QDialog>

namespace Ui {
    class changeRoomFurnitureDialog;
}

class changeRoomFurnitureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit changeRoomFurnitureDialog(QPoint center_old, int angle_old, QWidget *parent = nullptr);
    ~changeRoomFurnitureDialog();

    int getAngle() {
        return angle;
    }

    QPoint getCenter() {
        return center;
    }

private:
    Ui::changeRoomFurnitureDialog *ui;
    int angle;
    QPoint center;
protected:
    void accept() override;
};

#endif // CHANGEROOMFURNITUREDIALOG_H
