#include "mygraphicsview.h"

#include <QMouseEvent>
#include <QDebug>

MyGraphicsView::MyGraphicsView(QWidget *parent) : QGraphicsView (parent)
{
    setMouseTracking(true);
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
    emit positionX(mapToScene(event->pos()).x());
}
