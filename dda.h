#ifndef DDA_H
#define DDA_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QPoint>
#include <QThread>
#include <QMouseEvent>
#include <QGridLayout>
#include <QGroupBox>
#include "coordinate_paint.h"
#include "trans.h"
/*
 * dda算法组件类
 * 通过点击坐标系或在数值框中输入获取点坐标
 * 包含绘制坐标系类coordinate_paint的实例对象作为坐标系
*/
class DDA : public QWidget
{
    Q_OBJECT
public:
    explicit DDA(QWidget *parent = nullptr);
    void setWid();//设置组件
    void paint();//绘制功能
    void empty();//清空功能
    void mousePressEvent(QMouseEvent *event);//鼠标点击坐标系，坐标系显示点
    void transform();
    QLabel *label[5];
    QSpinBox *startx,*starty,*endx,*endy;//起始点横纵坐标
    QGridLayout *gridlay[3];
    QGroupBox *box[3];
    Coordinate_paint *coo;//绘画坐标系
    Trans *trans;
    int active=0;//鼠标点击次数
    bool ispaint=false;
};

#endif // DDA_H
