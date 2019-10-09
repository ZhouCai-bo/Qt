#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QWidget>
#include <QPushButton>


class subwindow : public QWidget
{
    Q_OBJECT
public:
    explicit subwindow(QWidget *parent = nullptr);

    void sendSlot();
    void change_slot1();
    void sendSlot_para();

private:
    QPushButton b;
    QPushButton b_para;

//信号声明关键字，信号和槽函数没有返回值，但可以有参数
//信号类似于函数的声明，只需声明，无需定义
signals:
    void change_singnal();
    void change_singnal(int, QString);

public slots:
};

#endif // SUBWINDOW_H
