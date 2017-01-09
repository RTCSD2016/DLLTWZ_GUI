
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QRectF>

#include "frame.h"
#include "graphwidget.h"


Frame::Frame(GraphWidget *graphWidget, QRectF framerect)

{
    setFlag(ItemIsMovable);
    setCacheMode(DeviceCoordinateCache);
    setZValue(1);
    graph=(graphWidget);
    rect = framerect;
}
Frame::Frame(GraphWidget *graphWidget)

{
    setFlag(ItemIsMovable);
    setCacheMode(DeviceCoordinateCache);
    setZValue(1);

    graph=(graphWidget);
    rect =  QRectF(-50,50,150,50);
}

QRectF Frame::boundingRect() const
{
    return rect;
}

QPainterPath Frame::shape() const
{
    QPainterPath path;
    path.addRect(rect);
    return path;
}

void Frame::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawRect(rect);
}
