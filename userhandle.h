#ifndef USERHANDLE_H
#define USERHANDLE_H

#include <QGraphicsItem>

//声明类

class GraphWidget;

class userHandle:public QGraphicsItem
{

public:
    userHandle(GraphWidget *graphWidget);

    QRectF boundingRect() const;
    QPainterPath shape() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    qreal Radius;//需要被另外的类访问就要声明为public类型


protected:

 private:

    GraphWidget *graph;

    int ratio; //图形比例

};
#endif // USERHANDLE_H
