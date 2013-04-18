//
//  StereographicProjection.cpp
//  SkyAtlas
//
//  Created by Adam French on 03/04/2013.
//  Copyright (c) 2013 Adam French. All rights reserved.
//

#include <cmath>
#include "StereographicProjection.h"

SkyAtlas::StereographicProjection::StereographicProjection(
    std::pair<double, double> viewerRectacensionDeclination,
    double viewerAngle) :
viewerRectacensionDeclination(viewerRectacensionDeclination),
viewerAngle(viewerAngle)
{
}

boost::shared_ptr<SkyAtlas::SkyRectangle> SkyAtlas::StereographicProjection::GetViewport()
{
    // The viewer celestial spherical co-ordinate 'Rectacension' (zenith angle) is A.
    // The viewer celestial spherical co-ordinate 'Declination' (azimuth angle) is B.
    // The viewport celestial spherical co-ordinate 'Rectacension' (zenith angle) is -A.
    // The viewport celestial spherical co-ordinate 'Declination' (azimuth angle) is -B.
    double a = viewerRectacensionDeclination.first;
    double b = viewerRectacensionDeclination.second;
    
    double minusA = -a;
    double minusB = -b;
    
    double halfHypotenuse = viewerAngle / 2.0;
    
    return boost::shared_ptr<SkyAtlas::SkyRectangle>(new SkyRectangle(
        minusA - halfHypotenuse,
        minusA + halfHypotenuse,
        minusB - halfHypotenuse,
        minusB + halfHypotenuse));
}

std::pair<double, double> SkyAtlas::StereographicProjection::ProjectPoint(
    std::pair<double, double> rectacensionDeclination)
{
    // The celestial spherical co-ordinate 'Rectacension' (zenith angle) is A.
    // The celestial spherical co-ordinate 'Declination' (azimuth angle) is B.
    // The atlas cartesian co-ordinate 'X' is X.
    // The atlas cartesian co-ordinate 'Y' is Y.
    double a = rectacensionDeclination.first;
    double b = rectacensionDeclination.second;
    
    double sinA = sin(a);
    double sinB = sin(b);
    double cosB = cos(b);
    double oneMinusCosA = 1.0 - cos(a);
    
    double x = (sinA * cosB) / oneMinusCosA;
    double y = (sinA * sinB) / oneMinusCosA;
    
    return std::pair<double, double>(x, y);
}
