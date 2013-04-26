//
//  Sky.cpp
//  SkyAtlas
//
//  Created by Adam French on 27/03/2013.
//  Copyright (c) 2013 Adam French. All rights reserved.
//

#include "Sky.h"

SkyAtlas::SkyRectangle::SkyRectangle(double minRectacensionInclusive,
                                     double maxRectacensionExclusive,
                                     double minDeclinationInclusive,
                                     double maxDeclinationExclusive) :
minRectacensionInclusive(minRectacensionInclusive),
maxRectacensionExclusive(maxRectacensionExclusive),
minDeclinationInclusive(minDeclinationInclusive),
maxDeclinationExclusive(maxDeclinationExclusive)
{
}

std::pair<
    boost::shared_ptr<SkyAtlas::SkyRectangle>,
    boost::shared_ptr<SkyAtlas::SkyRectangle> >
SkyAtlas::SkyRectangle::SplitByRectacension()
{
    double splitRectacension = (minRectacensionInclusive + maxRectacensionExclusive) / 2.0;
    return std::pair<
    boost::shared_ptr<SkyAtlas::SkyRectangle>,
    boost::shared_ptr<SkyAtlas::SkyRectangle> >
    (boost::shared_ptr<SkyAtlas::SkyRectangle>(new SkyRectangle(
        minRectacensionInclusive,
        splitRectacension,
        minDeclinationInclusive,
        maxDeclinationExclusive)),
     boost::shared_ptr<SkyAtlas::SkyRectangle>(new SkyRectangle(
        splitRectacension,
        maxRectacensionExclusive,
        minDeclinationInclusive,
        maxDeclinationExclusive)));
}

std::pair<
boost::shared_ptr<SkyAtlas::SkyRectangle>,
boost::shared_ptr<SkyAtlas::SkyRectangle> >
SkyAtlas::SkyRectangle::SplitByDeclination()
{
    double splitDeclination = (minDeclinationInclusive + maxDeclinationExclusive) / 2.0;
    return std::pair<
    boost::shared_ptr<SkyAtlas::SkyRectangle>,
    boost::shared_ptr<SkyAtlas::SkyRectangle> >
    (boost::shared_ptr<SkyAtlas::SkyRectangle>(new SkyRectangle(
        minRectacensionInclusive,
        maxRectacensionExclusive,
        minDeclinationInclusive,
        splitDeclination)),
     boost::shared_ptr<SkyAtlas::SkyRectangle>(new SkyRectangle(
        minRectacensionInclusive,
        maxRectacensionExclusive,
        splitDeclination,
        maxDeclinationExclusive)));
}

