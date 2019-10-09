#include "subwindow.h"

subwindow::subwindow(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("子窗口");
    this->setFixedSize(400,250);

    b.move(100,60);
    b.setParent(this);
    b.setText("切换");
    b.setFixedSize(100,40);
    connect(&b, &QPushButton::pressed, this, &subwindow::sendSlot);

    b_para.setParent(this);
    b_para.setText("带参数信号");
    b_para.setFixedSize(100,40);
    connect(&b_para, &QPushButton::pressed, this, &subwindow::sendSlot_para);
}

void subwindow::sendSlot()
{
    //发送信号
    emit change_singnal();
}

void subwindow::sendSlot_para()
{
    emit change_singnal(123, "with singal!");
}
