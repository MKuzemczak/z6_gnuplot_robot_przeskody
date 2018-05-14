#ifndef GJK_COLLISION_DETECTION_H
#define GJK_COLLISION_DETECTION_H

#include <vector>
#include <QDebug>

#include "Wektor3D.hh"
#include "Vertices.hh"

class Simplex : public std::vector<Wektor3D>
{
    Wektor3D directionToReturn;

public:
    void add(const Wektor3D & v);
    Wektor3D & getLast();
    bool containsOrigin();
    const Wektor3D  getDirection();
};


Wektor3D getFarthestPoint(const LineVertices & shape, const Wektor3D & d);

Wektor3D support(const LineVertices & shape1, const LineVertices & shape2, const Wektor3D & d);

bool gjk_collision(const LineVertices & shape1, const LineVertices & shape2);

#endif // GJK_COLLISION_DETECTION_H
