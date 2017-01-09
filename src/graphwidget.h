#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H


#include <QGraphicsView>

#define FRECUENCY 100

class Ball;
class Frame;
class userHandle;
class GameWidget;

class GraphWidget: public QGraphicsView
{
    Q_OBJECT
public:
    GraphWidget(GameWidget *gamewidget);

 QPointF ballPosition;
 QPointF HandlePosition;


protected:
void timerEvent(QTimerEvent *event);


private:
    GameWidget * game;//创建父对象的指针，便于传递信息

    int timerId;
    Ball *ballmove;
    Frame *frame;

    Frame * frameUp;
    Frame * frameLeft;
    Frame * frameDown;
    Frame * frameRight;
    userHandle * userhandle;  //



};

#endif // GRAPHWIDGET_H





