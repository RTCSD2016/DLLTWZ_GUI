#include "gamewidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QDebug>

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent)
{
    //create需要的部件
    showwidget = new GraphWidget(this); //将指针传递给子对象，方便信息交换

    labelBall  = new QLabel(tr("BallPos:"));
    editBall = new QLineEdit;
    labelBall->setBuddy(editBall);

    labelHandle = new QLabel(tr("HandlePos"));
    editHandle = new QLineEdit;
    labelHandle->setBuddy(editHandle);

    startButton = new QPushButton(tr("Start"));//开始
    pauseButton = new QPushButton(tr("Pause"));//暂停
    pauseButton->setText("Pause");
    restartButton = new QPushButton(tr(" Reset "));//重置，重新开始
    //连接信号与槽
    connect(startButton, SIGNAL(clicked()), showwidget, SLOT(start()));
    connect(pauseButton, SIGNAL(clicked()), showwidget, SLOT(pause()));
    connect(restartButton, SIGNAL(clicked()), showwidget, SLOT(reset()));
    connect(startButton, SIGNAL(clicked()), this, SLOT(start()));
    connect(pauseButton, SIGNAL(clicked()), this, SLOT(pause()));
    connect(restartButton, SIGNAL(clicked()), this, SLOT(reset()));

    pauseButton->setEnabled(false);
    restartButton->setEnabled(false);

    //布局
    QHBoxLayout *PosLayout = new QHBoxLayout;
    PosLayout->addWidget(labelBall);
    PosLayout->addWidget(editBall);
    PosLayout->addWidget(labelHandle);
    PosLayout->addWidget(editHandle);
    PosLayout->addStretch(5);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(pauseButton);
    buttonLayout->addWidget(restartButton);
    buttonLayout->addStretch();


    QVBoxLayout *AllLayout = new QVBoxLayout;
    AllLayout->addLayout(PosLayout);
    AllLayout->addLayout(buttonLayout);
    AllLayout->addWidget(showwidget);
    setLayout(AllLayout);

}
void GameWidget ::showPosition()
{
  // qDebug()<<"gametest"<< showwidget->ballPosition;//game需要graph的数据，graph调用game的函数，ehehehhehe
    editBall->setText(QString("%1 , %2 ").arg(showwidget->ballPosition.x()).arg(showwidget->ballPosition.y()));
    editHandle->setText(QString("%1 , %2 ").arg(showwidget->HandlePosition.x()).arg(showwidget->HandlePosition.y()));
}

void GameWidget ::start()
{
    pauseButton->setEnabled(true);
    restartButton->setEnabled(true);
}
void GameWidget ::pause()
{
    if(pauseButton->text().contains("Pause"))
    {
        startButton->setEnabled(false);
        restartButton->setEnabled(false);
        pauseButton->setText("Return");
        return;
    }
     if(pauseButton->text().contains("Return"))
    {
        startButton->setEnabled(true);
        restartButton->setEnabled(true);
        pauseButton->setText("Pause");
    }

}
void GameWidget ::reset()
{
    pauseButton->setEnabled(false);
    restartButton->setEnabled(false);
}
