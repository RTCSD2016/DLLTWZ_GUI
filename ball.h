#ifndef BALL_H
#define BALL_H

#include <QGraphicsItem>
#include <QtGlobal>
//声明类

class GraphWidget;

typedef   enum{Up=1,Down,Left,Right,Handle} collisionType;//用于表示碰撞方向类型（是否可以在类里定义）
#define PI 3.141592653
#define FRECUENCY 100

class Ball:public QGraphicsItem
{

public:
    Ball(GraphWidget *graphWidget);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    bool advance();        //计算一定时间周期后的位置并重新setpos
    bool collisionCalcualte(collisionType);//计算碰撞后的速度和方向；
    void setSpeed(qreal);
    void setAngle(qreal);
    void Reset();

protected:

public:         //只有声明为public后 其他的类才能访问【】或者添加额外的接口函数实现
    GraphWidget *graph;
    qreal Radius;//需要被另外的类访问就要声明为public类型
    qreal angle;//运动的速度和方向
    qreal speed;
    QPointF newPos; //新的位置
    qreal ratio ;//图形的比例大小


   // typedef   enum{up,down,left,right} Type;//用于表示碰撞类型


};

#endif // BALL_H
