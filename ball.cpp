#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

#include "ball.h"
#include "graphwidget.h"

#include <QtCore/qmath.h>
#include  <qDebug>

Ball::Ball(GraphWidget *graphWidget) : graph(graphWidget)
{
    setFlag(ItemIsMovable);
    setCacheMode(DeviceCoordinateCache);
    setZValue(1);
    //运动参数初始化
    speed = 0;//运动速度为100像素每秒；
    angle = -PI/6.0;
    Reset();//重置球的位置和方向
    ratio = 2;//图形比例
    Radius  = 20*ratio;
}
bool Ball::advance()
{
    qreal xvel = 0;
    qreal yvel = 0;

    xvel =speed*1.0/FRECUENCY *qCos(angle);
    yvel = speed*1.0/FRECUENCY *qSin(angle);

    newPos = pos() + QPointF(xvel, yvel);

    if (newPos == pos())
        return false;

    setPos(newPos);
    return true;

}

bool Ball::collisionCalcualte(collisionType direction)//计算碰撞后的速度和方向
{
    if(direction ==Up)   //如果碰到上边的Frame
    {
        qDebug()<<"collision to Up Frame!"<<endl;
        angle = 0-angle;
    }
    if(direction ==Down)   //如果碰到右边的Frame
    {
        qDebug()<<"collision to Down frame!"<<endl;
        angle = 0-angle;
    }
    if(direction ==Left)   //如果碰到右边的Frame
    {
        qDebug()<<"collision to Left Frame!"<<endl;
        angle = PI-angle;
    }
    if(direction ==Right)   //如果碰到右边的Frame
    {
        qDebug()<<"collision to Right Frame!"<<endl;
        angle = PI-angle;
    }
    if(direction ==Handle)   //如果碰到Handle，【】重点：叠加上Handle额外导致的速度;
    {
        qDebug()<<"collision to Handle now !"<<endl;
        QPointF point = graph->HandlePosition;
        qDebug()<<point;
        point-=graph->ballPosition;
        qreal collisionAngle =  qAtan2(point.y(),point.x() );
        angle = 2.0*(collisionAngle+PI/2.0)-angle; //angle 是由ball指向Handle
//        //将嵌入到Handle的 ball退出来
//        angle = angle+ PI; //angle 是由Handle指向ball

    }


return true;
}

QRectF Ball::boundingRect() const
{
    qreal adjust = 1;
    return QRectF(-10*ratio + adjust*ratio, -10*ratio + adjust*ratio,
                  20*ratio - 2*adjust*ratio, 20*ratio - 2*adjust*ratio);
}

QPainterPath Ball::shape() const
{
    QPainterPath path;
    path.addEllipse(-10*ratio, -10*ratio, 20*ratio, 20*ratio);
    return path;

}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    // painter->drawEllipse(-9*ratio, -9*ratio, 20*ratio, 20*ratio);//在后面造成阴影效果

    QRadialGradient gradient(-3*ratio, -3*ratio, 10*ratio);
      if (option->state & QStyle::State_Sunken) {
          gradient.setCenter(3*ratio, 3*ratio);
          gradient.setFocalPoint(3*ratio, 3*ratio);
          gradient.setColorAt(1, QColor(Qt::white).light(120));
          gradient.setColorAt(0, QColor(Qt::gray).light(120));
      } else {
          gradient.setColorAt(0, Qt::white);
          gradient.setColorAt(1, Qt::gray);
      }
      painter->setBrush(gradient);
      painter->setPen(QPen(Qt::white, 0));
      painter->drawEllipse(-10*ratio, -10*ratio, 20*ratio, 20*ratio);

  //    painter->drawEllipse(-10*ratio*0.8, -10*ratio*0.8, 20*ratio*0.8, 20*ratio*0.8);//画圆
      //painter->drawRect(QRectF());
}
void Ball::setSpeed(qreal s)
{
    speed = s;

}
void Ball::setAngle(qreal a)
{
    angle = a;
}
//重置球的位置和方向
void Ball::Reset()
{
   setPos(0,-400);
   int rand = qrand()%100;
   angle =0.1*PI+ 0.8*PI*rand/100.0;
}
