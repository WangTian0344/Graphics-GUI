#ifndef FILL_H
#define FILL_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QThread>
#include <QMessageBox>
#include "coordinate_fill.h"
#include "trans.h"
/*
 * 扫描填充算法组件
 * 在坐标系内点击若干点，根据点的顺序绘制封闭图形，并填充图形
 * 包含填充坐标系coordinate_fill的实例对象作为坐标系
 */
class Fill : public QWidget
{
    Q_OBJECT
public:
    explicit Fill(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);//鼠标点击坐标系，坐标系显示点
    void setWid();//设置组件
    void paint();//绘制图形
    void fill();//填充图形
    void empty();//清空功能
    void transform();
    QLabel *label[2];
    QPushButton *btn;//填充按钮
    coordinate_fill *coo;//填充坐标系
    Trans *trans;
    int endnum=0;//鼠标点击次数
    bool ispaint=false;
};

#endif // FILL_H
