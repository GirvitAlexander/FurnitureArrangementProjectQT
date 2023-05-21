#include "conditionwidget.h"
#include "ui_conditionwidget.h"

#include <QFileDialog>
#include <QInputDialog>
#include <QLineEdit>

ConditionWidget::ConditionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConditionWidget)
{
    ui->setupUi(this);
    connect(ui->saveButton, &QPushButton::clicked,
                this, &ConditionWidget::clickedSaveButton);

    connect(ui->downloadButton, &QPushButton::clicked,
                this, &ConditionWidget::clickedLoadButton);
}

void ConditionWidget::clickedSaveButton() {
    QString fileName;
    bool ok;
    QString text = QInputDialog::getText(this, "Выгрузка комнаты", "Название файла:",
                                         QLineEdit::Normal,
                                         "example.txt", &ok);
    if (!ok || text.isEmpty()) {
        return;
    }
    fileName = "D:/QT/Kursach/MAIN/FurnitureArrangementProjectQT/Save/" + text;
    emit getSaveFile(fileName);
}

void ConditionWidget::clickedLoadButton() {
    QString fileName;

    QFileDialog dialog;

    if (dialog.exec() != QDialog::Accepted) {
        return;
    }

    fileName = dialog.selectedFiles()[0];
    qDebug() << fileName;
    emit getLoadFile(fileName);
}


ConditionWidget::~ConditionWidget()
{
    delete ui;
}
