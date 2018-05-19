#include "obstacle.h"
#include "gjk_collision_detection.h"

/*Obstacle::Obstacle(int x, int y, int z, double width, double height, int baseVertixAmount)
{

    ShapeVertices sha;

    Wektor3D location(x,y,z);

    getLoc() = location;

    make_polygon3D(sha, width/2, height, baseVertixAmount);
    addShape(sha);


    scanBounds(vertices, collisionRectangle);

    goGlobal();
}

Obstacle::Obstacle(const Wektor3D & location, double width, double height, int baseVertixAmount)
{
    ShapeVertices sha;

    getLoc() = location;

    make_polygon3D(sha, width/2, height, baseVertixAmount);
    addShape(sha);

    scanBounds(vertices, collisionRectangle);

    goGlobal();
}

*/
void Obstacle::goGlobal()
{
    get_ver() = vertices;
    get_ver().rotateAroundZ(getAngleZRad());
    get_ver().addVector(getLoc());

    get_colRect() = collisionRectangle;
    get_colRect().rotateAroundZ(getAngleZRad());
    get_colRect().addVector(getLoc());
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
///////////////////////////////////////////////////////////////////////////// SquareObstacle

SquareObstacle::SquareObstacle(const double x, const double y, const double z,
                               const double height, const double width, const double angleRad)
{
    Wektor3D location(x, y, z);

    getLoc() = location;

    setAngleZRad(angleRad);

    ShapeVertices sha;
    LineVertices lin;

    Wektor3D v;
    lin.push_back(v);

    v[0] = width/2;
    v[1] = -v[0];
    lin.push_back(v);

    v[2] = height;
    lin.push_back(v);

    v[0] = v[1] = 0;
    lin.push_back(v);

    sha.push_back(lin);

    lin[1][1] = lin[2][1] = width/2;
    sha.push_back(lin);

    lin[1][0] = lin[2][0] = -width/2;
    sha.push_back(lin);

    lin[1][1] = lin[2][1] = -width/2;
    sha.push_back(lin);

    lin[1][0] = lin[2][0] = width/2;
    sha.push_back(lin);

    addShape(sha);

    scanBounds(getVer(), getColRect());

    goGlobal();
}

bool SquareObstacle::collides(const ObiektGraficzny & obj)
{
    for(LineVertices & lin0 : get_colRect())
        for(const LineVertices & lin1 : obj.get_colRect())
            if(gjk_collision(lin0, lin1))
                return true;

    return false;
}


////////////////////////////////////////////////////////////////////////// PolygonObstacle
PolygonObstacle::PolygonObstacle(const int x, const  int y, const int z,
                const double width, const double height,
                const int baseVertixAmount, const double angleRad)
{
    ShapeVertices sha;

    Wektor3D location(x,y,z);

    getLoc() = location;
    setAngleZRad(angleRad);

    make_polygon3D(sha, width/2, height, baseVertixAmount);
    addShape(sha);


    scanBounds(getVer(), getColRect());

    goGlobal();
}


bool PolygonObstacle::collides(const ObiektGraficzny & obj)
{
    for(LineVertices & lin0 : get_colRect())
        for(const LineVertices & lin1 : obj.get_colRect())
            if(gjk_collision(lin0, lin1))
                return true;

    return false;
}

///////////////////////////////////////////////////////////////////////////// PenisObstacle
PenisObstacle::PenisObstacle(const double x, const double y, const double z,
                             const double length, const double angleRad)
{
    Wektor3D location(x,y,z);

    getLoc() = location;
    setAngleZRad(angleRad);

    ShapeVertices sha;

    ////////////////////////////////////////////////////// balls
    make_ball(Wektor3D(length/5, 0, 0), length/5, sha);
    addShape(sha);

    make_ball(Wektor3D(-length/5, 0, 0), length/5, sha);
    addShape(sha);

    ////////////////////////////////////////////////////// penis
    LineVertices lin, lin0;

    for(int i = 0; i < 2; i++)
        lin.push_back(Wektor3D(0,0,0));

    lin[0][0] = length/10;
    lin[1][0] = length/10;
    lin[1][2] = length;

    double interval = PI/4;

    sha.clear();

    lin0 = lin;
    sha.push_back(lin0);

    for(int i = 1; i < 9; i++)
    {
        lin0 = lin;
        lin0.rotateAroundZ(i * interval);
        sha.push_back(lin0);
    }

    addShape(sha);

    make_ball(Wektor3D(0,0,length), length/7, sha);
    addShape(sha);

    scanBounds(getVer(), getColRect());

    goGlobal();
}


void PenisObstacle::make_ball(const Wektor3D location,
                              const double radius,ShapeVertices & sha)
{
    LineVertices lin, lin0;

    sha.clear();

    for(int i = 0; i < 5; i++)
        lin.push_back(Wektor3D(0,0,0));

    lin[0][2] = radius;
    lin[1][0] = radius*sqrt(2)/2;
    lin[1][2] = radius*sqrt(2)/2;
    lin[2][0] = radius;
    lin[3][0] = radius*sqrt(2)/2;
    lin[3][2] = -radius*sqrt(2)/2;
    lin[4][2] = -radius;

    double interval = PI/4;

    lin0 = lin;
    lin0.addVector(location);
    sha.push_back(lin0);

    for(int i = 1; i < 9; i++)
    {
        lin0 = lin;
        lin0.rotateAroundZ(i * interval);
        lin0.addVector(location);
        sha.push_back(lin0);
    }
}

bool PenisObstacle::collides(const ObiektGraficzny & obj)
{
    for(LineVertices & lin0 : get_colRect())
        for(const LineVertices & lin1 : obj.get_colRect())
            if(gjk_collision(lin0, lin1))
                return true;

    return false;
}
