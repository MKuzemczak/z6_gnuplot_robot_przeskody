#ifndef OBJECT2D_H
#define OBJECT2D_H

#include <string>
#include "ObiektGraficzny.hh"

class Object2D : public ObiektGraficzny
{
    ShapeVertices vertices;

    double angleZ;
public:
    Object2D();


    void move(const double x, const double y, const double z);
    void move(const Wektor3D & V);
    void rotate(const double aZ);
    void goGlobal();

};

class Text2D : public Object2D
{
    std::string text;
    int fontSize;

public:
    Text2D(const std::string txt);

    void setText(const std::string txt);
    void setFontSize(const int size);
    void stringToVertices(const std::string txt, ShapeVertices & sha, const int size);
    void letterToVertices(char l, ShapeVertices & sha, const int size);
};
#endif // OBJECT2D_H
