#ifndef COORDINATE_FILL_H
#define COORDINATE_FILL_H

#include <QWidget>
#include <QPainter>
#include <QVector>
#include <algorithm>
#define PI 3.1415926
/*
 * 填充坐标系类
 * 实现封闭图形绘制和填充
 */
class coordinate_fill : public QWidget
{
    Q_OBJECT
public:
    explicit coordinate_fill(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);//绘画事件
    void edge();//计算封闭图形边坐标
    void fill();//填充
    void empty();//清空功能
    void central();//计算填充坐标
    int findpointx(int i,int y);//计算扫描线与图形边相交的交点横坐标
    void transform(int translate_x,int translate_y,int angle,int sym);

    QVector<QPoint*> endpoint;//端点集
    QVector<QPoint*> point;//图形边坐标集
    //填充横坐标集
    //二维数组
    //行数表示从最小纵坐标开始向上扫描的扫描线的纵坐标与最小纵坐标的差值
    //每行内存储扫描线与图形边交点的横坐标
    //交点横坐标即二维数组中存储的数
    //交点纵坐标是行数加最小纵坐标
    QVector<QVector<int> > fillpoint;
    int miny,maxy;//图形最大最小纵坐标
    int active=0;//0不填充1填充
    int length;//动态绘制参数
    bool isfill=false;
};

#endif // COORDINATE_FILL_H
