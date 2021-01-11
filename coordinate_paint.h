#ifndef COORDINATE_PAINT_H
#define COORDINATE_PAINT_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QPoint>
#include <QVector>
#include <QTimer>
#include <QThread>
#include <qmath.h>
#define PI 3.1415926
/*
 * 绘画坐标系类
 * 实现直线、中心圆、中心椭圆绘制
 */
class Coordinate_paint : public QWidget
{
    Q_OBJECT
public:
    explicit Coordinate_paint(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);//绘图事件
    void paintDDA();//根据dda算法画直线
    void paintBres();//根据bresneham算法画直线
    void paintCircle();//画中心圆
    void paintEllipse();//画中心椭圆
    void empty();//清空功能
    void transform(int translate_x,int translate_y,int angle,int sym,int type);

    QVector<QPoint*> point;//点集
    QVector<QPoint*> staend;//端点集
    QVector<int> radius;
};

#endif // COORDINATE_PAINT_H
