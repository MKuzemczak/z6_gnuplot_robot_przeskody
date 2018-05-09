#include "Path.hh"

Path::Path()
{
    ShapeVertices sha;
    LineVertices lin;

    sha.push_back(lin);
    _addShape(sha);
}

void Path::addVertix(const Wektor3D & v)
{
    _push_back(v);
}

void Path::setLast(const Wektor3D & v)
{
    _ver()[_ver().size() - 1][_ver()[_ver().size() - 1].size() - 1][_ver()[_ver().size() - 1]\
            [_ver()[_ver().size() - 1].size() - 1].size() - 1] = v;
}

void Path::clear()
{
    _ver().clear();
}
