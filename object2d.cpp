#include "object2d.h"

using namespace std;

///////////////////////////////////////////////////////////// Object2D
Object2D::Object2D()
{
    angleZ = 0;
}



void Object2D::move(const double x, const double y, const double z)
{
    Wektor3D V(x, y, z);

    getLoc() = V;
}
void Object2D::move(const Wektor3D & V)
{
    getLoc() = V;
}
void Object2D::rotate(const double aZ)
{
    angleZ = aZ;
}
void Object2D::goGlobal()
{
    ShapeVertices sha = vertices;

    sha.rotateAroundZ(angleZ);
    sha.addVector(getLoc());

    if(get_ver().size() == 0)
        get_ver().push_back(sha);
    else
        get_ver()[0] = sha;
}


////////////////////////////////////////////////////////////// Text2D

Text2D::Text2D(const std::string txt)
{
    text = txt;

    angleZ = 0;

    fontSize = 50;
}

void Text2D::setText(const string txt)
{
    text = txt;
}

void Text2D::setFontSize(const int size)
{
    fontSize = size;
}

void Text2D::stringToVertices(const std::string txt, ShapeVertices & sha, const int size)
{
    for(char l : txt)
        letterToVertices(l, sha, size);
}

void Text2D::letterToVertices(char l, ShapeVertices & sha, const int size)
{
    LineVertices lin;

    switch (l) {
    case 'a':
    case 'A':
        {
            Wektor3D v(-0.4*size, 0, 0);
            lin.push_back(v);
            v[0] = 0;
            v[2] = size;
            lin.push_back(v);
            v[0] = 0.4*size;
            v[2] = 0;
            lin.push_back(v);
            v[0] = 0.24 * size;
            v[2] = 0.4*size;
            lin.push_back(v);
            v[0] = -v[0];
            lin.push_back(v);
        }
        break;
    default:
        break;
    }
}
