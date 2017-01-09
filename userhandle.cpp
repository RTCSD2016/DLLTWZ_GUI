
#include "graphwidget.h"
#include "userhandle.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>



#include <QtCore/qmath.h>
#include  <qDebug>

userHandle::userHandle(GraphWidget *graphWidget) : graph(graphWidget)
{
    setFlag(ItemIsMovable);
        setCacheMode(DeviceCoordinateCache);
        setZValue(1);
 ratio = 3;
   Radius  = 20*ratio;
}

QRectF userHandle::boundingRect() const
{
    qreal adjust = 2;
    return QRectF(-10*ratio - adjust*ratio, -10*ratio - adjust*ratio,
                  23*ratio + adjust*ratio, 23*ratio + adjust*ratio);
}

QPainterPath userHandle::shape() const
{
    QPainterPath path;
    path.addEllipse(-10*ratio, -10*ratio, 20*ratio, 20*ratio);
    return path;

}

void userHandle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{

        painter->setPen(Qt::NoPen);
        painter->setBrush(Qt::red);
        painter->drawEllipse(-10*ratio, -10*ratio, 20*ratio, 20*ratio);//画圆

     // painter->drawEllipse(-9*ratio, -9*ratio, 20*ratio, 20*ratio);//在后面造成阴影效果

      QRadialGradient gradient(-3*ratio, -3*ratio, 10*ratio);
      if (option->state & QStyle::State_Sunken) {
          gradient.setCenter(3*ratio, 3*ratio);
          gradient.setFocalPoint(3*ratio, 3*ratio);
          gradient.setColorAt(1, QColor(Qt::red).light(120));
          gradient.setColorAt(0, QColor(Qt::white).light(120));
      } else {
          gradient.setColorAt(0, Qt::white);
          gradient.setColorAt(1, Qt::red);
      }
      painter->setBrush(gradient);
      painter->setPen(QPen(Qt::white, 0));
      painter->drawEllipse(-10*ratio/2, -10*ratio/2, 20*ratio/2, 20*ratio/2);//画圆
      //painter->drawRect(QRectF());
}
