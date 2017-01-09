#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H


#include <QGraphicsView>

#define FRECUENCY 200

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
    void setScore(int ,int);

protected:
void timerEvent(QTimerEvent *event);

public slots:
    void start();
    void pause();
    void reset();
public:
    //分数
    int x1;
    int x2;

    //创建父对象的指针，便于传递信息
    GameWidget * game;
    //定时器id
    int timerId;
    //显示的实体
     QGraphicsRectItem *uphole;
      QGraphicsRectItem *downhole;
    Ball *ballmove;
    Frame *frame;
    Frame * frameUp;
    Frame * frameLeft;
    Frame * frameDown;
    Frame * frameRight;
    userHandle * userhandle;  //
    // 得分文本
    QGraphicsTextItem *gameScoreText;
  //  QGraphicsTextItem *gameLevelText;

};

#endif // GRAPHWIDGET_H