bool SkyAtlas::SkyRectangle::CouldContain(boost::shared_ptr<SkyAtlas::Star> star)
{
    if (star->rectascension >= minRectacensionInclusive &&
        star->rectascension < maxRectacensionExclusive &&
        star->declination >= minDeclinationInclusive &&
        star->declination < maxDeclinationExclusive)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool SkyAtlas::SkyRectangle::CouldContain(std::pair<double, double> rectacensionDeclination)
{
    if (rectacensionDeclination.first >= minRectacensionInclusive &&
        rectacensionDeclination.first < maxRectacensionExclusive &&
        rectacensionDeclination.second >= minDeclinationInclusive &&
        rectacensionDeclination.second < maxDeclinationExclusive)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool SkyAtlas::SkyRectangle::Overlaps(boost::shared_ptr<SkyRectangle> area)
{
    std::pair<double, double> minRectMinDec(area->minRectacensionInclusive, area->minDeclinationInclusive);
    std::pair<double, double> minRectMaxDec(area->minRectacensionInclusive, area->maxDeclinationExclusive);
    std::pair<double, double> maxRectMinDec(area->maxRectacensionExclusive, area->minDeclinationInclusive);
    std::pair<double, double> maxRectMaxDec(area->maxRectacensionExclusive, area->maxDeclinationExclusive);
    
    return
        CouldContain(minRectMinDec) ||
        CouldContain(minRectMaxDec) ||
        CouldContain(maxRectMinDec) ||
        CouldContain(maxRectMaxDec);
}

SkyAtlas::SkyGrid::SkyGrid(boost::shared_ptr<SkyRectangle> coverage) :
coverage(coverage)
{
    std::pair<
    boost::shared_ptr<SkyAtlas::SkyRectangle>,
    boost::shared_ptr<SkyAtlas::SkyRectangle> > split = coverage->SplitByRectacension();
    
    sky1 = boost::shared_ptr<Sky>(new SkyPatch(split.first));
    sky2 = boost::shared_ptr<Sky>(new SkyPatch(split.second));
}

SkyAtlas::SkyGrid::SkyGrid(boost::shared_ptr<SkyRectangle> coverage, SPLIT_DIRECTION direction) :
coverage(coverage)
{
    std::pair<
    boost::shared_ptr<SkyAtlas::SkyRectangle>,
    boost::shared_ptr<SkyAtlas::SkyRectangle> > split;
    
    if (direction == SkyAtlas::RECTACENSION_SPLIT)
    {
        split = coverage->SplitByRectacension();
    }
    else if (direction == SkyAtlas::DECLINATION_SPLIT)
    {
        split = coverage->SplitByDeclination();
    }
    
    sky1 = boost::shared_ptr<Sky>(new SkyPatch(split.first));
    sky2 = boost::shared_ptr<Sky>(new SkyPatch(split.second));
}

boost::shared_ptr<SkyAtlas::SkyRectangle> SkyAtlas::SkyGrid::GetCoverage()
{
    return coverage;
}

void SkyAtlas::SkyGrid::AddStar(boost::shared_ptr<Star> star)
{
    if (sky1->GetCoverage()->CouldContain(star))
    {
        if (sky1->NeedsToSplit())
        {
            sky1 = sky1->Split();
        }
        sky1->AddStar(star);
    }
    else if (sky2->GetCoverage()->CouldContain(star))
    {
        if (sky2->NeedsToSplit())
        {
            sky2 = sky2->Split();
        }
        sky2->AddStar(star);
    }
    else
    {
        assert(false);
    }
}

void SkyAtlas::SkyGrid::GetStars(boost::shared_ptr<std::vector<boost::shared_ptr<SkyAtlas::Star> > > result)
{
    sky1->GetStars(result);
    sky2->GetStars(result);
}

bool SkyAtlas::SkyGrid::NeedsToSplit()
{
    return false;
}

boost::shared_ptr<SkyAtlas::Sky> SkyAtlas::SkyGrid::Split()
{
    assert(false);
}

std::vector<boost::shared_ptr<SkyAtlas::Star> >::size_type SkyAtlas::SkyGrid::StarCount()
{
    return sky1->StarCount() + sky2->StarCount();
}

std::vector<boost::shared_ptr<SkyAtlas::Star> >::size_type SkyAtlas::SkyGrid::Inbalance()
{
    size_t size1 = sky1->StarCount();
    size_t size2 = sky2->StarCount();
    if (size1 > size2)
    {
        return size1 - size2;
    }
    else
    {
        return size2 - size1;
    }
}

void SkyAtlas::SkyGrid::VisitStars(boost::shared_ptr<SkyRectangle> area, void (*visitor)(boost::shared_ptr<Star>))
{
    if (sky1->GetCoverage()->Overlaps(area))
    {
        sky1->VisitStars(area, visitor);
    }
    
    if (sky2->GetCoverage()->Overlaps(area))
    {
        sky2->VisitStars(area, visitor);
    }
}

void SkyAtlas::SkyGrid::VisitStars(boost::shared_ptr<SkyRectangle> area, void (*visitor)(boost::shared_ptr<Star>, void* context), void* context)
{
    if (sky1->GetCoverage()->Overlaps(area))
    {
        sky1->VisitStars(area, visitor, context);
    }
    
    if (sky2->GetCoverage()->Overlaps(area))
    {
        sky2->VisitStars(area, visitor, context);
    }
}

SkyAtlas::SkyGrid::~SkyGrid()
{
}

SkyAtlas::SkyPatch::SkyPatch(boost::shared_ptr<SkyRectangle> coverage) :
coverage(coverage)
{
}

boost::shared_ptr<SkyAtlas::SkyRectangle> SkyAtlas::SkyPatch::GetCoverage()
{
    return coverage;
}

void SkyAtlas::SkyPatch::AddStar(boost::shared_ptr<Star> star)
{
    stars.push_back(star);
}

void SkyAtlas::SkyPatch::GetStars(
    boost::shared_ptr<std::vector<boost::shared_ptr<SkyAtlas::Star> > > result)
{
    result->insert(result->end(), stars.begin(), stars.end());
}

bool SkyAtlas::SkyPatch::NeedsToSplit()
{
    return stars.size() > MAX_STARS;
}

boost::shared_ptr<SkyAtlas::Sky> SkyAtlas::SkyPatch::Split()
{
    boost::shared_ptr<SkyGrid> rectacensionGrid(new SkyGrid(coverage, SkyAtlas::RECTACENSION_SPLIT));
    boost::shared_ptr<SkyGrid> declinationGrid(new SkyGrid(coverage, SkyAtlas::DECLINATION_SPLIT));

    for (std::vector<boost::shared_ptr<SkyAtlas::Star> >::iterator it = stars.begin();
         it != stars.end();
         ++it)
    {
        rectacensionGrid->AddStar(*it);
        declinationGrid->AddStar(*it);
    }
    
    if (rectacensionGrid->Inbalance() < declinationGrid->Inbalance())
    {
        std::cout << "Choosing to split sky patch by rectacension." << std::endl;
        return rectacensionGrid;
    }
    else
    {
        std::cout << "Choosing to split sky patch by declination." << std::endl;
        return declinationGrid;
    }
}

std::vector<boost::shared_ptr<SkyAtlas::Star> >::size_type SkyAtlas::SkyPatch::StarCount()
{
    return stars.size();
}

std::vector<boost::shared_ptr<SkyAtlas::Star> >::size_type SkyAtlas::SkyPatch::Inbalance()
{
    return 0;
}

void SkyAtlas::SkyPatch::VisitStars(boost::shared_ptr<SkyRectangle> area, void (*visitor)(boost::shared_ptr<Star>))
{
    for (std::vector<boost::shared_ptr<SkyAtlas::Star> >::iterator it = stars.begin();
         it != stars.end();
         ++it)
    {
        if (area->CouldContain(*it))
        {
            visitor(*it);
        }
    }
}

void SkyAtlas::SkyPatch::VisitStars(boost::shared_ptr<SkyRectangle> area, void (*visitor)(boost::shared_ptr<Star>, void* context), void* context)
{
    for (std::vector<boost::shared_ptr<SkyAtlas::Star> >::iterator it = stars.begin();
         it != stars.end();
         ++it)
    {
        if (area->CouldContain(*it))
        {
            visitor(*it, context);
        }
    }
}

SkyAtlas::SkyPatch::~SkyPatch()
{
}
