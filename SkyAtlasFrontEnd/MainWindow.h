//
//  MainWindow.h
//  SkyAtlas
//
//  Created by Adam French on 19/04/2013.
//  Copyright (c) 2013 Adam French. All rights reserved.
//

#ifndef __SkyAtlas__MainWindow__
#define __SkyAtlas__MainWindow__

#include <QWidget>
#include <boost/shared_ptr.hpp>
#include "../SkyAtlas/Model/Sky.h"
#include "../SkyAtlas/View/StereographicProjection.h"

namespace FrontEnd
{

    class SkyWidget;

    class MainWindow : public QWidget
    {
        //Q_OBJECT
        
    public:
        MainWindow();
        
    private:

        /// Loads the star database into the whole sky grid and initializes
        /// the stereographic projection ready for rendering.
        void LoadSky();

        SkyWidget *skyWidget;

        /// The whole sky grid.
        boost::shared_ptr<SkyAtlas::SkyGrid> wholeSky;

        /// The stereographic viewport projection.
        boost::shared_ptr<SkyAtlas::StereographicProjection> projection;

    };

}

#endif /* defined(__SkyAtlas__MainWindow__) */
