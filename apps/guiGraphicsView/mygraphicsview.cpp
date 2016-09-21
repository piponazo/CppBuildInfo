#include "mygraphicsview.h"

#include <QDebug>
#include <QMouseEvent>

MyGraphicsView::MyGraphicsView(QWidget* parent)
      : QGraphicsView(parent)
{
    setMouseTracking(true);
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
    QGraphicsView::mouseMoveEvent(event);
    emit positionX(mapToScene(event->pos()).x());
}

void MyGraphicsView::wheelEvent(QWheelEvent* event)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    // Scale the view / do the zoom
    double scaleFactor = 1.15;
    if (event->delta() > 0)
    {
        // Zoom in
        scale(scaleFactor, scaleFactor);
    }
    else
    {
        // Zooming out
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}
