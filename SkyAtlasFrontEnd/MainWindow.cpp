//
//  MainWindow.cpp
//  SkyAtlas
//
//  Created by Adam French on 19/04/2013.
//  Copyright (c) 2013 Adam French. All rights reserved.
//

#include <QtGui>
#include <QGridLayout>
#include "MainWindow.h"
#include "SkyWidget.h"

FrontEnd::MainWindow::MainWindow()
{
    skyWidget = new SkyWidget;
    
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(3, 1);
    mainLayout->addWidget(skyWidget, 0, 0, 1, 4);
    setLayout(mainLayout);
    
    setWindowTitle(tr("SkyAtlas"));
}
