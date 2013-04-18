//
//  SkyAtlasFrontEnd.cpp
//  SkyAtlas
//
//  Created by Adam French on 18/04/2013.
//
//

#include <QApplication>
#include <QPushButton>

int main(int argc, char **argv)
{
    QApplication app (argc, argv);
    
    QPushButton button ("SkyAtlas !");
    button.show();
    
    return app.exec();
}