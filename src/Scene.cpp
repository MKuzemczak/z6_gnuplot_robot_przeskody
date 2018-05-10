#include <iostream>
#include <unistd.h>
#include <QCoreApplication>
#include <QDebug>

#include "Scene.hh"


using namespace std;



Scene::Scene()
{
    _moving = false;
    _rotating = false;
    _threadRunning = false;
    _cameraFollow = false;
    _drawPath = true;

    activeRobot = 0;

    movement_direction = 1;
    rotation_direction = 1;
    fps = 35;

    Lacze.DodajNazwePliku("dane.dat");
    Lacze.ZmienTrybRys(PzG::TR_3D);
    Lacze.Inicjalizuj(); // Tutaj startuje gnuplot.

    Lacze.UstawZakresX(INIT_XMIN, INIT_XMAX);
    Lacze.UstawZakresY(INIT_YMIN, INIT_YMAX);
    Lacze.UstawZakresZ(INIT_ZMIN, INIT_ZMAX);

    Lacze.UstawRotacjeXZ(45, 0); // Tutaj ustawiany jest widok

    robots.push_back(Robot());


    robots.push_back(Robot(Wektor3D(200, 0, 0)));

    save();

    Lacze.Rysuj();

    path.addVertix(robots[activeRobot].getLoc());
}

void Scene::run()
{
    /*_threadRunning = true;

    while(_moving || _rotating)
    {
        if(_moving)
        {
            moveRobotInsta(movement_direction * robot.vel() / fps);
        }
        if (_rotating)
        {
            rotateRobotInsta(rotation_direction * robot.rotVel() / fps);
        }

        save();

        Lacze.Rysuj();

        usleep(1000000/fps);
    }
    */

    _threadRunning = true;

    while(_moving || _rotating)
    {
        if(_moving)
        {
            moveRobotInsta(movement_direction * robots[activeRobot].getVel() / fps);
        }
        if (_rotating)
        {
            rotateRobotInsta(rotation_direction * robots[activeRobot].getRotVel() / fps);
        }

        save();

        Lacze.Rysuj();

        usleep(1000000/fps);
    }
}

void Scene::activateRobot(int i)
{
    activeRobot = i;

    ShapeVertices sha;

    LineVertices lin;

    sha.push_back(lin);

    path.addShape(sha);

    if(_cameraFollow)
    {
        setCameraFollow(true);
    }

}

void Scene::addRobot()
{
    Wektor3D l;

    bool collides = false;

    do
    {

        collides = false;

        for(Robot & r : robots)
        {
            if(fabs(r.getLoc()[0] - l[0]) < 200)
                collides = true;
        }

        if(collides)
            l[0] += 200;
    } while (collides);

    robots.push_back(Robot(l));

    save();

    Lacze.Rysuj();
}

void Scene::moveRobot(double distance)
{
    /*Wektor3D translation;

    double t = distance/robot.vel();
    double interval = distance/(fps*t);
    double tab[3] = {interval * sin(robot.ang()), interval * cos(robot.ang()),0};

    if(_drawPath)
        path.addVertix(robot.loc());

    translation.set(tab);

    for(double i = 0; i < distance; i+=interval)
    {
        robot.move(translation);

        if(_drawPath)
            path.setLast(robot.loc());

        save();
        if(_cameraFollow)
        {
            Lacze.UstawZakresX(Lacze.Xmin() + translation[0], Lacze.Xmax() + translation[0]);
            Lacze.UstawZakresY(Lacze.Ymin() + translation[1], Lacze.Ymax() + translation[1]);
        }

        Lacze.Rysuj();

        usleep(1000000/fps);
    }*/

    Wektor3D translation;

    double t = distance/robots[activeRobot].getVel();
    double interval = distance/(fps*t);
    double tab[3] = {interval * sin(robots[activeRobot].getAng()), interval * cos(robots[activeRobot].getAng()),0};

    if(_drawPath)
        path.addVertix(robots[activeRobot].getLoc());

    translation.set(tab);

    for(double i = 0; i < distance; i+=interval)
    {
        robots[activeRobot].move(translation);

        if(_drawPath)
            path.setLast(robots[activeRobot].getLoc());

        save();
        if(_cameraFollow)
        {
            Lacze.UstawZakresX(Lacze.Xmin() + translation[0], Lacze.Xmax() + translation[0]);
            Lacze.UstawZakresY(Lacze.Ymin() + translation[1], Lacze.Ymax() + translation[1]);
        }

        Lacze.Rysuj();

        usleep(1000000/fps);
    }
}

