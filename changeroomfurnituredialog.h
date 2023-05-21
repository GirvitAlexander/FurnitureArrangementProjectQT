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
    explicit changeRoomFurnitureDialog(QWidget *parent = nullptr);
    ~changeRoomFurnitureDialog();

private:
    Ui::changeRoomFurnitureDialog *ui;
};

#endif // CHANGEROOMFURNITUREDIALOG_H
