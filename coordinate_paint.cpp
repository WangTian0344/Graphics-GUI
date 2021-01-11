#include "coordinate_paint.h"
#include <QDebug>
Coordinate_paint::Coordinate_paint(QWidget *parent) : QWidget(parent)
{
    this->resize(800,800);//组件大小
}

void Coordinate_paint::paintEvent(QPaintEvent *event)
{
    //初始化painter
    QPainter painter(this);
    //绘制坐标系
    painter.setPen(QPen(QColor(0,0,0)));
    for(int i=1;i<=40;i++)
    {
        painter.drawLine(0,i*20,800,i*20);
        painter.drawLine(i*20,0,i*20,800);
    }
    //突出坐标轴
    painter.setPen(QPen(QColor(0,255,0),5));
    painter.drawLine(0,400,800,400);
    painter.drawLine(400,0,400,800);
    //绘制直线端点
    if(!this->staend.empty())
        for(int i=0;i<this->staend.length();i++)
            painter.fillRect(390+staend[i]->x()*20,390-staend[i]->y()*20,20,20,QColor(255,0,0));
    //绘制图案
    if(!point.isEmpty())
    {
        for(int i=0;i<point.length();i++)
        {
            painter.fillRect(390+point[i]->x()*20,390-point[i]->y()*20,20,20,QColor(255,0,0));
        }
    }
}

