//
//  SkyWidget.h
//  SkyAtlas
//
//  Created by Adam French on 19/04/2013.
//  Copyright (c) 2013 Adam French. All rights reserved.
//

#ifndef __SkyAtlas__SkyWidget__
#define __SkyAtlas__SkyWidget__

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>

namespace FrontEnd
{

    class SkyWidget : public QWidget
    {
        //Q_OBJECT
        
    public:
        
        SkyWidget(QWidget *parent = 0);
        
        QSize minimumSizeHint() const;
        QSize sizeHint() const;
        
    protected:
        void paintEvent(QPaintEvent *event);
        
    private:

    };
    
}

#endif /* defined(__SkyAtlas__SkyWidget__) */
