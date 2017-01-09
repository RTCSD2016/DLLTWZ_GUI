#ifndef FRAME_H
#define FRAME_H


#include <QGraphicsItem>

//声明类

class GraphWidget;

 //typedef   enum{up,down,left,right} type;

class Frame:public QGraphicsItem
{
public:
     Frame(GraphWidget *graphWidget);
    Frame(GraphWidget *graphWidget,QRectF rect );
    bool advance();
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
 protected:

 private:
   GraphWidget *graph;
    QRectF rect;
};

#endif // FRAME_H
