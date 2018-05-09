#include <iostream>
#include <iomanip>
#include <QApplication>

#include "Scene.hh"
#include "lacze_do_gnuplota.hh"
#include "Vertices.hh"
#include "Robot.hh"
#include "Path.hh"
#include "okno.h"

using namespace std;

int main(int argc, char **argv)
{
    QApplication app (argc, argv);

    Okno okno0;

    okno0.show();
    return app.exec();
}
