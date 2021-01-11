#include "coordinate_fill.h"
#include <QDebug>
coordinate_fill::coordinate_fill(QWidget *parent) : QWidget(parent)
{
    this->resize(800,800);//组件大小
}
//绘图事件
void coordinate_fill::paintEvent(QPaintEvent *event)
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
    //绘制填充点
    if(this->active)
        for(int i=0;i<=this->maxy-this->miny;i++)
        {
            if(this->fillpoint[i].length()==1)//二维数组某行只有一个数据即该图形与扫描线只有一个交点，不用填充
                continue;
            for(int j=0;j<this->fillpoint[i].length();j+=2)
            {
                for(int k=this->fillpoint[i][j]+1;k<this->fillpoint[i][j+1];k++)
                {
                    painter.fillRect(390+k*20,390-(i+this->miny)*20,20,20,QColor(0,0,255));
                }
            }
        }
    //绘制封闭图形
    if(!this->point.empty())
    {
        for(int i=0;i<this->point.length();i++)
        {
            painter.fillRect(390+point[i]->x()*20,390-point[i]->y()*20,20,20,QColor(255,0,0));
        }
    }
    //绘制端点
    if(!this->endpoint.empty())
    {
        for(int i=0;i<this->endpoint.length();i++)
        {
            painter.fillRect(390+endpoint[i]->x()*20,390-endpoint[i]->y()*20,20,20,QColor(255,0,0));
        }
    }
}
//计算封闭图形边坐标
void coordinate_fill::edge()
{
    this->point.clear();
    //将端点集内相邻的两点作为起点终点，根据bresenham算法计算直线坐标
    for(int i=0;i<this->endpoint.length();i++)
    {
        int j=(i+1)%this->endpoint.length();
        int dx=qAbs(endpoint[j]->x()-endpoint[i]->x());
        int dy=qAbs(endpoint[j]->y()-endpoint[i]->y());
        int sx=endpoint[i]->x()<endpoint[j]->x()?1:-1;
        int sy=endpoint[i]->y()<endpoint[j]->y()?1:-1;
        int err=(dx>dy?dx:-dy)/2,e2;

        int tempx=endpoint[i]->x();
        int tempy=endpoint[i]->y();
        for(;;)
        {
            QPoint *temp=new QPoint(tempx,tempy);
            point.append(temp);
           if(temp->x()==endpoint[j]->x()&&temp->y()==endpoint[j]->y())
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
    }
    //更新坐标系
    update();
}
//填充
void coordinate_fill::fill()
{
    this->isfill=true;
    //计算填充坐标
   this->central();
    update();
}
//清空功能
void coordinate_fill::empty()
{
    //清空所有集合
    this->endpoint.clear();
    this->point.clear();
    this->fillpoint.clear();
    this->active=0;
    this->isfill=false;
    //更新坐标系
    update();
}
//计算填充坐标
void coordinate_fill::central()
{
    this->fillpoint.clear();
    //获取最大最小纵坐标
    this->miny=this->endpoint[0]->y();
    this->maxy=this->endpoint[0]->y();
    for(int i=1;i<this->endpoint.length();i++)
    {
        if(this->endpoint[i]->y()<miny)
            miny=this->endpoint[i]->y();
        if(this->endpoint[i]->y()>maxy)
            maxy=this->endpoint[i]->y();
    }
    //设置交点坐标集行数
    this->fillpoint.resize(this->maxy-this->miny+1);
    //从最小纵坐标开始扫描到最大纵坐标
    for(int i=miny;i<=maxy;i++)
    {
        //扫描线与每一条线进行求交
        for(int j=0;j<this->endpoint.length();j++)
        {
            //i表示扫描线纵坐标
            //j k表示直线起点和终点在端点集内位置
            int k=(j+1)%this->endpoint.length();
            //如果起点和终点的纵坐标都大于或小于扫描线坐标，则跳过该直线
            if((this->endpoint[j]->y()>i&&this->endpoint[k]->y()>i)||(this->endpoint[j]->y()<i&&this->endpoint[k]->y()<i))
                continue;
            else if(this->endpoint[j]->y()==i)//扫描线过起点
            {
                //计算以该点为端点的两条直线的另一端点与扫描线的关系
                int num1=(this->endpoint[(j+1)%this->endpoint.length()]->y()>i)+(this->endpoint[(j-1+this->endpoint.length())%this->endpoint.length()]->y()>i);
                int num2=(this->endpoint[(j+1)%this->endpoint.length()]->y()<i)+(this->endpoint[(j-1+this->endpoint.length())%this->endpoint.length()]->y()<i);
                if(num1==2||num2==2)//两端点全在扫描线上方或下方
                {
                    //两个交点 全是该点
                    //将横坐标加入填充横坐标集
                    this->fillpoint[i-miny].append(this->endpoint[j]->x());
                    this->fillpoint[i-miny].append(this->endpoint[j]->x());
                }
                else
                {
                    //一个端点 是该点
                    this->fillpoint[i-miny].append(this->endpoint[j]->x());
                }
            }
            else if(this->endpoint[k]->y()==i)
            {
                int num1=(this->endpoint[(k+1)%this->endpoint.length()]->y()>i)+(this->endpoint[(k-1+this->endpoint.length())%this->endpoint.length()]->y()>i);
                int num2=(this->endpoint[(k+1)%this->endpoint.length()]->y()<i)+(this->endpoint[(k-1+this->endpoint.length())%this->endpoint.length()]->y()<i);
                if(num1==2||num2==2)
                {
                    this->fillpoint[i-miny].append(this->endpoint[k]->x());
                    this->fillpoint[i-miny].append(this->endpoint[k]->x());
                }
                else
                {
                    this->fillpoint[i-miny].append(this->endpoint[k]->x());
                }
            }
            else//扫描线与直线相交且交点不是端点
            {
                //计算横坐标
                int x=findpointx(j,i);
                this->fillpoint[i-miny].append(x);
            }
        }
    }
    for(int i=0;i<this->fillpoint.count();i++)
    {
        //将每一行的数据从小到大排序
        std::sort(this->fillpoint[i].begin(),this->fillpoint[i].end());
        //移除重复元素
        this->fillpoint[i].erase(std::unique(this->fillpoint[i].begin(),this->fillpoint[i].end()),this->fillpoint[i].end());
    }
    //可以进行填充
    this->active=1;
}
//计算扫描线与图形边相交的交点横坐标
int coordinate_fill::findpointx(int i, int y)
{
    //通过bresenham算法计算横坐标
    int j=(i+1)%this->endpoint.length();
    int dx=qAbs(endpoint[j]->x()-endpoint[i]->x());
    int dy=qAbs(endpoint[j]->y()-endpoint[i]->y());
    int sx=endpoint[i]->x()<endpoint[j]->x()?1:-1;
    int sy=endpoint[i]->y()<endpoint[j]->y()?1:-1;
    int err=(dx>dy?dx:-dy)/2,e2;

    int tempx=endpoint[i]->x();
    int tempy=endpoint[i]->y();
    for(;;)
    {
       if(tempy==y)
            return tempx;
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
}

void coordinate_fill::transform(int translate_x, int translate_y, int angle, int sym)
{
    for(int i=0;i<this->endpoint.length();i++)
    {
        //平移
        this->endpoint[i]->setX(this->endpoint[i]->x()+translate_x);
        this->endpoint[i]->setY(this->endpoint[i]->y()+translate_y);
        //旋转
        int x=this->endpoint[i]->x()*cos(angle*PI/180)-this->endpoint[i]->y()*sin(angle*PI/180);
        int y=this->endpoint[i]->x()*sin(angle*PI/180)+this->endpoint[i]->y()*cos(angle*PI/180);
        this->endpoint[i]->setX(x);
        this->endpoint[i]->setY(y);
        //对称
        if(sym==1)
            this->endpoint[i]->setY(-this->endpoint[i]->y());
        else if(sym==2)
            this->endpoint[i]->setX(-this->endpoint[i]->x());
    }
    edge();
    if(isfill)
        central();
    //update();
}


