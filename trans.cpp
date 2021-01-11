#include "trans.h"

Trans::Trans(QWidget *parent) : QWidget(parent)
{
    setWid();
    this->resize(200,400);
}

void Trans::setWid()
{
    //平移
    this->label[0]=new QLabel("X轴方向",this);
    this->label[1]=new QLabel("Y轴方向",this);
    this->translate_x=new QSpinBox(this);
    this->translate_x->setRange(-19,19);
    this->translate_y=new QSpinBox(this);
    this->translate_y->setRange(-19,19);
    this->gridlay[0]=new QGridLayout(this);
    this->gridlay[0]->addWidget(this->label[0],0,0);
    this->gridlay[0]->addWidget(this->translate_x,0,1);
    this->gridlay[0]->addWidget(this->label[1],1,0);
    this->gridlay[0]->addWidget(this->translate_y,1,1);
    this->box[0]=new QGroupBox("平移",this);
    this->box[0]->setLayout(this->gridlay[0]);
    //this->box[0]->move(10,10);

    //旋转
    this->label[2]=new QLabel("旋转角(度)",this);
    this->angle=new QSpinBox(this);
    this->angle->setRange(-360,360);
    this->gridlay[1]=new QGridLayout(this);
    this->gridlay[1]->addWidget(this->label[2],0,0);
    this->gridlay[1]->addWidget(this->angle,0,1);
    this->box[1]=new QGroupBox("旋转",this);
    this->box[1]->setLayout(this->gridlay[1]);
    //this->box[1]->move(10,150);
    //对称
    this->sym_x=new QRadioButton("X轴",this);
    this->sym_y=new QRadioButton("Y轴",this);
    this->btnbox=new QButtonGroup(this);
    this->btnbox->addButton(this->sym_x,0);
    this->btnbox->addButton(this->sym_y,1);
    this->gridlay[2]=new QGridLayout(this);
    this->gridlay[2]->addWidget(this->sym_x,0,0);
    this->gridlay[2]->addWidget(this->sym_y,0,1);
    this->box[2]=new QGroupBox("对称",this);
    this->box[2]->setLayout(this->gridlay[2]);
    //this->box[2]->move(10,250);

    this->gridlay[3]=new QGridLayout(this);
    this->gridlay[3]->addWidget(this->box[0],0,0);
    this->gridlay[3]->addWidget(this->box[1],1,0);
    this->gridlay[3]->addWidget(this->box[2],2,0);
    this->box[3]=new QGroupBox("变换",this);
    this->box[3]->setLayout(this->gridlay[3]);
    this->box[3]->move(0,0);

}

void Trans::empty()
{
    this->translate_x->setValue(0);
    this->translate_y->setValue(0);
    this->angle->setValue(0);
    this->sym_x->setCheckable(false);
    this->sym_x->setCheckable(true);
    this->sym_y->setCheckable(false);
    this->sym_y->setCheckable(true);
    update();
}
