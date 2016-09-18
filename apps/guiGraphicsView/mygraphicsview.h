#pragma once

#include <QGraphicsView>

class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    MyGraphicsView(QWidget *parent = nullptr);

    virtual void mouseMoveEvent(QMouseEvent *event);

signals:
    void positionX(int x);
};
