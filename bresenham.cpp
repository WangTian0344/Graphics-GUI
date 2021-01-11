#include "bresenham.h"
#include <QDebug>
Bresenham::Bresenham(QWidget *parent) : QWidget(parent)
{
    this->setWid();
    this->resize(800,800);//组件大小
}

void Bresenham::setWid()//设置组件
{
    this->label[0]=new QLabel("Bresenham画线算法",this);
    this->label[0]->move(10,10);
    //设置起点标签位置
    this->label[1]=new QLabel("X:",this);
    this->label[2]=new QLabel("Y:",this);
    //设置起点坐标输入组件位置和输入范围
    this->startx=new QSpinBox(this);
    this->startx->setRange(-19,19);
    this->startx->setReadOnly(true);
    this->starty=new QSpinBox(this);
    this->starty->setRange(-19,19);
    this->starty->setReadOnly(true);
    this->gridlay[0]=new QGridLayout(this);
    this->gridlay[0]->addWidget(this->label[1],0,0);
    this->gridlay[0]->addWidget(this->startx,0,1);
    this->gridlay[0]->addWidget(this->label[2],1,0);
    this->gridlay[0]->addWidget(this->starty,1,1);
    this->box[0]=new QGroupBox("起点坐标",this);
    this->box[0]->setLayout(this->gridlay[0]);
    //this->box[0]->move(10,50);
    //设置终点标签位置
    this->label[3]=new QLabel("X:",this);
    this->label[4]=new QLabel("Y:",this);
    //设置终点坐标输入组件位置和输入范围
    this->endx=new QSpinBox(this);
    this->endx->setRange(-19,19);
    this->endx->setReadOnly(true);
    this->endy=new QSpinBox(this);
    this->endy->setRange(-19,19);
    this->endy->setReadOnly(true);
    this->gridlay[1]=new QGridLayout(this);
    this->gridlay[1]->addWidget(this->label[3],0,0);
    this->gridlay[1]->addWidget(this->endx,0,1);
    this->gridlay[1]->addWidget(this->label[4],1,0);
    this->gridlay[1]->addWidget(this->endy,1,1);
    this->box[1]=new QGroupBox("终点坐标",this);
    this->box[1]->setLayout(this->gridlay[1]);
    //this->box[1]->move(10,180);
    this->gridlay[2]=new QGridLayout(this);
    this->gridlay[2]->addWidget(this->box[0],0,0);
    this->gridlay[2]->addWidget(this->box[1],1,0);
    this->box[2]=new QGroupBox("坐标",this);
    this->box[2]->setLayout(this->gridlay[2]);
    this->box[2]->move(30,50);
    //变换
    this->trans=new Trans(this);
    this->trans->move(0,300);
    //设置绘画坐标系位置
    this->coo=new Coordinate_paint(this);
    this->coo->move(200,0);
}

void Bresenham::paint()//绘制功能
{
    this->ispaint=true;
    //通过数值框数值初始化点
    QPoint *point1=new QPoint(this->startx->text().toInt(),this->starty->text().toInt());
    QPoint *point2=new QPoint(this->endx->text().toInt(),this->endy->text().toInt());
    this->coo->staend.append(point1);
    this->coo->staend.append(point2);
    //绘制坐标系Bresenham算法函数
    this->coo->paintBres();
}

void Bresenham::empty()//清空功能
{
    //鼠标点击数清零
    this->active=0;
    //起始点坐标全归零
    this->startx->setValue(0);
    this->starty->setValue(0);
    this->endx->setValue(0);
    this->endy->setValue(0);
    this->ispaint=false;
    //调用绘制坐标系empty函数
    this->coo->empty();
    this->trans->empty();
}

void Bresenham::mousePressEvent(QMouseEvent *event)
{
    //鼠标左键单击且点击位置为坐标系内
    if(event->button()==Qt::LeftButton&&event->x()>=200)
    {
        QPoint *po=new QPoint((event->x()-590)/20,(390-event->y())/20);
        //第一次点击既获取起点
        if(this->active==0)
        {
            //设置起点坐标
            this->startx->setValue((event->x()-590)/20);
            this->starty->setValue((390-event->y())/20);
            //加入绘制坐标系端点集
            this->coo->staend.append(po);
            this->active=1;
        }
        else if(this->active==1)
        {
            //设置终点坐标
            this->endx->setValue((event->x()-590)/20);
            this->endy->setValue((390-event->y())/20);
            //加入绘制坐标系端点集
            this->coo->staend.append(po);
            this->active=2;
        }
    }
    //更新坐标系
    update();
}

void Bresenham::transform()
{
    int translate_x=this->trans->translate_x->text().toInt();
    int translate_y=this->trans->translate_y->text().toInt();
    int angle=this->trans->angle->text().toInt();
    int sym_type=0;
    if(this->trans->btnbox->checkedId()==0)
        sym_type=1;
    else if(this->trans->btnbox->checkedId()==1)
        sym_type=2;
    this->trans->empty();
    this->coo->transform(translate_x,translate_y,angle,sym_type,1);
}
