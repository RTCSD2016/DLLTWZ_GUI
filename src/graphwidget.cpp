
#include <QDebug>
#include <QGraphicsScene>
#include <QWheelEvent>
#include <QRectF>
#include <math.h>
#include <QtCore/qmath.h>

#include "ball.h"
#include "frame.h"
#include "userhandle.h"

#include "graphwidget.h"
#include "gamewidget.h"

GraphWidget::GraphWidget(GameWidget *gamewidget) : timerId(0)
{
    game = gamewidget;


    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-300-10, -500-10, 600+20, 1000+20);
    setScene(scene);//
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    setResizeAnchor(AnchorViewCenter);
scene->setBackgroundBrush(QColor(255-20*2, 255-20*2, 255-20*2, 127));//

//添加终点图块

QGraphicsRectItem *uphole = new QGraphicsRectItem(0,0,100,40);
   uphole->setBrush(Qt::blue);
   uphole->setData(0,"hole1");
   scene->addItem(uphole);//上边
   uphole->setPos(-50,-500-20);

   QGraphicsRectItem *downhole = new QGraphicsRectItem(0,0,100,40);
   downhole->setBrush(Qt::yellow);
   downhole->setData(0,"hole2");
   scene->addItem(downhole);//下边
   downhole->setPos(-50,500-20);

//添加球
    ballmove  =new Ball(this);
    scene->addItem(ballmove);
    ballmove->setPos(0,0);

//添加标示线
//    Frame * LineFrame = new Frame(this,QRectF(-300,-5,600,10));
//    scene->addItem(LineFrame);
//    LineFrame->setPos(0,0);
    scene->addLine(QLineF(-300,0,300,0),QPen(QColor(Qt::red)));
    //scene->addEllipse();

//添加边框
    frameUp = new Frame(this,QRectF(-0,-0,300-50,20));
    scene->addItem(frameUp);
    frameUp->setPos(-300,-500);
   frameUp->setData(0,"up");//设置键值up

   Frame *up2 = new Frame(this,QRectF(-0,-0,300-50,20));
   scene->addItem(up2);
   up2->setPos(0+50,-500);
  up2->setData(0,"up");//设置键值up

    frameDown = new Frame(this,QRectF(0,0,300-50,20));
    scene->addItem(frameDown);
    frameDown->setPos(-300,+500-20);
   frameDown->setData(0,"down");//设置键值down

   Frame *down2 = new Frame(this,QRectF(0,0,300-50,20));
   scene->addItem(down2);
   down2->setPos(0+50,500-20);
  down2->setData(0,"down");//设置键值down

    frameLeft = new Frame(this,QRectF(-300,-500,20,1000));
    scene->addItem(frameLeft);
    frameLeft->setPos(0,0);
   frameLeft->setData(0,"left");//设置键值left

    frameRight = new Frame(this,QRectF(300-20,-500,20,1000));
    scene->addItem(frameRight);
    frameRight->setPos(0,0);
    frameRight->setData(0,"right");//设置键值right
    
    //添加游戏手柄

    userhandle  =new userHandle(this);
    scene->addItem(userhandle);
    userhandle->setPos(10,200);

    userhandle->setData(0,"userhandle");//设置键值userhandle


//    frame = new Frame(this);
//    scene->addItem(frame);
//    frame->setPos(0,0);


    // scale(qreal(0.8), qreal(0.8));
    setMinimumSize(600+50, 1000+60);
    setWindowTitle(tr("Elastic Nodes"));
//设置更新时间,(如果时间太长,也就是更新太慢，当speed太小时会导致更新比鼠标运动还要慢，出错)、

    timerId = startTimer(1000 / FRECUENCY);//设置更新的时间间隔 FRECUENCY = 100

}
void GraphWidget::timerEvent(QTimerEvent *event)
{
 Q_UNUSED(event);

//碰撞检测、速度更新
//ballmove->collidingItems();

//获取球和Handle的位置，【】相邻两次Handle的位置可以计算出Handle的速度
ballPosition = ballmove->pos();
HandlePosition  = userhandle->pos();
game->setPosition();

 QList<QGraphicsItem *>  collisions = ballmove->collidingItems();//获取所有碰撞的对象
 foreach (QGraphicsItem *item, collisions) 
 {
     //碰撞物体检测
     if(item->data(0).toString().contains("up")) // 如果碰到了上边的Frame; if collide with Right wall
     {
        ballmove->collisionCalcualte(Up) ;
     }
     if(item->data(0).toString().contains("down")) // 如果碰到了下边的Frame; if collide with Right wall
     {
        ballmove->collisionCalcualte(Down) ;
     }
     if(item->data(0).toString().contains("left")) // 如果碰到了左边的Frame; if collide with Right wall
     {
        ballmove->collisionCalcualte(Left) ;
     }
     if(item->data(0).toString().contains("right")) // 如果碰到了右边的Frame; if collide with Right wall
     {
        ballmove->collisionCalcualte(Right) ;
     }
     if(item->data(0).toString().contains("userhandle")) // 如果碰到了userhandle; if collide with Right wall
     {

         //将嵌入到Handle的 ball退出来,【】但是可能把球推出去了;

//        {
//            qreal angle=0;
//            QPointF point = HandlePosition;

////            qDebug()<<point;
//            point-=ballPosition;
//            qreal collisionAngle =  PI+qAtan2(point.y(),point.x() );
//            //angle = 2.0*(collisionAngle+PI/2.0)-ballmove->angle; //angle 是由ball指向Handle

//          //  angle = angle+ PI; //angle 是由Handle指向ball
//            angle = collisionAngle;
//            point = HandlePosition;
//            point+=QPointF((ballmove->Radius+userhandle->Radius)*cos(angle)/2.0,(ballmove->Radius+userhandle->Radius)*sin(angle)/2.0);
//            ballmove->setPos(point);
//        }
         //或者使用另外一种方式 ,ball 退回一步
         {
             qreal xvel = 0;
             qreal yvel = 0;
             qreal angle = ballmove->angle;

             xvel =ballmove->speed*0.01*qCos(angle);
             yvel = ballmove->speed*0.01*qSin(angle);

             QPointF newPos = ballmove->pos() -QPointF(xvel, yvel);//往回退回一步

             ballmove->setPos(newPos);
         }
          ballmove->collisionCalcualte(Handle) ;//一定要先退出来再反弹

     }

 }

 //运动物体的运动更新

ballmove->advance();

//    ballmove->moveBy(0.1,0.1);
}
