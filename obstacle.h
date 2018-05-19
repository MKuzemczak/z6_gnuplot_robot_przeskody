#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "ObiektGraficzny.hh"

enum ObstacleType {POLYGON, SQUARE, PENIS};

class Obstacle : public ObiektGraficzny
{
    Vertices<ShapeVertices> vertices;

    ShapeVertices collisionRectangle;

    double angleZRad;
public:
    Obstacle() : angleZRad() {}
    //Obstacle(int x, int y, int z, double width, double height, int baseVertixAmount);
    //Obstacle(const Wektor3D & location, double width, double height, int baseVertixAmount);

    Vertices<ShapeVertices> & getVer() { return vertices; }
    ShapeVertices & getColRect() { return collisionRectangle; }
    const double & getAngleZRad() const { return angleZRad; }
    void setAngleZRad(const double a) { angleZRad = a; }

    void rotateZ(const double a) { angleZRad += a; goGlobal(); }

    void addShape(const ShapeVertices sha) { vertices.push_back(sha); }
    void goGlobal();
    void make_polygon3D(ShapeVertices & sha, double radius, double height, double vertixAmount);

    bool collides(const ObiektGraficzny & obj);
};

class SquareObstacle : public Obstacle {
public:
    SquareObstacle(const double x, const double y, const double z,
                   const double height, const double width,
                   const double angleRad);

    bool collides(const ObiektGraficzny &obj);
};

class PolygonObstacle : public Obstacle {
public:
    PolygonObstacle(const int x, const  int y, const int z,
                    const double width, const double height,
                    const int baseVertixAmount,
                    const double angleRad);

    bool collides(const ObiektGraficzny &obj);
};

class PenisObstacle : public Obstacle {
public:
    PenisObstacle(const double x, const double y, const double z,
                  const double length, const double angleRad);

    bool collides(const ObiektGraficzny &obj);
    void make_ball(const Wektor3D location,
                   const double radius,ShapeVertices & sha);
};

#endif // OBSTACLE_H
