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

//布局
    QHBoxLayout *PosLayout = new QHBoxLayout;
    PosLayout->addWidget(labelBall);
    PosLayout->addWidget(editBall);
    PosLayout->addWidget(labelHandle);
    PosLayout->addWidget(editHandle);

    PosLayout->addStretch();

    QVBoxLayout *AllLayout = new QVBoxLayout;
    AllLayout->addLayout(PosLayout);
    AllLayout->addWidget(showwidget);
    setLayout(AllLayout);

}
void GameWidget ::setPosition()
{
  // qDebug()<<"gametest"<< showwidget->ballPosition;//game需要graph的数据，graph调用game的函数，ehehehhehe
    editBall->setText(QString("%1 , %2 ").arg(showwidget->ballPosition.x()).arg(showwidget->ballPosition.y()));
    editHandle->setText(QString("%1 , %2 ").arg(showwidget->HandlePosition.x()).arg(showwidget->HandlePosition.y()));


}