void Scene::moveRobotInsta(double distance)
{
    /*Wektor3D translation;

    double tab[3] = {distance * sin(robot.ang()), distance * cos(robot.ang()),0};

    if(_drawPath)
        path.addVertix(robot.loc());

    translation.set(tab);
    robot.move(translation);

    if(_drawPath)
        path.setLast(robot.loc());

    if(_cameraFollow)
    {
        Lacze.UstawZakresX(Lacze.Xmin() + translation[0], Lacze.Xmax() + translation[0]);
        Lacze.UstawZakresY(Lacze.Ymin() + translation[1], Lacze.Ymax() + translation[1]);
    }*/

    Wektor3D translation;

    double tab[3] = {distance * sin(robots[activeRobot].getAng()), distance * cos(robots[activeRobot].getAng()),0};

    if(_drawPath)
        path.addVertix(robots[activeRobot].getLoc());

    translation.set(tab);
    robots[activeRobot].move(translation);

    if(_drawPath)
        path.setLast(robots[activeRobot].getLoc());

    if(_cameraFollow)
    {
        Lacze.UstawZakresX(Lacze.Xmin() + translation[0], Lacze.Xmax() + translation[0]);
        Lacze.UstawZakresY(Lacze.Ymin() + translation[1], Lacze.Ymax() + translation[1]);
    }
}


void Scene::rotateRobot(double angle)
{
    /*int degRobotAngle;
    double t = fabs(angle)/robot.rotVel();
    double interval = angle/(fps*t);

    for(double i = 0; i < fabs(angle); i+=fabs(interval))
    {
        robot.rotate(interval);
        save();

        if(_cameraFollow)
        {
            degRobotAngle = RADTODEG * robot.ang();
            Lacze.UstawRotacjeZ(360-degRobotAngle);
        }

        Lacze.Rysuj();

        usleep(1000000/fps);
    }*/

    int degRobotAngle;
    double t = fabs(angle)/robots[activeRobot].getRotVel();
    double interval = angle/(fps*t);

    for(double i = 0; i < fabs(angle); i+=fabs(interval))
    {
        robots[activeRobot].rotate(interval);
        save();

        if(_cameraFollow)
        {
            degRobotAngle = RADTODEG * robots[activeRobot].getAng();
            Lacze.UstawRotacjeZ(360-degRobotAngle);
        }

        Lacze.Rysuj();

        usleep(1000000/fps);
    }
}

void Scene::rotateRobotInsta(double angle)
{
    /*int degRobotAngle;

    robot.rotate(angle);

    degRobotAngle = (int) (RADTODEG * robot.ang()) % 360;

    if(robot.ang() < 0)
    {
        degRobotAngle = 360 + degRobotAngle;
        robot.ang() = DOUBLEPI + robot.ang();
    }

    if(_cameraFollow)
        Lacze.UstawRotacjeZ(360-degRobotAngle);*/

    int degRobotAngle;

    robots[activeRobot].rotate(angle);

    degRobotAngle = (int) (RADTODEG * robots[activeRobot].getAng()) % 360;

    if(robots[activeRobot].getAng() < 0)
    {
        degRobotAngle = 360 + degRobotAngle;
        robots[activeRobot].getAng() = DOUBLEPI + robots[activeRobot].getAng();
    }

    if(_cameraFollow)
        Lacze.UstawRotacjeZ(360-degRobotAngle);

}


void Scene::setRobotVelocity(double v)
{
    //robot.vel() = v;

    robots[activeRobot].getVel() = v;
}
void Scene::setRobotRotVelocity(double v)
{
    //robot.rotVel() = v;

    robots[activeRobot].getRotVel() = v;
}

void Scene::setCameraFollow(const bool s)
{
    if(s)
    {
        _cameraFollow = true;

        Lacze.UstawZakresX(robots[activeRobot].getLoc()[0]-(Lacze.Xmax() - Lacze.Xmin())/2, robots[activeRobot].getLoc()[0] + (Lacze.Xmax() - Lacze.Xmin())/2);
        Lacze.UstawZakresY(robots[activeRobot].getLoc()[1]-(Lacze.Ymax() - Lacze.Ymin())/2, robots[activeRobot].getLoc()[1] + (Lacze.Ymax() - Lacze.Ymin())/2);

        Lacze.UstawRotacjeZ(360 - (robots[activeRobot].getAng() * RADTODEG));

        Lacze.Rysuj();
    }
    else
        _cameraFollow = false;
}

