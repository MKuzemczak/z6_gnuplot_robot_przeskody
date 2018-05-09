#ifndef VERTICES_HH
#define VERTICES_HH

/*!
  * \file
  * \brief Zawiera definicję szablonu klasy Vertices<Typ>
  */

#include <vector>
#include "Wektor3D.hh"


/*!
 * \brief Szablon klasy Vertices
 *
 * Pozwala na translację i obrót zbioru wierzchołków
 */
template <typename Typ>
class Vertices : public std::vector<Typ> {

public:

    /*!
     * \brief Dodaje Wektor3D do wszystkich wektorów 3D występujących w zbiorze wierzchołków
     * \param v - wektor do dodania
     */
    void addVector(const Wektor3D & v);

    /*!
     * \brief Obraca wszystkie wektory współrzędnych wierzchołków wokół osi Z
     * \param a - kąt, o który użytkownik chce obrócić wektory (w radianach)
     */
    void rotateAroundZ(const double a);
};

/*!
 * \brief Typ definiujący krzywą łamaną jako zbiór wierzchołków
 */
typedef Vertices<Wektor3D> LineVertices;

/*!
 * \brief Typ definiujący kształt jako zbiór krzywych łamanych połączonych płaszczyznami
 */
typedef Vertices<Vertices<Wektor3D>> ShapeVertices;

template <typename Typ>
std::ostream & operator << (std::ostream & out, Vertices<Typ> V) // przeniesc deklaracje do *.cpp
{
    for (Typ p : V)
    {
        out << p;
    }

    return out;
}

template<>
 inline std::ostream & operator << <Wektor3D> (std::ostream & out, Vertices<Wektor3D> l)
{
    for (Wektor3D v : l)
    {
        out << v << std::endl;
    }
    
    return out;
}

template<>
inline std::ostream & operator << <Vertices<Wektor3D>> (std::ostream & out, Vertices<Vertices<Wektor3D>> s)
{
    for (unsigned int i = 0; i < s.size() - 1; i++)
    {
        out << s[i] << "#\n\n";
    }

    out << s[s.size() - 1] << "\n\n";

    return out;
}

template<>
inline void Vertices<Wektor3D>::addVector(const Wektor3D & v)
{
    for(Wektor3D & u : (*this))
    {
        u += v;
    }
}

template<>
inline void Vertices<LineVertices>::addVector(const Wektor3D & v)
{
    for(LineVertices & l : (*this))
    {
        l.addVector(v);
    }
}

template<>
inline void Vertices<ShapeVertices>::addVector(const Wektor3D & v)
{
    for(ShapeVertices & s : (*this))
    {
        s.addVector(v);
    }
}


template<>
inline void Vertices<Wektor3D>::rotateAroundZ(const double a)
{
    for(Wektor3D & u : (*this))
    {
        double tab[3] = {u[0]*cos(a) + u[1]*sin(a), -u[0]*sin(a) + u[1]*cos(a), u[2]};

        u.set(tab);
    }
}

template<>
inline void Vertices<LineVertices>::rotateAroundZ(const double a)
{
    for(LineVertices & l : (*this))
    {
        l.rotateAroundZ(a);
    }
}

template<>
inline void Vertices<ShapeVertices>::rotateAroundZ(const double a)
{
    for(ShapeVertices & s : (*this))
    {
        s.rotateAroundZ(a);
    }
}
#endif
