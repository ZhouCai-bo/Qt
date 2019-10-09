#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "subwindow.h"
#include <QString>
#include <string>
#include <QDebug>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void TestSlot();
    QPushButton b;
    QPushButton b1;
    subwindow subwin;

public slots:
    void change_slot();
    void change_slot1();
    void para_slot(int, QString);
};
#endif // MAINWINDOW_H
