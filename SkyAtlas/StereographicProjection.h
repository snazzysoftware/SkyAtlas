//
//  StereographicProjection.h
//  SkyAtlas
//
//  Created by Adam French on 03/04/2013.
//  Copyright (c) 2013 Adam French. All rights reserved.
//

#ifndef __SkyAtlas__StereographicProjection__
#define __SkyAtlas__StereographicProjection__

#include "Projection.h"

namespace SkyAtlas
{
    
    class StereographicProjection : public Projection
    {
        
    public:
        
        StereographicProjection(std::pair<double, double> viewerRectacensionDeclination, double viewerAngle);
        
        virtual boost::shared_ptr<SkyRectangle> GetViewport();
        
        virtual std::pair<double, double> ProjectPoint(std::pair<double, double> starRectacensionDeclination);
        
        virtual ~StereographicProjection() { }
        
        std::pair<double, double> viewerRectacensionDeclination;
        double viewerAngle;
        
    private:

    };
    
}

#endif /* defined(__SkyAtlas__StereographicProjection__) */
