//
//  SkyWidget.h
//  SkyAtlas
//
//  Created by Adam French on 19/04/2013.
//  Copyright (c) 2013 Adam French. All rights reserved.
//

#ifndef __SkyAtlas__SkyWidget__
#define __SkyAtlas__SkyWidget__

#include <boost/shared_ptr.hpp>
#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include "../SkyAtlas/Model/Sky.h"
#include "../SkyAtlas/View/StereographicProjection.h"

namespace FrontEnd
{

    class SkyWidget : public QWidget
    {
        //Q_OBJECT
        
    public:
        
        SkyWidget(QWidget *parent = 0,
                  boost::shared_ptr<SkyAtlas::SkyGrid> wholeSky =
                boost::shared_ptr<SkyAtlas::SkyGrid>(
                    new SkyAtlas::SkyGrid(boost::shared_ptr<SkyAtlas::SkyRectangle>(
                                              new SkyAtlas::SkyRectangle(0.0, 360.0, -90.0, 90.0)))),
                  boost::shared_ptr<SkyAtlas::StereographicProjection> projection =
                boost::shared_ptr<SkyAtlas::StereographicProjection>(
                    new SkyAtlas::StereographicProjection(std::pair<double, double>(0.0, 0.0), 90.0)));
        
        QSize minimumSizeHint() const;
        QSize sizeHint() const;
        
        // Spectral colour constants
        static const QColor OClassColour;
        static const QColor BClassColour;
        static const QColor AClassColour;
        static const QColor FClassColour;
        static const QColor GClassColour;
        static const QColor KClassColour;
        static const QColor MClassColour;
        static const QColor LClassColour;
        static const QColor TClassColour;
        static const QColor YClassColour;

    protected:
        void paintEvent(QPaintEvent *event);
        
    private:
        boost::shared_ptr<SkyAtlas::SkyGrid> wholeSky;
        boost::shared_ptr<SkyAtlas::StereographicProjection> projection;

    };
    
}

#endif /* defined(__SkyAtlas__SkyWidget__) */
