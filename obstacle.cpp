#include "obstacle.h"

Obstacle::Obstacle(int x, int y, int z, double width, double height, int baseVertixAmount)
{

    ShapeVertices sha;

    Wektor3D location(x,y,z);

    getLoc() = location;

    make_polygon3D(sha, width/2, height, baseVertixAmount);
    addShape(sha);


    LineVertices lin;

    double tab[6];

    scanBounds(vertices, tab);

    lin.push_back(Wektor3D(tab[0], tab[1], tab[2]));
    lin.push_back(Wektor3D(tab[3], tab[1], tab[2]));
    lin.push_back(Wektor3D(tab[0], tab[4], tab[2]));
    lin.push_back(Wektor3D(tab[3], tab[4], tab[2]));
    lin.push_back(Wektor3D(tab[0], tab[1], tab[5]));
    lin.push_back(Wektor3D(tab[3], tab[1], tab[5]));
    lin.push_back(Wektor3D(tab[0], tab[4], tab[5]));
    lin.push_back(Wektor3D(tab[3], tab[4], tab[5]));

    collisionRectangle = lin;

    goGlobal();
}

Obstacle::Obstacle(const Wektor3D & location, double width, double height, int baseVertixAmount)
{
    ShapeVertices sha;

    getLoc() = location;

    make_polygon3D(sha, width/2, height, baseVertixAmount);
    addShape(sha);


    LineVertices lin;

    double tab[6];

    scanBounds(vertices, tab);

    lin.push_back(Wektor3D(tab[0], tab[1], tab[2]));
    lin.push_back(Wektor3D(tab[3], tab[1], tab[2]));
    lin.push_back(Wektor3D(tab[0], tab[4], tab[2]));
    lin.push_back(Wektor3D(tab[3], tab[4], tab[2]));
    lin.push_back(Wektor3D(tab[0], tab[1], tab[5]));
    lin.push_back(Wektor3D(tab[3], tab[1], tab[5]));
    lin.push_back(Wektor3D(tab[0], tab[4], tab[5]));
    lin.push_back(Wektor3D(tab[3], tab[4], tab[5]));

    collisionRectangle = lin;

    goGlobal();
}


void Obstacle::goGlobal()
{
    get_ver() = vertices;
    get_ver().addVector(getLoc());

    getColRect() = collisionRectangle;
    getColRect().addVector(getLoc());
}

void Obstacle::make_polygon3D(ShapeVertices & sha, double radius, double height, double vertixAmount)
{
    LineVertices lin;

    for(int i = 0; i < 4; i++)
    {
        Wektor3D v;
        lin.push_back(v);
    }

    double tab[4][3] = {
        {0, 0, 0},
        {radius, 0, 0},
        {radius, 0, height},
        {0, 0, height},
    };

    double interval = DOUBLEPI / vertixAmount;

    for(int j = 0; j < 4; j++)
    {
        lin[j].set(tab[j]);
    }

    for(double i = 0; i < DOUBLEPI+0.1; i += interval)
    {
        for(int j = 0; j < 4; j++)
        {
            lin[j][0] = cos(i) * tab[j][0];
            lin[j][1] = sin(i) * tab[j][0];
        }

        sha.push_back(lin);
    }
}