//根据dda算法画直线
void Coordinate_paint::paintDDA()
{
    //清空点集
    point.clear();
    QPoint *point1=this->staend[0];
    QPoint *point2=this->staend[1];
    //计算图案点集，更新坐标系
    int dx=point2->x()-point1->x();
    int dy=point2->y()-point1->y();
    int step=qAbs(dx)>qAbs(dy)?qAbs(dx):qAbs(dy);
    double deltax=1.0*dx/step;
    double deltay=1.0*dy/step;
    double xx=point1->x();
    double yy=point1->y();
    for(int i=0;i<=step;i++)
    {
        QPoint *temp=new QPoint(qRound(xx),qRound(yy));
        point.append(temp);
        xx+=deltax;
        yy+=deltay;
    }
    update();
}
//根据bresneham算法画直线
void Coordinate_paint::paintBres()
{
    QPoint *point1=this->staend[0];
    QPoint *point2=this->staend[1];
    //清空点集
    point.clear();
    //计算图案点集，更新坐标系
    int dx=qAbs(point2->x()-point1->x());
    int dy=qAbs(point2->y()-point1->y());
    int sx=point1->x()<point2->x()?1:-1;
    int sy=point1->y()<point2->y()?1:-1;
    int err=(dx>dy?dx:-dy)/2,e2;

    int tempx=point1->x();
    int tempy=point1->y();
    for(;;)
    {
        QPoint *temp=new QPoint(tempx,tempy);
        point.append(temp);
        if(temp->x()==point2->x()&&temp->y()==point2->y())
            break;
        e2=err;
        if(e2>-dx)
        {
            err-=dy;
            tempx+=sx;
        }
        if(e2<dy)
        {
            err+=dx;
            tempy+=sy;
        }
    }
    update();
}
//画中心圆
void Coordinate_paint::paintCircle()
{
    //清空点集
    point.clear();
    int r=this->radius[0];
    int x0=this->staend[0]->x();
    int y0=this->staend[0]->y();
    //qDebug()<<r<<x0<<y0;
    //计算图案点集，更新坐标系
    int xx=0,yy=r;
    double p=1.25-r;
    while(xx<=yy)
    {
        QPoint *mp=new QPoint(xx+x0,yy+y0);
        point.append(mp);
        if(p<0)
        {
            p=p+2*(xx+1)+1;
            xx+=1;
        }
        else
        {
            p=p+2*(xx+1)+1-2*(yy-1);
            xx+=1;
            yy-=1;
        }
    }
    //根据y=x进行对称
    for(int i=point.size()-1;i>=0;i--)
    {
        if(point[i]->x()-x0==point[i]->y()-y0)
            continue;
        QPoint *mp=new QPoint(point[i]->y()-y0+x0,point[i]->x()-x0+y0);
        point.append(mp);
    }
    //根据x轴进行对称
    for(int i=point.size()-1;i>=0;i--)
    {
        if(point[i]->y()-y0==0)
            continue;
        QPoint *mp=new QPoint(point[i]->x(),2*y0-point[i]->y());
        point.append(mp);
    }
    //根据y轴进行对称
    for(int i=point.size()-1;i>=0;i--)
    {
        if(point[i]->x()-x0==0)
            continue;
        QPoint *mp=new QPoint(2*x0-point[i]->x(),point[i]->y());
        point.append(mp);
    }
    update();
}
//画中心椭圆
void Coordinate_paint::paintEllipse()
{
    //清空点集
    point.clear();
    int a=this->radius[0];
    int b=this->radius[1];
    int x0=this->staend[0]->x();
    int y0=this->staend[0]->y();
    qDebug()<<x0<<y0<<a<<b;
    //计算图案点集，更新坐标系
    int x2=a*a,y2=b*b;
    int twox2=2*x2,twoy2=2*y2;
    int p,x=0,y=b;
    int px=0,py=twox2*y;
    QPoint *mp1=new QPoint(x+x0,y+y0);
    point.append(mp1);
    p=qRound(y2-(x2*b)+(0.25*x2));
    while(px<py)
    {
        x++;
        px+=twoy2;
        if(p<0)
        {
            p+=y2+px;
        }
        else
        {
            y--;
            py-=twox2;
            p+=y2+px-py;
        }
        QPoint *mp2=new QPoint(x+x0,y+y0);
        point.append(mp2);
    }
    p=qRound(y2*(x+0.5)*(x+0.5)+x2*(y-1)*(y-1)-x2*y2);
    while(y>0)
    {
        y--;
        py-=twox2;
        if(p>0)
        {
            p+=x2-py;
        }
        else
        {
            x++;
            px+=twoy2;
            p+=x2-py+px;
        }
        QPoint *mp3=new QPoint(x+x0,y+y0);
        point.append(mp3);
    }
    //根据x轴进行对称
    for(int i=point.size()-1;i>=0;i--)
    {
        if(point[i]->y()-y0==0)
            continue;
        QPoint *mp=new QPoint(point[i]->x(),2*y0-point[i]->y());
        point.append(mp);
    }
    //根据y轴进行对称
    for(int i=point.size()-1;i>=0;i--)
    {
        if(point[i]->x()-x0==0)
            continue;
        QPoint *mp=new QPoint(2*x0-point[i]->x(),point[i]->y());
        point.append(mp);
    }
    update();
}
//清空功能
void Coordinate_paint::empty()
{
    //清空所有点集
    this->point.clear();
    this->staend.clear();
    this->radius.clear();
    //更新坐标系
    update();
}

void Coordinate_paint::transform(int translate_x, int translate_y, int angle, int sym, int type)
{
    for(int i=0;i<this->staend.length();i++)
    {
        //平移
        this->staend[i]->setX(this->staend[i]->x()+translate_x);
        this->staend[i]->setY(this->staend[i]->y()+translate_y);
        //旋转
        int x=this->staend[i]->x()*cos(angle*PI/180)-this->staend[i]->y()*sin(angle*PI/180);
        int y=this->staend[i]->x()*sin(angle*PI/180)+this->staend[i]->y()*cos(angle*PI/180);
        this->staend[i]->setX(x);
        this->staend[i]->setY(y);
        //对称
        if(sym==1)
            this->staend[i]->setY(-this->staend[i]->y());
        else if(sym==2)
            this->staend[i]->setX(-this->staend[i]->x());
    }
    switch (type) {
    case 0:
        paintDDA();
        break;
    case 1:
        paintBres();
        break;
    case 2:
        paintCircle();
        break;
    case 3:
        paintEllipse();
        break;
    case 4:
        break;
    }

}

