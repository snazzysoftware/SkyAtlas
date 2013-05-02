//
//  Grids.h
//  SkyAtlas
//
//  Created by Adam French on 02/05/2013.
//  Copyright (c) 2013 Adam French. All rights reserved.
//

#ifndef __SkyAtlas__Grids__
#define __SkyAtlas__Grids__

#include <boost/shared_ptr.hpp>
#include "Sky.h"

namespace SkyAtlas
{
    
    boost::shared_ptr<SkyAtlas::Sky> BuildEquatorialGrid(
            double declinationSeparation, double rectacensionSeparation);
    
}

#endif /* defined(__SkyAtlas__Grids__) */
