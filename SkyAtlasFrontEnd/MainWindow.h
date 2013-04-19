//
//  MainWindow.h
//  SkyAtlas
//
//  Created by Adam French on 19/04/2013.
//  Copyright (c) 2013 Adam French. All rights reserved.
//

#ifndef __SkyAtlas__MainWindow__
#define __SkyAtlas__MainWindow__

#include <QWidget>

namespace FrontEnd
{

    class SkyWidget;

    class MainWindow : public QWidget
    {
        //Q_OBJECT
        
    public:
        MainWindow();
        
    private:
        SkyWidget *skyWidget;
    };

}

#endif /* defined(__SkyAtlas__MainWindow__) */
