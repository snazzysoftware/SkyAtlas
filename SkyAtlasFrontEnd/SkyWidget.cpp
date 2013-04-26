//
//  SkyWidget.cpp
//  SkyAtlas
//
//  Created by Adam French on 19/04/2013.
//  Copyright (c) 2013 Adam French. All rights reserved.
//

#include <QtGui>
#include "SkyWidget.h"
#include "SkyAtlas/Model/Star.h"
#include "SkyAtlas/View/StereographicProjection.h"

FrontEnd::SkyWidget::SkyWidget(QWidget *parent,
                               boost::shared_ptr<SkyAtlas::SkyGrid> wholeSky,
                               boost::shared_ptr<SkyAtlas::StereographicProjection> projection)
    : QWidget(parent), wholeSky(wholeSky), projection(projection)
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

const QColor FrontEnd::SkyWidget::OClassColour = QColor(157, 180, 255);
const QColor FrontEnd::SkyWidget::BClassColour = QColor(170, 191, 255);
const QColor FrontEnd::SkyWidget::AClassColour = QColor(202, 216, 255);
const QColor FrontEnd::SkyWidget::FClassColour = QColor(251, 248, 255);
const QColor FrontEnd::SkyWidget::GClassColour = QColor(255, 244, 232);
const QColor FrontEnd::SkyWidget::KClassColour = QColor(255, 221, 180);
const QColor FrontEnd::SkyWidget::MClassColour = QColor(255, 189, 111);
const QColor FrontEnd::SkyWidget::LClassColour = QColor(247, 66, 53);
const QColor FrontEnd::SkyWidget::TClassColour = QColor(186, 48, 89);
const QColor FrontEnd::SkyWidget::YClassColour = QColor(96, 81, 112);

void starPlotVisitor(boost::shared_ptr<SkyAtlas::Star> star, void* context)
{
    std::pair<boost::shared_ptr<QPainter>, boost::shared_ptr<SkyAtlas::StereographicProjection> >* pContext =
            (std::pair<boost::shared_ptr<QPainter>, boost::shared_ptr<SkyAtlas::StereographicProjection> >*)(context);
    boost::shared_ptr<QPainter> painter = pContext->first;
    boost::shared_ptr<SkyAtlas::StereographicProjection> projection = pContext->second;

    std::pair<double, double> cartesianPosition = projection->ProjectPoint(
                std::pair<double, double>(star->rectascension, star->declination));

    painter->setPen(Qt::black);

    // Set approximate spectral colour
    if (star->spectralClass.substr(0, 1).compare("O") == 0)
        painter->setBrush(QBrush(FrontEnd::SkyWidget::OClassColour, Qt::SolidPattern));
    else if (star->spectralClass.substr(0, 1).compare("B") == 0)
        painter->setBrush(QBrush(FrontEnd::SkyWidget::BClassColour, Qt::SolidPattern));
    else if (star->spectralClass.substr(0, 1).compare("A") == 0)
        painter->setBrush(QBrush(FrontEnd::SkyWidget::AClassColour, Qt::SolidPattern));
    else if (star->spectralClass.substr(0, 1).compare("F") == 0)
        painter->setBrush(QBrush(FrontEnd::SkyWidget::FClassColour, Qt::SolidPattern));
    else if (star->spectralClass.substr(0, 1).compare("G") == 0)
        painter->setBrush(QBrush(FrontEnd::SkyWidget::GClassColour, Qt::SolidPattern));
    else if (star->spectralClass.substr(0, 1).compare("K") == 0)
        painter->setBrush(QBrush(FrontEnd::SkyWidget::KClassColour, Qt::SolidPattern));
    else if (star->spectralClass.substr(0, 1).compare("M") == 0)
        painter->setBrush(QBrush(FrontEnd::SkyWidget::MClassColour, Qt::SolidPattern));
    else if (star->spectralClass.substr(0, 1).compare("L") == 0)
        painter->setBrush(QBrush(FrontEnd::SkyWidget::LClassColour, Qt::SolidPattern));
    else if (star->spectralClass.substr(0, 1).compare("T") == 0)
        painter->setBrush(QBrush(FrontEnd::SkyWidget::TClassColour, Qt::SolidPattern));
    else if (star->spectralClass.substr(0, 1).compare("Y") == 0)
        painter->setBrush(QBrush(FrontEnd::SkyWidget::YClassColour, Qt::SolidPattern));
    else
        painter->setBrush(QBrush(Qt::lightGray, Qt::SolidPattern));

    painter->drawEllipse((cartesianPosition.first * 20.0 + 250.0),
                         (cartesianPosition.second * 20.0 + 250.0),
                         10,
                         10);
}

void FrontEnd::SkyWidget::paintEvent(QPaintEvent * /* event */)
{
    // Get the projection viewport
    boost::shared_ptr<SkyAtlas::SkyRectangle> viewport = projection->GetViewport();

    // Draw the stars
    boost::shared_ptr<QPainter> painter = boost::shared_ptr<QPainter>(new QPainter(this));
    painter->setRenderHint(QPainter::Antialiasing, true);
    std::pair<boost::shared_ptr<QPainter>, boost::shared_ptr<SkyAtlas::StereographicProjection> > context(painter, projection);
    wholeSky->VisitStars(viewport, starPlotVisitor, &context);

    // Draw the border
    painter->setPen(QPen(Qt::gray, 2, Qt::SolidLine, Qt::FlatCap));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(QRect(1, 1, width() - 2, height() - 2));
}


