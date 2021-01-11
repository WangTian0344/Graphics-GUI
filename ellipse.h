#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QGroupBox>
#include <QGridLayout>
#include <QButtonGroup>
#include <QRadioButton>
#include <QMessageBox>
#include <QThread>
#include <QMouseEvent>
#include <coordinate_paint.h>
#include "trans.h"
/*
 * 中心椭圆组件类
 * 包含绘制坐标系类coordinate_paint的实例对象作为坐标系
 */
class Ellipse : public QWidget
{
    Q_OBJECT
public:
    explicit Ellipse(QWidget *parent = nullptr);
    void setWid();//设置组件
    void paint();//绘画功能
    void empty();//清空功能
    void mousePressEvent(QMouseEvent *event);
    void transform();
    QLabel *label[5];
    QSpinBox *halflong,*halfshort;//半长轴长 半短轴长
    QSpinBox *pointx,*pointy;
    QGroupBox *box[4];
    QGridLayout *gridlay[4];
    QRadioButton *posx,*posy;//焦点位置
    Coordinate_paint *coo;//绘画坐标系
    QButtonGroup *group;//单选组
    Trans *trans;
    bool ispaint=false;
    int active=0;
};

#endif // ELLIPSE_H
