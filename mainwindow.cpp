#include "mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //主窗口标题
    this->setWindowTitle("图形绘制与变换");
    this->setMenu();
    this->setMenuAction();
    this->setToolbar();
    this->setCentral();
    this->resize(1150,820);//主窗口大小
}

MainWindow::~MainWindow()
{

}

void MainWindow::setMenu()//设置菜单栏
{
    //添加菜单栏
    this->menubar=new QMenuBar(this);
    this->setMenuBar(menubar);
    //添加菜单
    this->menu[0]=new QMenu("控制",this);
    this->menu[1]=new QMenu("画线",this);
    this->menu[2]=new QMenu("画圆",this);
    this->menu[3]=new QMenu("画椭圆",this);
    this->menu[4]=new QMenu("填充",this);
    this->menubar->addMenu(this->menu[0]);
    this->menubar->addMenu(this->menu[1]);
    this->menubar->addMenu(this->menu[2]);
    this->menubar->addMenu(this->menu[3]);
    this->menubar->addMenu(this->menu[4]);
    //添加菜单功能
    this->action[0]=new QAction("绘制",this);
    this->action[1]=new QAction("清空",this);
    this->action[2]=new QAction("退出",this);
    this->action[3]=new QAction("DDA画线",this);
    this->action[4]=new QAction("Bresenham画线",this);
    this->action[5]=new QAction("中心圆",this);
    this->action[6]=new QAction("中心椭圆",this);
    this->action[7]=new QAction("扫描填充",this);
    this->action[8]=new QAction("变换",this);
    this->menu[0]->addAction(this->action[0]);
    this->menu[0]->addSeparator();
    this->menu[0]->addAction(this->action[8]);
    this->menu[0]->addSeparator();
    this->menu[0]->addAction(this->action[1]);
    this->menu[0]->addSeparator();
    this->menu[0]->addAction(this->action[2]);
    this->menu[1]->addAction(this->action[3]);
    this->menu[1]->addSeparator();
    this->menu[1]->addAction(this->action[4]);
    this->menu[2]->addAction(this->action[5]);
    this->menu[3]->addAction(this->action[6]);
    this->menu[4]->addAction(this->action[7]);
}

void MainWindow::setMenuAction()//设置菜单功能
{
    //菜单功能：点击action0，绘制图案
    connect(this->action[0],&QAction::triggered,this,&MainWindow::paint);
    //菜单功能：点击action1，清空图案
    connect(this->action[1],&QAction::triggered,this,&MainWindow::empty);
    //菜单功能：点击action2，退出
    connect(this->action[2],&QAction::triggered,this,&MainWindow::close);
    //菜单功能：点击action（3-7）切换中央控件
    //分别为dda bresenhan 圆 椭圆 填充
    connect(this->action[3],&QAction::triggered,[=](){
        this->centralstack->setCurrentIndex(0);
    });
    connect(this->action[4],&QAction::triggered,[=](){
        this->centralstack->setCurrentIndex(1);
    });
    connect(this->action[5],&QAction::triggered,[=](){
        this->centralstack->setCurrentIndex(2);
    });
    connect(this->action[6],&QAction::triggered,[=](){
        this->centralstack->setCurrentIndex(3);
    });
    connect(this->action[7],&QAction::triggered,[=](){
        this->centralstack->setCurrentIndex(4);
    });
    //变换
    connect(this->action[8],&QAction::triggered,this,&MainWindow::transform);
}

void MainWindow::setToolbar()//设置工具栏
{
    //添加工具栏
    this->toolbar=new QToolBar(this);
    this->toolbar->setFloatable(true);
    //工具栏添加功能
    this->toolbar->addAction(this->action[3]);
    this->toolbar->addAction(this->action[4]);
    this->toolbar->addAction(this->action[5]);
    this->toolbar->addAction(this->action[6]);
    this->toolbar->addAction(this->action[7]);
    this->toolbar->addSeparator();
    this->toolbar->addAction(this->action[0]);
    this->toolbar->addAction(this->action[8]);
    this->toolbar->addAction(this->action[1]);
    this->toolbar->addAction(this->action[2]);
    this->addToolBar(Qt::LeftToolBarArea,this->toolbar);
    //工具栏只能位于左侧和右侧
    this->toolbar->setAllowedAreas(Qt::LeftToolBarArea|Qt::RightToolBarArea);
}

void MainWindow::setCentral()//设置中心区域
{
    this->centralstack=new QStackedWidget(this);
    //dda组件
    this->dda=new DDA(this);
    this->centralstack->insertWidget(0,dda);
    //bresenham组件
    this->bres=new Bresenham(this);
    this->centralstack->insertWidget(1,bres);
    //中心圆组件
    this->cir=new Circle(this);
    this->centralstack->insertWidget(2,cir);
    //中心椭圆组件
   this->ell=new Ellipse(this);
    this->centralstack->insertWidget(3,ell);
    //扫描填充组件
    this->fill=new Fill(this);
    this->centralstack->insertWidget(4,fill);
    //设置中央组件
    this->setCentralWidget(this->centralstack);
}

void MainWindow::paint()//绘制功能
{
    //根据中心组件的页数，调用不同组件的paint函数
    if(this->centralstack->currentIndex()==0)
    {
        this->dda->paint();
    }
    else if(this->centralstack->currentIndex()==1)
    {
        this->bres->paint();
    }
    else if(this->centralstack->currentIndex()==2)
    {
        this->cir->paint();
    }
    else if(this->centralstack->currentIndex()==3)
    {
         this->ell->paint();
    }
    else
     {
        this->fill->paint();
    }
}

void MainWindow::empty()//清空功能
{
    //根据中心组件的页数，调用不同组件的empty函数
    if(this->centralstack->currentIndex()==0)
    {
        this->dda->empty();
    }
    else if(this->centralstack->currentIndex()==1)
    {
        this->bres->empty();
    }
    else if(this->centralstack->currentIndex()==2)
    {
        this->cir->empty();
    }
    else if(this->centralstack->currentIndex()==3)
    {
        this->ell->empty();
    }
    else
     {
        this->fill->empty();
    }
}

void MainWindow::transform()
{
    int index=this->centralstack->currentIndex();
    switch(index)
    {
        case 0:
            if(!this->dda->ispaint)
                QMessageBox::warning(NULL,"未找到图形","请先绘制图形!");
            else
                this->dda->transform();
            break;
        case 1:
            if(!this->bres->ispaint)
                QMessageBox::warning(NULL,"未找到图形","请先绘制图形!");
            else
                this->bres->transform();
            break;
        case 2:
            if(!this->cir->ispaint)
                QMessageBox::warning(NULL,"未找到图形","请先绘制图形!");
            else
                this->cir->transform();
            break;
        case 3:
            if(!this->ell->ispaint)
                QMessageBox::warning(NULL,"未找到图形","请先绘制图形!");
            else
                this->ell->transform();
            break;
        case 4:
            if(!this->fill->ispaint)
                QMessageBox::warning(NULL,"未找到图形","请先绘制图形!");
            else
                this->fill->transform();
            break;
    }
}



