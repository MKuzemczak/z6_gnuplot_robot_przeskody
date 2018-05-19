/*!
 * \file
 * \brief Zawiera definicje metod klasy ObiektGraficzny
 *
 * Zawiera definicje metod klasy ObiektGraficzny
 * wraz z ich opisem.
 */

#include <fstream>
#include "ObiektGraficzny.hh"


using namespace std;


void ObiektGraficzny::scanBounds(Vertices<ShapeVertices> obj, ShapeVertices & sha)
{
    LineVertices lin;
    double tab[6];

    for(ShapeVertices & shape : obj)
    {
        tab[0] = shape[0][0][0];
        tab[1] = shape[0][0][1];
        tab[2] = shape[0][0][2];
        tab[3] = shape[0][0][0];
        tab[4] = shape[0][0][1];
        tab[5] = shape[0][0][2];


        for(LineVertices & line : shape)
            for(Wektor3D & vec : line)
            {
                if(vec[0] < tab[0])
                    tab[0] = vec[0];
                if(vec[1] < tab[1])
                    tab[1] = vec[1];
                if(vec[2] < tab[2])
                    tab[2] = vec[2];
                if(vec[0] > tab[3])
                    tab[3] = vec[0];
                if(vec[1] > tab[4])
                    tab[4] = vec[1];
                if(vec[2] > tab[5])
                    tab[5] = vec[2];
            }

        lin.push_back(Wektor3D(tab[0], tab[1], tab[2]));
        lin.push_back(Wektor3D(tab[3], tab[1], tab[2]));
        lin.push_back(Wektor3D(tab[0], tab[4], tab[2]));
        lin.push_back(Wektor3D(tab[3], tab[4], tab[2]));
        lin.push_back(Wektor3D(tab[0], tab[1], tab[5]));
        lin.push_back(Wektor3D(tab[3], tab[1], tab[5]));
        lin.push_back(Wektor3D(tab[0], tab[4], tab[5]));
        lin.push_back(Wektor3D(tab[3], tab[4], tab[5]));

        sha.push_back(lin);

        lin.clear();
    }
}
