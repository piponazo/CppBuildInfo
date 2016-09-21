#include "mygraphicsview.h"

#include <QDebug>
#include <QMouseEvent>

namespace
{
    const double scaleFactor = 1.15;
}

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
    if (event->delta() > 0)
    {
        scale(scaleFactor, scaleFactor); // Zoom in
    }
    else
    {
        scale(1.0 / scaleFactor, 1.0 / scaleFactor); // Zooming out
    }
}

void MyGraphicsView::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
    case Qt::Key_Plus:
        scale(scaleFactor, scaleFactor);
        break;
    case Qt::Key_Minus:
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        break;
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Down:
    case Qt::Key_Up:
        QAbstractScrollArea::keyPressEvent(event);
        break;
    };
}
