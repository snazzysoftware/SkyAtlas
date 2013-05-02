//
//  MainWindow.cpp
//  SkyAtlas
//
//  Created by Adam French on 19/04/2013.
//  Copyright (c) 2013 Adam French. All rights reserved.
//

#include <fstream>
#include <QtGui>
#include <QGridLayout>
#include "../SkyAtlas/Model/Grids.h"
#include "MainWindow.h"
#include "SkyWidget.h"

FrontEnd::MainWindow::MainWindow()
{
    LoadSky();
    skyWidget = new SkyWidget(0, wholeSky, equatorialGrid, projection);
    
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(3, 1);
    mainLayout->addWidget(skyWidget, 0, 0, 1, 4);
    setLayout(mainLayout);
    
    setWindowTitle(tr("SkyAtlas"));
}

void FrontEnd::MainWindow::LoadSky()
{
    // Create a sky to put the stars into
    boost::shared_ptr<SkyAtlas::SkyRectangle> wholeSkyRectangle(new SkyAtlas::SkyRectangle(0.0, 24.0, -90.0, 90.0));
    wholeSky = boost::shared_ptr<SkyAtlas::SkyGrid>(new SkyAtlas::SkyGrid(wholeSkyRectangle));

    // Read in the star catalogue
    std::ifstream starsInput("/Users/adamfrench/Documents/XCode/SkyAtlas/SkyAtlas/SkyAtlas/stars.dat", std::ifstream::in);
    while (starsInput.good())
    {
        boost::shared_ptr<SkyAtlas::Star> star(new SkyAtlas::Star(starsInput));
        wholeSky->AddStar(star);
    }

    // Generate the equatorial grid
    equatorialGrid = SkyAtlas::BuildEquatorialGrid(360.0 / 100, 24.0 / 100);

    // Initialize the stereographic projection
    std::pair<double, double> viewerRectacensionDeclination(-10.0, -10.0);
    double viewerAngle = 10.0;
    projection = boost::shared_ptr<SkyAtlas::StereographicProjection>(
        new SkyAtlas::StereographicProjection(viewerRectacensionDeclination, viewerAngle));
}
