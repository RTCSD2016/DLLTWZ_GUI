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
    void setPosition();

private:
    QLabel *labelBall;
    QLabel *labelHandle;
    QLineEdit *editBall;
    QLineEdit *editHandle;

    GraphWidget *showwidget;

};

#endif // GAMEWIDGET_H
