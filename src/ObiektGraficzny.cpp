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


void ObiektGraficzny::scanBounds(Vertices<ShapeVertices> obj, double *tab)
{
    tab[0] = obj[0][0][0][0];
    tab[1] = obj[0][0][0][1];
    tab[2] = obj[0][0][0][2];
    tab[3] = obj[0][0][0][0];
    tab[4] = obj[0][0][0][1];
    tab[5] = obj[0][0][0][2];

    for(ShapeVertices & sha : obj)
        for(LineVertices & lin : sha)
            for(Wektor3D & vec : lin)
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
}
