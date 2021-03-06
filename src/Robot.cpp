#include <iostream>
#include <cmath>
#include <unistd.h>
#include <QDebug>

#include "lacze_do_gnuplota.hh" //tymczasowo do poruszania
#include "Robot.hh"

using namespace std;

Robot::Robot()
{
    ShapeVertices sha;
    Wektor3D tmploc;

    double tab[3] = {0,0,0};

    getLoc().set(tab);

    angle = 0;
    velocity = INIT_VELOCITY;
    rotVelocity = INIT_ROTATION_VELOCITY;

    tmploc.set(tab);

    tmploc[0] = -10;
    tmploc[1] = 10;
    tmploc[2] = 50;
    make_tire(sha, 20, PI, tmploc);
    addShape(sha);
    sha.clear();

    tmploc[0] = 10;
    make_tire(sha, 20, 0, tmploc);
    addShape(sha);
    sha.clear();

    tmploc[0] = -30;
    tmploc[1] = 0;
    tmploc[2] = 50;
    make_box(sha, 20, 20, 80, tmploc);
    addShape(sha);
    sha.clear();

    tmploc[0] = 10;
    make_box(sha, 20, 20, 80, tmploc);
    addShape(sha);
    sha.clear();

    tmploc[0] = -30;
    tmploc[2] = 130;
    make_box(sha, 60, 30, 150, tmploc);
    addShape(sha);
    sha.clear();

    tmploc[0] = -50;
    tmploc[2] = 180;
    make_box(sha, 20, 20, 70, tmploc);
    addShape(sha);
    sha.clear();

    tmploc[2] -= 20;
    make_box(sha, 20, 80, 20, tmploc);
    addShape(sha);
    sha.clear();
    
    tmploc[0] = 30;
    make_box(sha, 20, 80, 20, tmploc);
    addShape(sha);
    sha.clear();

    tmploc[2] += 20;
    make_box(sha, 20, 20, 70, tmploc);
    addShape(sha);
    sha.clear();

    tmploc[0] = -20;
    tmploc[2] = 280;
    make_box(sha, 40, 25, 50, tmploc);
    addShape(sha);
    sha.clear();

    tmploc[0] = 30;
    tmploc[1] = 10;
    tmploc[2] = 51;
    make_tire(sha, 50, 0, tmploc);
    addShape(sha);
    sha.clear();

    tmploc[0] = -30;
    make_tire(sha, 50, PI, tmploc);
    addShape(sha);
    sha.clear();


    /////////////////////////////////////////////// making collision rectangle


    scanBounds(vertices, collisionRectangle);

    ////////////////////////////////////////////////


    goGlobal();
}

Robot::Robot(const Wektor3D & l, const double height)
{
    ShapeVertices sha;
    Wektor3D tmploc;

    double unit = height/33;
    double tab[3] = {0,0,0};

    getLoc() = l;

    angle = 0;
    velocity = INIT_VELOCITY;
    rotVelocity = INIT_ROTATION_VELOCITY;

    tmploc.set(tab);

    tmploc[0] = -unit;
    tmploc[1] = unit;
    tmploc[2] = 5*unit;
    make_tire(sha, 2*unit, PI, tmploc);
    addShape(sha);
    sha.clear();

    tmploc[0] = unit;
    make_tire(sha, 2*unit, 0, tmploc);
    addShape(sha);
    sha.clear();

    tmploc[0] = -3*unit;
    tmploc[1] = 0;
    tmploc[2] = 5*unit;
    make_box(sha, 2*unit, 2*unit, 8*unit, tmploc);
    addShape(sha);
    sha.clear();

    tmploc[0] = 1*unit;
    make_box(sha, 2*unit, 2*unit, 8*unit, tmploc);
    addShape(sha);
    sha.clear();

    tmploc[0] = -3*unit;
    tmploc[2] = 13*unit;
    make_box(sha, 6*unit, 3*unit, 15*unit, tmploc);
    addShape(sha);
    sha.clear();

    tmploc[0] = -5*unit;
    tmploc[2] = 18*unit;
    make_box(sha, 2*unit, 2*unit, 7*unit, tmploc);
    addShape(sha);
    sha.clear();

    tmploc[2] -= 2*unit;
    make_box(sha, 2*unit, 8*unit, 2*unit, tmploc);
    addShape(sha);
    sha.clear();

    tmploc[0] = 3*unit;
    make_box(sha, 2*unit, 8*unit, 2*unit, tmploc);
    addShape(sha);
    sha.clear();

    tmploc[2] += 2*unit;
    make_box(sha, 2*unit, 2*unit, 7*unit, tmploc);
    addShape(sha);
    sha.clear();

    tmploc[0] = -2*unit;
    tmploc[2] = 28*unit;
    make_box(sha, 4*unit, 2*unit, 5*unit, tmploc);
    addShape(sha);
    sha.clear();

    tmploc[0] = 3*unit;
    tmploc[1] = 1*unit;
    tmploc[2] = 5.1*unit;
    make_tire(sha, 5*unit, 0, tmploc);
    addShape(sha);
    sha.clear();

    tmploc[0] = -3*unit;
    make_tire(sha, 5*unit, PI, tmploc);
    addShape(sha);
    sha.clear();


    /////////////////////////////////////////////// making collision rectangle

    scanBounds(vertices, collisionRectangle);

    ////////////////////////////////////////////////

    goGlobal();
}


