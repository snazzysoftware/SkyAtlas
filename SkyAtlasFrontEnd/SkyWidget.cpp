//
//  SkyWidget.cpp
//  SkyAtlas
//
//  Created by Adam French on 19/04/2013.
//  Copyright (c) 2013 Adam French. All rights reserved.
//

#include <QtGui>
#include "SkyWidget.h"

FrontEnd::SkyWidget::SkyWidget(QWidget *parent)
: QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

QSize FrontEnd::SkyWidget::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize FrontEnd::SkyWidget::sizeHint() const
{
    return QSize(400, 200);
}

void FrontEnd::SkyWidget::paintEvent(QPaintEvent * /* event */)
{
    static const QPoint points[4] = {
        QPoint(10, 80),
        QPoint(20, 10),
        QPoint(80, 30),
        QPoint(90, 70)
    };
    
    QPainter painter(this);
    painter.setPen(palette().text().color());
    painter.setBrush(Qt::SolidPattern);
    painter.setRenderHint(QPainter::Antialiasing, true);
    
    for (int x = 0; x < width(); x += 100) {
        for (int y = 0; y < height(); y += 100) {
            painter.save();
            painter.translate(x, y);
            painter.drawPoints(points, 4);
            painter.restore();
        }
    }

    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
