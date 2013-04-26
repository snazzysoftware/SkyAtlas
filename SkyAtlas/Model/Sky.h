//
//  Sky.h
//  SkyAtlas
//
//  Created by Adam French on 27/03/2013.
//  Copyright (c) 2013 Adam French. All rights reserved.
//

#ifndef __SkyAtlas__Sky__
#define __SkyAtlas__Sky__

#include <vector>
#include <boost/shared_ptr.hpp>
#include "Star.h"

namespace SkyAtlas
{
    
    class SkyRectangle
    {
        
    public:
        
        SkyRectangle(double minRectacensionInclusive,
                     double maxRectacensionExclusive,
                     double minDeclinationInclusive,
                     double maxDeclinationExclusive);
        
        std::pair<
        boost::shared_ptr<SkyAtlas::SkyRectangle>,
        boost::shared_ptr<SkyAtlas::SkyRectangle> >
        SplitByRectacension();
        
        std::pair<
        boost::shared_ptr<SkyAtlas::SkyRectangle>,
        boost::shared_ptr<SkyAtlas::SkyRectangle> >
        SplitByDeclination();
        
        bool CouldContain(boost::shared_ptr<Star> star);
        bool CouldContain(std::pair<double, double> rectacensionDeclination);
        
        bool Overlaps(boost::shared_ptr<SkyRectangle> area);
        
        double minRectacensionInclusive;
        double maxRectacensionExclusive;
        double minDeclinationInclusive;
        double maxDeclinationExclusive;
        
    };
    
    enum SPLIT_DIRECTION
    {
        RECTACENSION_SPLIT,
        DECLINATION_SPLIT
    };
    
    class Sky
    {
        
    public:
        
        virtual boost::shared_ptr<SkyRectangle> GetCoverage() = 0;
        
        virtual void AddStar(boost::shared_ptr<Star> star) = 0;
        
        virtual void GetStars(boost::shared_ptr<std::vector<boost::shared_ptr<SkyAtlas::Star> > > result) = 0;
        
        virtual bool NeedsToSplit() = 0;
        
        virtual boost::shared_ptr<Sky> Split() = 0;
        
        virtual std::vector<boost::shared_ptr<SkyAtlas::Star> >::size_type StarCount() = 0;
        
        virtual std::vector<boost::shared_ptr<SkyAtlas::Star> >::size_type Inbalance() = 0;
        
        virtual void VisitStars(boost::shared_ptr<SkyRectangle> area, void (*visitor)(boost::shared_ptr<Star>)) = 0;
        
        virtual void VisitStars(boost::shared_ptr<SkyRectangle> area, void (*visitor)(boost::shared_ptr<Star>, void* context), void* context) = 0;
        
        virtual ~Sky() { }
        
    };
    
    class SkyGrid : public Sky
    {
        
    public:
        
        SkyGrid(boost::shared_ptr<SkyRectangle> coverage);
        
        SkyGrid(boost::shared_ptr<SkyRectangle> coverage, SPLIT_DIRECTION direction);
        
        virtual boost::shared_ptr<SkyRectangle> GetCoverage();
        
        virtual void AddStar(boost::shared_ptr<Star> star);
        
        virtual void GetStars(boost::shared_ptr<std::vector<boost::shared_ptr<SkyAtlas::Star> > > result);
        
        virtual bool NeedsToSplit();
        
        virtual boost::shared_ptr<Sky> Split();
        
        virtual std::vector<boost::shared_ptr<SkyAtlas::Star> >::size_type StarCount();
        
        virtual std::vector<boost::shared_ptr<SkyAtlas::Star> >::size_type Inbalance();
        
        virtual void VisitStars(boost::shared_ptr<SkyRectangle> area, void (*visitor)(boost::shared_ptr<Star>));
        
        virtual void VisitStars(boost::shared_ptr<SkyRectangle> area, void (*visitor)(boost::shared_ptr<Star>, void* context), void* context);
        
        virtual ~SkyGrid();
        
    private:
        
        boost::shared_ptr<Sky> sky1;
        boost::shared_ptr<Sky> sky2;
        boost::shared_ptr<SkyRectangle> coverage;
        
    };
    
    class SkyPatch : public Sky
    {
        
    public:
        
        SkyPatch(boost::shared_ptr<SkyRectangle> coverage);
        
        virtual boost::shared_ptr<SkyRectangle> GetCoverage();
        
        virtual void AddStar(boost::shared_ptr<Star> star);
        
        virtual void GetStars(boost::shared_ptr<std::vector<boost::shared_ptr<SkyAtlas::Star> > > result);
        
        virtual bool NeedsToSplit();
        
        virtual boost::shared_ptr<Sky> Split();
        
        virtual std::vector<boost::shared_ptr<SkyAtlas::Star> >::size_type StarCount();
        
        virtual std::vector<boost::shared_ptr<SkyAtlas::Star> >::size_type Inbalance();
        
        virtual void VisitStars(boost::shared_ptr<SkyRectangle> area, void (*visitor)(boost::shared_ptr<Star>));
        
        virtual void VisitStars(boost::shared_ptr<SkyRectangle> area, void (*visitor)(boost::shared_ptr<Star>, void* context), void* context);
        
        virtual ~SkyPatch();
        
    private:
        
        static const std::vector<boost::shared_ptr<SkyAtlas::Star> >::size_type MAX_STARS = 500;
        
        std::vector<boost::shared_ptr<Star> > stars;
        boost::shared_ptr<SkyRectangle> coverage;
        
    };
    
}

#endif /* defined(__SkyAtlas__Sky__) */
