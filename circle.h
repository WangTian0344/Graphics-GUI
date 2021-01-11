#ifndef CIRCLE_H
#define CIRCLE_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QThread>
#include <QMouseEvent>
#include <QGridLayout>
#include <QGroupBox>
#include <coordinate_paint.h>
#include "trans.h"
/*
 * 中心圆组件类
 * 通过点击坐标系或在数值框中输入获取半径
 * 包含绘制坐标系类coordinate_paint的实例对象作为坐标系
 */
class Circle : public QWidget
{
    Q_OBJECT
public:
    explicit Circle(QWidget *parent = nullptr);
    void setWid();//设置组件
    void paint();//绘制功能
    void empty();//清空功能
    void mousePressEvent(QMouseEvent *event);//鼠标点击坐标系获取点到原点距离作为半径
    void transform();

    QLabel *label[4];
    QSpinBox *r;//半径
    QSpinBox *pointx,*pointy;
    Coordinate_paint *coo;//绘画坐标系
    QGridLayout *gridlay[3];
    QGroupBox *box[3];
    Trans *trans;
    bool ispaint=false;
    int active=0;
};

#endif // CIRCLE_H
