#include "mainwindow.h"

//在指定父对象后，或者对象之间或间接继承于QObject
//在程序结束后会自动调用析构函数，不用使用delete释放new

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //按钮的作用只是调用槽函数
    this->setFixedSize(400,250);
    this->setWindowTitle("主窗口");
    b.setText("This is a test!");
    b.setParent(this);
    b.setMaximumSize(200,50);
    b.move(100,40);
    connect(&b, &QPushButton::pressed, this, &MainWindow::TestSlot);

    b1.move(100,120);
    b1.setText("切换");
    b1.setParent(this);
    b1.setFixedSize(100,40);
    connect(&b1, &QPushButton::pressed, this, &MainWindow::change_slot1);

    //由于相同的信号名会导致编译错，这里使用函数指针
    void (subwindow::*singnal_pure)()=&subwindow::change_singnal;
    void (subwindow::*singnal_para)(int, QString)=&subwindow::change_singnal;

    //处理子窗口信号
    connect(&subwin, singnal_pure, this, &MainWindow::change_slot);
    connect(&subwin, singnal_para, this, &MainWindow::para_slot);

    //信号连接,这种方式会将函数名转换为字符串，如果信号名拼写错误不会报错，这种方式在qt5之后不再推荐
    //connect(&subwin, SIGNAL(singnal_pure()), this, SLOT(change_slot()));
    //connect(&subwin, SIGNAL(singnal_para(int, QString)), this, SLOT(para_slot(int, QString)));

    QPushButton *b_ld = new QPushButton(this);
    b_ld->move(100,200);
    b_ld->setText("lambda表达式");
    b_ld->setFixedSize(120,40);
    connect(b_ld, &QPushButton::clicked,
            //lambda表达式是一种匿名函数
            //[]中的值
            //[=]会将当前作用域中的局部变量、类的成员函数以值传递的方式传进函数，但这种方式的传值是只读的
            //[=] mutable 可以修改函数中参数值
            //[this]将类的成员函数以值传递的方式传进函数
            //[&]将当前作用域中的局部变量以值传递的方式传进函数,但使用这种方式不要修改参数值，应为connect函数中包含引用，该函数体中正在操作地址
            //再次修改引用值会导致内存错误，如果需要修改值，建议使用[=] mutable
            //Lambda函数可以带参数，即是信号参数，clicked信号带有默认参数checked=false
            [=](bool isCheck) mutable
                {
                    b_ld->setText("lambda函数已调用");
                    qDebug() << isCheck;
                }

            );
}

void MainWindow::change_slot1()
{
    this->hide();
    subwin.show();
}


void MainWindow::change_slot()
{
    this->show();
    subwin.hide();
}

void MainWindow::para_slot(int a, QString str)
{
    //toUtf8()函数将QString转换为QByteArray字节数组，data()再将其转换为char*，这样将中文输出
    qDebug()<<str.toUtf8().data()<<" and num "<<a<<endl;
}

MainWindow::~MainWindow()
{
}

void MainWindow::TestSlot()
{
    QString str=b.text();
    if(!str.compare("This is a test!")||!str.compare("Hello Qt!"))
    {
        b.setText("Hello world!");
    }
    else
    {
        b.setText("Hello Qt!");
    }
}

