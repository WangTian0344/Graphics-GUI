#include "circle.h"
#include <QDebug>
Circle::Circle(QWidget *parent) : QWidget(parent)
{
    this->setWid();
    this->resize(800,800);//组件大小
}

void Circle::setWid()//设置组件
{
    //设置标签位置
    this->label[0]=new QLabel("中心圆",this);
    this->label[0]->move(10,10);

    this->label[1]=new QLabel("横坐标",this);
    this->label[2]=new QLabel("纵坐标",this);
    this->pointx=new QSpinBox(this);
    this->pointx->setRange(-19,19);
    this->pointx->setReadOnly(true);
    this->pointy=new QSpinBox(this);
    this->pointy->setRange(-19,19);
    this->pointy->setReadOnly(true);
    this->gridlay[0]=new QGridLayout(this);
    this->gridlay[0]->addWidget(this->label[1],0,0);
    this->gridlay[0]->addWidget(this->pointx,0,1);
    this->gridlay[0]->addWidget(this->label[2],1,0);
    this->gridlay[0]->addWidget(this->pointy,1,1);
    this->box[0]=new QGroupBox("圆心",this);
    this->box[0]->setLayout(this->gridlay[0]);

    this->label[3]=new QLabel("半径",this);
    this->r=new QSpinBox(this);
    this->r->setRange(0,19);
    this->gridlay[1]=new QGridLayout(this);
    this->gridlay[1]->addWidget(this->label[3],0,0);
    this->gridlay[1]->addWidget(this->r,0,1);
    this->box[1]=new QGroupBox("圆数据",this);
    this->box[1]->setLayout(this->gridlay[1]);

    this->gridlay[2]=new QGridLayout(this);
    this->gridlay[2]->addWidget(this->box[0],0,0);
    this->gridlay[2]->addWidget(this->box[1],1,0);
    this->box[2]=new QGroupBox("圆数据",this);
    this->box[2]->setLayout(this->gridlay[2]);
    this->box[2]->move(20,50);
    //变换
    this->trans=new Trans(this);
    this->trans->move(0,300);
    //设置绘画坐标系位置
    this->coo=new Coordinate_paint(this);
    this->coo->move(200,0);
}

void Circle::paint()//绘画功能
{
    this->ispaint=true;
    //调用绘画坐标系中心圆函数
    this->coo->radius.append(this->r->text().toInt());
    QPoint *point=new QPoint(this->pointx->text().toInt(),this->pointy->text().toInt());
    this->coo->staend.append(point);
    this->coo->paintCircle();
}

void Circle::empty()//清空功能
{
    //半径归零
    this->r->setValue(0);
    this->pointx->setValue(0);
    this->pointy->setValue(0);
    this->ispaint=false;
    this->active=0;
    //调用绘画坐标系empty函数
    this->coo->empty();
    this->trans->empty();
}

//鼠标点击坐标系获取点到原点距离作为半径
void Circle::mousePressEvent(QMouseEvent *event)
{
    //鼠标左键单击且点击坐标系内
    if(event->button()==Qt::LeftButton&&event->x()>=200&&active==0)
    {
        QPoint *po=new QPoint((event->x()-590)/20,(390-event->y())/20);
        this->pointx->setValue((event->x()-590)/20);
        this->pointy->setValue((390-event->y())/20);
        //加入绘制坐标系端点集
        this->coo->staend.append(po);
        active++;
    }
    update();
}

void Circle::transform()
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
    this->coo->transform(translate_x,translate_y,angle,sym_type,2);
}
