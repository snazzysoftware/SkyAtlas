//
//  Projection.h
//  SkyAtlas
//
//  Created by Adam French on 03/04/2013.
//  Copyright (c) 2013 Adam French. All rights reserved.
//

#ifndef __SkyAtlas__Projection__
#define __SkyAtlas__Projection__

#include <boost/shared_ptr.hpp>
#include <utility>
#include "Sky.h"

namespace SkyAtlas
{
    
    class Projection
    {
        
    public:
        
        virtual boost::shared_ptr<SkyRectangle> GetViewport() = 0;
        
        virtual std::pair<double, double> ProjectPoint(std::pair<double, double> rectacensionDeclination) = 0;
        
        virtual ~Projection() { }
        
    private:
        
    };
    
}

#endif /* defined(__SkyAtlas__Projection__) */
