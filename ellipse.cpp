#include "ellipse.h"
#include <QDebug>
Ellipse::Ellipse(QWidget *parent) : QWidget(parent)
{
    this->setWid();
    this->resize(800,800);//组件大小
}

void Ellipse::setWid()//设置组件
{
    //设置标签位置
    this->label[0]=new QLabel("中心椭圆",this);
    this->label[0]->move(10,10);
    this->label[1]=new QLabel("半长轴长",this);
    this->label[2]=new QLabel("半短轴长",this);
    //中心
    this->label[3]=new QLabel("横坐标",this);
    this->label[4]=new QLabel("纵坐标",this);
    this->pointx=new QSpinBox(this);
    this->pointx->setRange(-19,19);
    this->pointx->setReadOnly(true);
    this->pointy=new QSpinBox(this);
    this->pointy->setRange(-19,19);
    this->pointy->setReadOnly(true);
    this->gridlay[3]=new QGridLayout(this);
    this->gridlay[3]->addWidget(this->label[3],0,0);
    this->gridlay[3]->addWidget(this->pointx,0,1);
    this->gridlay[3]->addWidget(this->label[4],1,0);
    this->gridlay[3]->addWidget(this->pointy,1,1);
    this->box[3]=new QGroupBox("中心点",this);
    this->box[3]->setLayout(this->gridlay[3]);
    //设置半长轴长，半短轴长数据框
    this->halflong=new QSpinBox(this);
    this->halfshort=new QSpinBox(this);
    this->gridlay[0]=new QGridLayout(this);
    this->gridlay[0]->addWidget(this->label[1],0,0);
    this->gridlay[0]->addWidget(this->halflong,0,1);
    this->gridlay[0]->addWidget(this->label[2],1,0);
    this->gridlay[0]->addWidget(this->halfshort,1,1);
    this->box[0]=new QGroupBox("长短轴",this);
    this->box[0]->setLayout(this->gridlay[0]);
    //this->box[0]->move(10,50);
    //焦点位置单选
    this->posx=new QRadioButton("X轴",this);
    this->posy=new QRadioButton("Y轴",this);
    this->gridlay[1]=new QGridLayout(this);
    this->gridlay[1]->addWidget(this->posx,0,0);
    this->gridlay[1]->addWidget(this->posy,0,1);
    this->group=new QButtonGroup(this);
    this->group->addButton(this->posx,0);
    this->group->addButton(this->posy,1);
    this->posx->setChecked(true);
    this->box[1]=new QGroupBox("焦点位置",this);
    this->box[1]->setLayout(this->gridlay[1]);
    //this->box[1]->move(10,200);
    this->gridlay[2]=new QGridLayout(this);
    this->gridlay[2]->addWidget(this->box[3],0,0);
    this->gridlay[2]->addWidget(this->box[0],1,0);
    this->gridlay[2]->addWidget(this->box[1],2,0);
    this->box[2]=new QGroupBox("椭圆数据",this);
    this->box[2]->setLayout(this->gridlay[2]);
    this->box[2]->move(10,50);
    //变换
    this->trans=new Trans(this);
    this->trans->move(0,350);
    //设置绘画坐标系位置
    this->coo=new Coordinate_paint(this);
    this->coo->move(200,0);
}

void Ellipse::paint()//绘制功能
{
    this->ispaint=true;
    //获取数据
    int a=this->halflong->text().toInt();
    int b=this->halfshort->text().toInt();
    //数据有误
    if(a<b)
    {
        QMessageBox::warning(NULL,"数据错误","椭圆半长轴长不小于短半轴长!");
    }
    else
    {
        QPoint *point=new QPoint(this->pointx->text().toInt(),this->pointy->text().toInt());
        this->coo->staend.append(point);
        //根据焦点位置调用绘制坐标系绘制中心椭圆函数
        if(this->group->checkedId()==0)
        {
            this->coo->radius.append(a);
            this->coo->radius.append(b);
        }
        else
        {
            this->coo->radius.append(b);
            this->coo->radius.append(a);
        }
        this->coo->paintEllipse();
    }
}
void Ellipse::empty()//清空功能
{
    this->ispaint=false;
    this->active=0;
    //数据清零
    this->pointx->setValue(0);
    this->pointy->setValue(0);
    this->halflong->setValue(0);
    this->halfshort->setValue(0);
    //单选变为默认值
    this->posx->setChecked(true);
    //调用绘制坐标系empty函数
    this->coo->empty();
    this->trans->empty();
}

void Ellipse::mousePressEvent(QMouseEvent *event)
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

void Ellipse::transform()
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
    this->coo->transform(translate_x,translate_y,angle,sym_type,3);
}
