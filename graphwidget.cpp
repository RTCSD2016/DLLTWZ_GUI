
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
    x1 = 0;
    x2 = 0;

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

    // 得分文本
    gameScoreText = new QGraphicsTextItem();
    gameScoreText->setFont(QFont("Times", 20, QFont::Bold));
    gameScoreText->setPos(200, 0);
    setScore(0,0);
    //gameScoreText->setHtml(tr("<font color=red>%1:%2</font>").arg(0).arg(0));//设置初始分数
    scene->addItem(gameScoreText);//

    //添加球洞

    uphole = new QGraphicsRectItem(0,0,100,40);
    uphole->setBrush(Qt::blue);
    uphole->setData(0,"hole1");
    scene->addItem(uphole);//上边
    uphole->setPos(-50,-500-20);
    uphole->setFlag(QGraphicsItem::ItemIsMovable,false);//禁止鼠标拖动 // // // //

    downhole = new QGraphicsRectItem(0,0,100,40);
    downhole->setBrush(Qt::yellow);
    downhole->setData(0,"hole2");
    scene->addItem(downhole);//下边
    downhole->setPos(-50,500-20);
    downhole->setFlag(QGraphicsItem::ItemIsMovable,false);//禁止鼠标拖动 // // // //

    //添加球
    ballmove  =new Ball(this);
    scene->addItem(ballmove);
    //ballmove->setPos(0,0);
      ballmove->setData(0,"ball");//设置键值up
    ballmove->setFlag(QGraphicsItem::ItemIsMovable,false);//禁止鼠标拖动 // // // //

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
    frameUp->setFlag(QGraphicsItem::ItemIsMovable,false);//边框禁止鼠标拖动 // // // //

    Frame *up2 = new Frame(this,QRectF(-0,-0,300-50,20));
    scene->addItem(up2);
    up2->setPos(0+50,-500);
    up2->setData(0,"up");//设置键值up
    up2->setFlag(QGraphicsItem::ItemIsMovable,false);// // // // //

    frameDown = new Frame(this,QRectF(0,0,300-50,20));
    scene->addItem(frameDown);
    frameDown->setPos(-300,+500-20);
    frameDown->setData(0,"down");//设置键值down
    frameDown->setFlag(QGraphicsItem::ItemIsMovable,false);// // // // //

    Frame *down2 = new Frame(this,QRectF(0,0,300-50,20));
    scene->addItem(down2);
    down2->setPos(0+50,500-20);
    down2->setData(0,"down");//设置键值down
    down2->setFlag(QGraphicsItem::ItemIsMovable,false);// // // // //


    frameLeft = new Frame(this,QRectF(-300,-500,20,1000));
    scene->addItem(frameLeft);
    frameLeft->setPos(0,0);
    frameLeft->setData(0,"left");//设置键值left
    frameLeft->setFlag(QGraphicsItem::ItemIsMovable,false);// // // // //

    frameRight = new Frame(this,QRectF(300-20,-500,20,1000));
    scene->addItem(frameRight);
    frameRight->setPos(0,0);
    frameRight->setData(0,"right");//设置键值right
    frameRight->setFlag(QGraphicsItem::ItemIsMovable,false);// // // // //

    //添加游戏手柄

    userhandle  =new userHandle(this);
    scene->addItem(userhandle);
    userhandle->setPos(10,200);
    userhandle->setData(0,"userhandle");//设置键值userhandle

    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(500, 800+50);
    //   setMinimumSize(600+50, 1000+60);
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
    game->showPosition();
    //判断球是否进洞
    if(ballmove->pos().y() < -500+20)
    {x2 = x2+1;

        setScore(x1,x2);
        //延时一段时间

        ballmove->Reset();
        return;
    }
    if(ballmove->pos().y() > +500-20)
    {
         x1 = x1+1;
        setScore(x1,x2);
        //延时一段时间

        ballmove->Reset();
        return;
    }
    /*
     QList<QGraphicsItem *>  collisionsforhole1 = uphole->collidingItems();//获取所有碰撞的对象
     foreach (QGraphicsItem *item, collisionsforhole1)
     {
         if(item->data(0).toString().contains("ball")) // 如果碰到了上边的hole
         {
            x1 = x1+1;
            setScore(x1,x2);
            //延时一段时间

            ballmove->Reset();
            break;
         }
         if
     }

     QList<QGraphicsItem *>  collisionsforhole2 = downhole->collidingItems(Qt::ContainsItemBoundingRect);//获取所有碰撞的对象
     foreach (QGraphicsItem *item, collisionsforhole2)
     {
         if(item->data(0).toString().contains("ball")) // 如果碰到了下边的hole
         {
            x2 = x2+1;
            setScore(x1,x2);
            //延时一段时间

            ballmove->Reset();
            break;
         }
     }*/
     //判断球与边框的碰撞
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

                 QPointF newPos = ballmove->pos() -QPointF(2*xvel, 2*yvel);//往回退回一步,*2表示多退一点

                 ballmove->setPos(newPos);
             }
              ballmove->collisionCalcualte(Handle) ;//一定要先退出来再反弹
         }
     }

    //运动物体的运动更新

    ballmove->advance();

//    ballmove->moveBy(0.1,0.1);
}

//设置分数
void GraphWidget::setScore(int x1 ,int x2)
{
 gameScoreText->setHtml(tr("<font color=red>%1:%2</font>").arg(x1).arg(x2));//设置分数
}


void GraphWidget ::start()
{
    //showwidget->ballmove->Reset();
    ballmove->Reset();
    ballmove->setSpeed(400);
}

void GraphWidget ::pause()
{
    if(ballmove->speed > 0)
    {
         ballmove->setSpeed(0);
    }
    else if(ballmove->speed < 1.0)
    {
         ballmove->setSpeed(400);
    }

}
void GraphWidget ::reset()
{
    ballmove->Reset();
    ballmove->setSpeed(0);
    x1 = 0;
    x2 = 0;
    gameScoreText->setHtml(tr("<font color=red>%1:%2</font>").arg(0).arg(0));//设置分数
}
