#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "ObiektGraficzny.hh"

class Obstacle : public ObiektGraficzny
{
    Vertices<ShapeVertices> vertices;

    LineVertices collisionRectangle;
public:
    Obstacle(int x, int y, int z, double width, double height, int baseVertixAmount);
    Obstacle(const Wektor3D & location, double width, double height, int baseVertixAmount);

    void addShape(const ShapeVertices sha) { vertices.push_back(sha); }
    void goGlobal();
    void make_polygon3D(ShapeVertices & sha, double radius, double height, double vertixAmount);
};

#endif // OBSTACLE_H
