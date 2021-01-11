#include "fill.h"
#include <QDebug>
Fill::Fill(QWidget *parent) : QWidget(parent)
{
    this->setWid();
    this->resize(800,800);//组件大小
}
//鼠标点击坐标系，坐标系显示点
void Fill::mousePressEvent(QMouseEvent *event)
{
    //鼠标左键单击且点击坐标系内
    if(event->button()==Qt::LeftButton&&event->x()>=200)
    {
        //将点击的点加入填充坐标系端点集
        QPoint *po=new QPoint((event->x()-590)/20,(390-event->y())/20);
        //限制端点个数
        if(this->endnum<5)
        {
            this->coo->endpoint.append(po);
            this->endnum++;
        }
    }
    update();
}

void Fill::setWid()//设置组件
{
    //标签位置
    this->label[0]=new QLabel("扫描填充",this);
    this->label[0]->move(10,10);
    //填充按钮位置
    this->btn=new QPushButton("填充",this);
    this->btn->move(50,150);
    //点击填充按钮调用fill函数
    connect(this->btn,&QPushButton::clicked,this,&Fill::fill);
    this->trans=new Trans(this);
    this->trans->move(0,300);
    //填充坐标系位置
    this->coo=new coordinate_fill(this);
    this->coo->move(200,0);
}

void Fill::paint()//绘制图形
{
    this->ispaint=true;
    //调用填充坐标系edge函数
    this->coo->edge();
}

void Fill::fill()//填充图形
{
    if(!this->ispaint)
        QMessageBox::warning(NULL,"未找到图形","请先绘制图形!");
    else
    //填充坐标系fill函数
        this->coo->fill();
}

void Fill::empty()//清空功能
{
    this->ispaint=false;
    //点击次数清零
    this->endnum=0;
    //填充坐标系empty函数
    this->coo->empty();
    this->trans->empty();
}

void Fill::transform()
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
    this->coo->transform(translate_x,translate_y,angle,sym_type);
}
