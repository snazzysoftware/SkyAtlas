//
//  SkyAtlasFrontEnd.cpp
//  SkyAtlas
//
//  Created by Adam French on 18/04/2013.
//
//

#include <QApplication>
#include <QPushButton>
#include "MainWindow.h"

int main(int argc, char **argv)
{
    //Q_INIT_RESOURCE(basicdrawing);

    QApplication app(argc, argv);
    FrontEnd::MainWindow window;
    window.show();
    return app.exec();
}