void Scene::setAxisVals(int *tab, bool keep)
{
    double ratio = 1;

    if(keep)
    {/*
        if(tab[0] != Lacze.Xmin() || tab[1] != Lacze.Xmax())
            ratio = (tab[1] - tab[0])/(Lacze.Xmax() - Lacze.Xmin());
        else if(tab[2] != Lacze.Ymin() || tab[3] != Lacze.Ymax())
            ratio = (tab[3] - tab[2])/(Lacze.Ymax() - Lacze.Ymin());
        else if(tab[4] != Lacze.Zmin() || tab[5] != Lacze.Zmax())
            ratio = (tab[5] - tab[4])/(Lacze.Zmax() - Lacze.Zmin());
*/
        if(tab[0] != Lacze.Xmin())
            ratio = (((Lacze.Xmax() - Lacze.Xmin())/2) + Lacze.Xmin() - tab[0])/((Lacze.Xmax() - Lacze.Xmin())/2);
        else if(tab[1] != Lacze.Xmax())
            ratio = (tab[1] - (((Lacze.Xmax() - Lacze.Xmin())/2) + Lacze.Xmin()))/((Lacze.Xmax() - Lacze.Xmin())/2);
        else if(tab[2] != Lacze.Ymin())
            ratio = (((Lacze.Ymax() - Lacze.Ymin())/2) + Lacze.Xmin() - tab[2])/((Lacze.Ymax() - Lacze.Ymin())/2);
        else if(tab[3] != Lacze.Ymax())
            ratio = (tab[3] - (((Lacze.Ymax() - Lacze.Ymin())/2) + Lacze.Ymin()))/((Lacze.Ymax() - Lacze.Ymin())/2);
        else if(tab[4] != Lacze.Zmin())
            ratio = (((Lacze.Zmax() - Lacze.Xmin())/2) + Lacze.Xmin() - tab[4])/((Lacze.Zmax() - Lacze.Zmin())/2);
        else if(tab[5] != Lacze.Zmax())
            ratio = (tab[5] - (((Lacze.Zmax() - Lacze.Zmin())/2) + Lacze.Zmin()))/((Lacze.Zmax() - Lacze.Zmin())/2);

        Lacze.UstawZakresX((Lacze.Xmin() + (Lacze.Xmax() - Lacze.Xmin())/2) - ratio * (Lacze.Xmax() - Lacze.Xmin())/2,\
                           (Lacze.Xmin() + (Lacze.Xmax() - Lacze.Xmin())/2) + ratio * (Lacze.Xmax() - Lacze.Xmin())/2);
        Lacze.UstawZakresY((Lacze.Ymin() + (Lacze.Ymax() - Lacze.Ymin())/2) - ratio * (Lacze.Ymax() - Lacze.Ymin())/2,\
                           (Lacze.Ymin() + (Lacze.Ymax() - Lacze.Ymin())/2) + ratio * (Lacze.Ymax() - Lacze.Ymin())/2);
        Lacze.UstawZakresZ(0, (Lacze.Zmin() + (Lacze.Zmax() - Lacze.Zmin())/2) + ratio * (Lacze.Zmax() - Lacze.Zmin())/2);

        tab[0] = Lacze.Xmin();
        tab[1] = Lacze.Xmax();
        tab[2] = Lacze.Ymin();
        tab[3] = Lacze.Ymax();
        tab[4] = Lacze.Zmin();
        tab[5] = Lacze.Zmax();
    }
    else
    {
        Lacze.UstawZakresX(tab[0], tab[1]);
        Lacze.UstawZakresY(tab[2], tab[3]);
        Lacze.UstawZakresZ(tab[4], tab[5]);
    }
    Lacze.Rysuj();
}

void Scene::getAxisVals(int *tab)
{
    tab[0] = Lacze.Xmin();
    tab[1] = Lacze.Xmax();
    tab[2] = Lacze.Ymin();
    tab[3] = Lacze.Ymax();
    tab[4] = Lacze.Zmin();
    tab[5] = Lacze.Zmax();
}

void Scene::toggleDrawPath()
{
    if(!_drawPath)
    {
        ShapeVertices sha;
        LineVertices lin;

        sha.push_back(lin);

        path.addShape(sha);

        _drawPath = true;
    }
    else
        _drawPath = false;
}

bool Scene::save()  
{
    /*Vertices<ShapeVertices> drawing;

    drawing = robot.ver();

    drawing.rotateAroundZ(robot.ang());
    drawing.addVector(robot.loc());

    for(ShapeVertices sha : path.ver())
        drawing.push_back(sha);

    return ZapiszDoPliku<ShapeVertices>("dane.dat", drawing);*/

    Vertices<ShapeVertices> singleObject;
    Vertices<ShapeVertices> drawing;

    for(Robot & r : robots)
    {
        singleObject = r.ver();

        singleObject.rotateAroundZ(r.getAng());
        singleObject.addVector(r.getLoc());

        for(ShapeVertices & s : singleObject)
            drawing.push_back(s);
    }

    for(ShapeVertices sha : path.ver())
        drawing.push_back(sha);

    return ZapiszDoPliku<ShapeVertices>("dane.dat", drawing);
}

template <typename Typ>
bool Scene::ZapiszDoPliku(const char* sNazwaPliku, Vertices<Typ> ver) const
{
  std::ofstream   StrmWy(sNazwaPliku);

  if (!StrmWy.is_open()) {
    std::cerr << std::endl
         << "Blad: Otwarcie do zapisu pliku '" << sNazwaPliku
     << "' nie powiodlo sie." << std::endl
     << std::endl;
    return false;
  }

  StrmWy << ver;

  return !StrmWy.fail();
}
