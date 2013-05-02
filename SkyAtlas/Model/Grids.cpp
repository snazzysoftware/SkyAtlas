//
//  Grids.cpp
//  SkyAtlas
//
//  Created by Adam French on 02/05/2013.
//  Copyright (c) 2013 Adam French. All rights reserved.
//

#include <boost/shared_ptr.hpp>
#include "Grids.h"
#include "Star.h"

boost::shared_ptr<SkyAtlas::Sky> SkyAtlas::BuildEquatorialGrid(
        double declinationSeparation, double rectacensionSeparation)
{
    boost::shared_ptr<SkyAtlas::SkyRectangle> wholeSkyRectangle(new SkyAtlas::SkyRectangle(0.0, 24.0, -90.0, 90.0));
    boost::shared_ptr<SkyAtlas::Sky> result(new SkyPatch(wholeSkyRectangle));
    
    std::string empty;
    
    // Create the north and south pole points
    boost::shared_ptr<SkyAtlas::Star> southPoint(
        new SkyAtlas::Star(0, 0, 0.0, -90.0, 0.0, 0.0, 0, empty, empty, empty));
    boost::shared_ptr<SkyAtlas::Star> northPoint(
        new SkyAtlas::Star(0, 0, 0.0, -90.0, 0.0, 0.0, 0, empty, empty, empty));
    result->AddStar(southPoint);
    result->AddStar(northPoint);
    
    std::vector<std::vector<boost::shared_ptr<SkyAtlas::Star> > > workingGrid;
    int d = 0;
    for (double declination = -90.0 + declinationSeparation; declination < 90.0; declination += declinationSeparation)
    {
        int r = 0;
        workingGrid.push_back(std::vector<boost::shared_ptr<SkyAtlas::Star> >());
        for (double rectacension = 0.0; rectacension < 24.0; rectacension += rectacensionSeparation)
        {
            boost::shared_ptr<SkyAtlas::Star> current(
                new SkyAtlas::Star(0, 0, rectacension, declination, 0.0, 0.0, 0, empty, empty, empty));
            
            // Connect the current point to the one on the previous declination
            // ring at the same rectacension
            if ((d - 1) > 0)
            {
                current->connectedStars.push_back(workingGrid[d - 1][r]);
            }
            // Connect the points on the first declination ring to the south
            // point
            else if ((d - 1) == 0)
            {
                current->connectedStars.push_back(southPoint);
            }
            
            // Connect the points on the last declination ring to the north
            // point
            if (declination + declinationSeparation >= 90.0)
            {
                current->connectedStars.push_back(northPoint);
            }
            
            // Connect the current point to the one on the current declination
            // ring at the previous rectacension
            if ((r - 1) > 0)
            {
                current->connectedStars.push_back(workingGrid[d][r - 1]);
            }
            
            // Connect the last point on the current rectacension ring to the
            // first point on the current rectacension ring
            if (rectacension + rectacensionSeparation >= 24.0 && !workingGrid[d].empty())
            {
                current->connectedStars.push_back(workingGrid[d][0]);
            }
            
            result->AddStar(current);
            workingGrid[d].push_back(current);
            r++;
        }
        d++;
    }
    
    return result;
}
