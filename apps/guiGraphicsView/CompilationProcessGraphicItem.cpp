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
#include <QFontMetrics>
#include <QDebug>
#include <QPainter>

CompilationProcessGraphicItem::CompilationProcessGraphicItem(const QString &fileName, qreal x,
    qreal y, qreal width, qreal height, QGraphicsItem *parent)
    : QGraphicsRectItem (x, y, width, height, parent)
    , _fileName(fileName)
{
    qDebug() << "Item created at: " << x << y << width << height;
    setToolTip(QString("File: %1\nDuration: %2 msecs").arg(fileName).arg(width));
}

void CompilationProcessGraphicItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                                          QWidget *widget)
{
    QFont font = painter->font();
    font.setPixelSize(25);
    font.setBold(true);
//    font.setPointSize(30);
//    font.setWeight(5);
    font.setLetterSpacing(QFont::PercentageSpacing, 200);
    painter->setFont(font);

    // Set gradient color
    {
        QLinearGradient g(this->rect().topLeft(),this->rect().bottomRight());
        g.setColorAt(0.0,QColor(128,128,128));
        g.setColorAt(1.0,QColor(240,240,240));
        this->setBrush(g);
    }

    //Let QGraphicsRectItem handle the default painting
    QGraphicsRectItem::paint(painter, option, widget);

    //Draw the text on the drawn rectangle
    painter->drawText(this->rect(), Qt::AlignCenter, _fileName);
}
