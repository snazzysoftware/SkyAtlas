//
//  Star.cpp
//  SkyAtlas
//
//  Created by Adam French on 27/02/2013.
//  Copyright (c) 2013 Adam French. All rights reserved.
//
#include <ios>
#include <sstream>
#include "Star.h"

SkyAtlas::Star::Star(unsigned long henreyDraperCatalogueNumber,
                     unsigned long bscCatalogueNumber,
                     double rectascension,
                     double declination,
                     double visualBrightness,
                     double bvBrightness,
                     unsigned long flamsteedNumber,
                     std::string &label,
                     std::string &constellation,
                     std::string &spectralClass) :
    henreyDraperCatalogueNumber(henreyDraperCatalogueNumber),
    bscCatalogueNumber(bscCatalogueNumber),
    rectascension(rectascension),
    declination(declination),
    visualBrightness(visualBrightness),
    bvBrightness(bvBrightness),
    flamsteedNumber(flamsteedNumber),
    label(label),
    constellation(constellation),
    spectralClass(spectralClass),
    connectedStars()
{
}

SkyAtlas::Star::Star(std::istream &input) :
    henreyDraperCatalogueNumber(0),
    bscCatalogueNumber(0),
    rectascension(0),
    declination(0),
    visualBrightness(0),
    bvBrightness(0),
    flamsteedNumber(0),
    connectedStars()
{
    std::string numericLine;
    getline(input, numericLine);
    std::stringstream inputStream(numericLine, std::ios_base::in);
    inputStream >> henreyDraperCatalogueNumber;
    inputStream >> bscCatalogueNumber;
    inputStream >> rectascension;
    inputStream >> declination;
    inputStream >> visualBrightness;
    inputStream >> bvBrightness;
    inputStream >> flamsteedNumber;
    
    // Read strings by entire line in case of whitespace
    getline(input, label);
    getline(input, constellation);
    getline(input, spectralClass);
}

bool SkyAtlas::Star::operator<(const Star& star) const
{
    return (visualBrightness < star.visualBrightness);
}
