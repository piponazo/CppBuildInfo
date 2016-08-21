/* Cpp Build Info
   Copyright (C) 2016 Luis Díaz Más

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
*/

#include "CompilationProcessGraphicItem.h"
#include <QPen>
#include <QBrush>
#include <QDebug>
#include <QPainter>

CompilationProcessGraphicItem::CompilationProcessGraphicItem(const QString &fileName, qreal x, qreal y,
    qreal width, qreal height, QGraphicsItem *parent)
    : QGraphicsRectItem (x, y, width, height, parent)
    , _fileName(fileName)
{
    setToolTip(fileName);

    QBrush brush(Qt::darkGreen);
    QPen pen (brush, 2);

    QBrush brushFill(Qt::lightGray);
    setPen(pen);
    setBrush(brushFill);
    /// \todo add the name inside the rect
}

void CompilationProcessGraphicItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsRectItem::paint(painter, option, widget);

    /// \todo spend some more time trying to make nicer this representation
    QRectF rect = this->rect();
    rect.setX(rect.x() + 5);
    rect.setY(rect.y() + 5);

    painter->drawText(rect, _fileName);
}
