#ifndef CHANGEWALLFURNITUREDIALOG_H
#define CHANGEWALLFURNITUREDIALOG_H

#include <QDialog>

namespace Ui {
    class changeWallFurnitureDialog;
}

class changeWallFurnitureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit changeWallFurnitureDialog(QWidget *parent = nullptr);
    ~changeWallFurnitureDialog();

private:
    Ui::changeWallFurnitureDialog *ui;
};

#endif // CHANGEWALLFURNITUREDIALOG_H
