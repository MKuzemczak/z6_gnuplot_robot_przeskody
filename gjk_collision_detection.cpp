#include "gjk_collision_detection.h"


void Simplex::add(const Wektor3D & v)
{
    push_back(v);
}

Wektor3D & Simplex::getLast()
{
    return at(size() - 1);
}

bool Simplex::containsOrigin()
{
    if(size() < 4)
        return false;

    Wektor3D A = at(0), B = at(1), C = at(2), D = at(3), zero;

    Wektor3D A0 = zero - A, B0 = zero - B;

    Wektor3D AC = C - A;
    Wektor3D AB = B - A;
    Wektor3D AD = D - A;
    Wektor3D BC = C - B;
    Wektor3D BD = D - B;

    Wektor3D ACD = AD.cross(AC);
    Wektor3D ABC = AB.cross(AC);
    Wektor3D ABD = AB.cross(AD);
    Wektor3D BCD = BC.cross(BD);

    if(ACD * AB > 0)
        ACD = ACD * (-1);
    if(ABC * AD > 0)
        ABC = ABC * (-1);
    if(ABD * AC > 0)
        ABD = ABD * (-1);
    if(BCD * (AB * (-1)) > 0)
        BCD = BCD * (-1);



    if(ACD * A0 > 0)
    {
        erase(++begin());
        directionToReturn = ACD;
        return false;
    }
    if(ABD * A0 > 0)
    {
        erase(--(--end()));
        directionToReturn = ABD;
        return false;
    }
    if(BCD * B0 > 0)
    {
        erase(begin());
        directionToReturn = BCD;
        return false;
    }

    return true;
}

const Wektor3D Simplex::getDirection()
{

    if(size() == 2)
    {
        Wektor3D AB = at(1) - at(0);
        Wektor3D A0 = at(0) * (-1);
        Wektor3D ret = (AB.cross(A0));
        ret = ret * 0.000001;
        ret = ret.cross(AB);

        return ret;
    }
    if(size() == 3)
    {
        Wektor3D CB = at(1) - at(2), CA = at(0) - at(2);
        Wektor3D CBA = CB.cross(CA);
        Wektor3D C0 = at(2) * (-1);

        if(CBA.cross(CA) * C0 > 0)
        {
            // środek za odcinkiem CA, usuwam punkt B
            // i szukam w kierunku za CA
            erase(++begin());

            Wektor3D ret = CA.cross(C0);
            ret = ret * 0.000001;
            ret = ret.cross(CA);
            return ret;
        }
        if((CBA.cross(CB) * (-1)) * C0 > 0)
        {
            // środek za odcinkiem CB, usuwam punkt A
            // i szukam w kierunku za CB
            erase(begin());

            Wektor3D ret = CB.cross(C0);
            ret = ret * 0.000001;
            ret = ret.cross(CB);
            return ret;
        }
        if(CBA * C0 > 0)
            // srodek nad trójkątem
            return CBA;

        // środek pod trójkątem
        return CBA * (-1);

    }

    return directionToReturn;
}

Wektor3D getFarthestPoint(const LineVertices & shape, const Wektor3D & d)
{
    double dot = shape[0] * d;
    double tmpdot;

    int index = 0;

    for(unsigned int i = 0; i < shape.size(); i++)
    {
        tmpdot = shape[i] * d;

        if(tmpdot > dot)
        {
            dot = tmpdot;

            index = i;
        }
    }

    return shape[index];
}

Wektor3D support(const LineVertices & shape1, const LineVertices & shape2, const Wektor3D & d)
{
    Wektor3D p1 = getFarthestPoint(shape1, d);
    Wektor3D p2 = getFarthestPoint(shape2, d*(-1));

    Wektor3D ret = p1 - p2;
    return ret;
}


bool gjk_collision(const LineVertices & shape1, const LineVertices & shape2)
{
    Simplex simplex;

    Wektor3D d(1,1,1);

    simplex.add(support(shape1, shape2, d));

    d = d * (-1);

    while(1)
    {
        simplex.add(support(shape1, shape2, d));

        if(simplex.getLast() * d <= 0)
        {
            return false;
        }
        else
        {
            if(simplex.containsOrigin())
            {
                return true;
            }
            else
                d = simplex.getDirection();
        }

    }
}
