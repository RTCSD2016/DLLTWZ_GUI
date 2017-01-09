#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include "graphwidget.h"

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = 0);


signals:

public slots:
    void showPosition();

    void start();
    void pause();
    void reset();

private:
    QLabel *labelBall;
    QLabel *labelHandle;
    QLineEdit *editBall;
    QLineEdit *editHandle;

    QPushButton* startButton;//开始
    QPushButton* pauseButton;//暂停
    QPushButton* restartButton;//重置，重新开始
    //QPushButton* startButton;//

    GraphWidget *showwidget;

};

#endif // GAMEWIDGET_H
