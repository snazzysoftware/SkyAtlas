//
//  Star.h
//  SkyAtlas
//
//  Created by Adam French on 27/02/2013.
//  Copyright (c) 2013 Adam French. All rights reserved.
//

#ifndef __SkyAtlas__Star__
#define __SkyAtlas__Star__

#include <boost/shared_ptr.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace SkyAtlas
{
    
    class Star {
    public:
        unsigned long henreyDraperCatalogueNumber;
        unsigned long bscCatalogueNumber;
        double rectascension; // In hours
        double declination; // In degrees
        double visualBrightness;
        double bvBrightness;
        unsigned long flamsteedNumber;
        std::string label;
        std::string constellation;
        std::string spectralClass;
        
        // Connected neighbour stars
        std::vector<boost::shared_ptr<Star> > connectedStars;
    
        // Create a Star from numeric values
        Star(unsigned long henreyDraperCatalogueNumber,
             unsigned long bscCatalogueNumber,
             double rectascension,
             double declination,
             double visualBrightness,
             double bvBrightness,
             unsigned long flamsteedNumber,
             std::string &label,
             std::string &constellation,
             std::string &spectralClass);
    
        // Create a Star from an input stream
        Star(std::istream &input);

        bool operator<(const Star& star) const;
        
        // Output stream operator to allow textual debugging
        //std::ostream & operator<<(std::ostream &os, const Star &p);

    };
    
}

#endif /* defined(__SkyAtlas__Star__) */
