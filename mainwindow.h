#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QLabel>
#include <QStackedWidget>
#include <QPoint>
#include <QMessageBox>
#include "dda.h"
#include "bresenham.h"
#include "circle.h"
#include "ellipse.h"
#include "fill.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setMenu();//设置菜单栏
    void setMenuAction();//设置菜单功能
    void setToolbar();//设置工具栏
    void setCentral();//设置中心区域
    void paint();//绘制功能
    void empty();//清空功能
    void transform();


    QMenuBar *menubar;//菜单栏
    QMenu *menu[5];//菜单
    QAction *action[9];//菜单功能
    QToolBar *toolbar;//工具栏
    QStackedWidget *centralstack;//中央栈组件
    DDA *dda;//dda算法实现组件
    Bresenham *bres;//bresenham算法实现组件
    Circle *cir;//中心圆实现组件
    Ellipse *ell;//中心椭圆实现组件
    Fill *fill;//扫描填充实现组件


};

#endif // MAINWINDOW_H
