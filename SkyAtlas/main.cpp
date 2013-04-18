//
//  main.cpp
//  SkyAtlas
//
//  Created by Adam French on 27/02/2013.
//  Copyright (c) 2013 Adam French. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <boost/bimap.hpp>
#include <boost/algorithm/string.hpp>
#include "Star.h"
#include "Constellation.h"
#include "Sky.h"
#include "StereographicProjection.h"

std::ostream & operator<<(std::ostream &os, const SkyAtlas::Star &p)
{
    os << "Henry Draper Catalogue Number: " << p.henreyDraperCatalogueNumber << std::endl;
    os << "BSC Catalogue Number: " << p.bscCatalogueNumber << std::endl;
    os << "Rectascension: " << p.rectascension << std::endl;
    os << "Declination: " << p.declination << std::endl;
    os << "Visual Brightness: " << p.visualBrightness << std::endl;
    os << "BV Brightness: " << p.bvBrightness << std::endl;
    os << "Flamsteed Number: " << p.flamsteedNumber << std::endl;
    os << "Label: " << p.label << std::endl;
    os << "Constellation: " << p.constellation << std::endl;
    os << "SpectralClass: " << p.spectralClass << std::endl;
    return os;
}

std::ostream & operator<<(std::ostream &os, const SkyAtlas::StereographicProjection &p)
{
    os << "Viewer Rectacension: " << p.viewerRectacensionDeclination.first << std::endl;
    os << "Viewer Declination: " << p.viewerRectacensionDeclination.second << std::endl;
    os << "Viewer Angle: " << p.viewerAngle << std::endl;
    return os;
}

std::ostream & operator<<(std::ostream &os, const SkyAtlas::SkyRectangle &p)
{
    os << "Min Rectacension Inclusive: " << p.minRectacensionInclusive << std::endl;
    os << "Max Rectacension Exclusive: " << p.maxRectacensionExclusive << std::endl;
    os << "Min Declination Inclusive: " << p.minDeclinationInclusive << std::endl;
    os << "Max Declination Exclusive: " << p.maxDeclinationExclusive << std::endl;
    return os;
}

std::ostream & operator<<(std::ostream &os, const SkyAtlas::Constellation &p)
{
    os << "Code: " << p.code;
    for (std::vector<SkyAtlas::ConstellationLine>::const_iterator line = p.lines.begin();
         line != p.lines.end();
         ++line)
    {
        os << "Line: ";
        for (std::vector<SkyAtlas::Star>::const_iterator star = (*line).line.begin();
             star != (*line).line.end();
             ++star)
        {
            os << (*star).bscCatalogueNumber << " ";
        }
        os << std::endl;
    }
    return os;
}

boost::shared_ptr<SkyAtlas::StereographicProjection> projection;

void visitor(boost::shared_ptr<SkyAtlas::Star> star)
{
    std::cout << "Visiting star " << star->bscCatalogueNumber << " in " << star->constellation << std::endl;
    std::pair<double, double> cartesianPosition = projection->ProjectPoint(std::pair<double, double>(star->rectascension, star->declination));
    std::cout << "(Rectacension, Declination) (" << star->rectascension << ", " << star->declination << ") maps to (X, Y) (" << cartesianPosition.first << ", " << cartesianPosition.second << ")" << std::endl << std::endl;
}

int main(int argc, const char * argv[])
{
    // Build the constellation maps
    typedef boost::bimap<SkyAtlas::ConstellationCode, std::string> mapType;
    typedef boost::bimap<SkyAtlas::ConstellationCode, std::string>::value_type mapElementType;
    mapType constellations;
    for (size_t i = 0; i < sizeof(SkyAtlas::ConstellationNames) / sizeof(std::pair<SkyAtlas::ConstellationCode, std::string>); ++i)
    {
        constellations.insert(mapElementType(SkyAtlas::ConstellationNames[i].first, boost::to_upper_copy(SkyAtlas::ConstellationNames[i].second)));
    }
    
    // Create a sky to put the stars into
    boost::shared_ptr<SkyAtlas::SkyRectangle> wholeSkyRectangle(new SkyAtlas::SkyRectangle(0.0, 24.0, -90.0, 90.0));
    SkyAtlas::SkyGrid wholeSky(wholeSkyRectangle);
    
    // Read in the star catalogue
    std::ifstream starsInput("stars.dat", std::ifstream::in);
    unsigned long count = 0;
    while (starsInput.good())
    {
        boost::shared_ptr<SkyAtlas::Star> star(new SkyAtlas::Star(starsInput));
        
        boost::trim(star->constellation);
        
        mapType::right_const_iterator findIt = constellations.right.find(star->constellation);
        if (findIt != constellations.right.end())
        {
            SkyAtlas::ConstellationCode code = findIt->second;
            std::cout << code << std::endl;
        }
        else
        {
            assert(false);
        }
        
        wholeSky.AddStar(star);
        //std::cout << *star << std::string(10, '#') << std::endl;
        count++;
    }
    std::cout << count << " stars." << std::endl;
    
    // Visit a small viewport of stars
    std::cout << "Visiting stars..." << std::endl;
    std::pair<double, double> viewerRectacensionDeclination(-10.0, -10.0);
    double viewerAngle = 10.0;
    projection = boost::shared_ptr<SkyAtlas::StereographicProjection>(
        new SkyAtlas::StereographicProjection(viewerRectacensionDeclination, viewerAngle));
    boost::shared_ptr<SkyAtlas::SkyRectangle> viewport = projection->GetViewport();
    std::cout << *projection;
    std::cout << *viewport;
    wholeSky.VisitStars(viewport, visitor);
    
    // Plot a small viewport of stars
    
    // Read in the constellation lines
    std::ifstream linesInput("lines.dat", std::ifstream::in);
    count = 0;
    while (linesInput.good())
    {
        const SkyAtlas::Constellation constellation(linesInput);
        std::cout << constellation << std::string(10, '#') << std::endl;
        count++;
    }
    std::cout << count << " constellations." << std::endl;
    
    return 0;
}