bool Robot::collides(const ObiektGraficzny & obj)
{
    for(LineVertices & lin0 : get_colRect())
        for(const LineVertices & lin1 : obj.get_colRect())
            if(gjk_collision(lin0, lin1))
                return true;

    return false;
}


void Robot::goGlobal()
{
    get_ver() = vertices;
    get_ver().rotateAroundZ(angle);
    get_ver().addVector(getLoc());

    get_colRect() = collisionRectangle;
    get_colRect().rotateAroundZ(angle);
    get_colRect().addVector(getLoc());
}

void Robot::move(const double distance)
{
    double tab[3] = {distance * sin(angle), distance * cos(angle),0};

    Wektor3D translation;

    translation.set(tab);

    getLoc() += translation;

    goGlobal();
}

void Robot::move(const Wektor3D translation)
{
    getLoc() += translation;

    goGlobal();
}

void Robot::rotate(double angle)
{
    this->angle += angle;

    this->angle = fmod(this->angle,DOUBLEPI);

    if(this->angle < 0)
        this->angle = DOUBLEPI + this->angle;

    goGlobal();
}

void Robot::make_box(ShapeVertices & sha, int width, int depth, int height, Wektor3D loc)
{
    LineVertices lin;
    Wektor3D vstart, vend, v;

    int tab[5][2] = {{0, 0}, {width, 0}, {width, height}, {0, height}, {0,0}};

    vstart[0] = loc[0] + width/2;
    vstart[1] = loc[1];
    vstart[2] = loc[2] + height/2;

    vend[0] = loc[0] + width/2;
    vend[1] = loc[1] + depth;
    vend[2] = loc[2] + height/2;

    for(int i = 0; i < 5; i++)
    {
        lin.clear();
        lin.push_back(vstart);

        v[0] = loc[0] + tab[i][0];
        v[1] = loc[1];
        v[2] = loc[2] + tab[i][1];
        
        lin.push_back(v);

        v[0] = loc[0] + tab[i][0];
        v[1] = loc[1] + depth;
        v[2] = loc[2] + tab[i][1];

        lin.push_back(v);
        lin.push_back(vend);

        sha.push_back(lin);
    }

}

void Robot::make_tire(ShapeVertices & sha, double radius, double facingAngle, const Wektor3D & loc)
{
    LineVertices lin;
    for(int i = 0; i < 7; i++)
    {
        Wektor3D v;
        lin.push_back(v);
    }

    double tab[7][3] = {
        {0, 0, 0},
        {0, 0, radius},
        {radius * cos(facingAngle), radius * sin(facingAngle), radius},
        {radius * cos(facingAngle), radius * sin(facingAngle), 0.4 * radius},
        {0.8 * radius * cos(facingAngle), 0.8 * radius * sin(facingAngle), 0.4 * radius},
        {0.5 * radius * cos(facingAngle), 0.8 * radius * sin(facingAngle), 0.25 * radius},
        {0.5 * radius * cos(facingAngle), 0.8 * radius * sin(facingAngle), 0}
    };

    double interval = DOUBLEPI / 20;

    double tab1[3];

    for(int j = 0; j < 7; j++)
    {
        tab1[0] = tab[j][0] + loc[0];
        tab1[1] = tab[j][1] + loc[1];
        tab1[2] = tab[j][2] + loc[2];

        lin[j].set(tab1);
    }

    for(double i = 0; i < DOUBLEPI; i += interval)
    {
        for(int j = 0; j < 7; j++)
        {
            lin[j][1] = loc[1] + sin(i) * tab[j][2];
            lin[j][2] = loc[2] + cos(i) * tab[j][2];
        }

        sha.push_back(lin);
    }
}
