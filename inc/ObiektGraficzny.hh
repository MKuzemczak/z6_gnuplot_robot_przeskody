#ifndef OBIEKTGRAFICZNY_HH
#define OBIEKTGRAFICZNY_HH

/*!
 * \file
 * \brief Definicja klasy ObiektGraficzny
 *
 * Plik zawiera definicję klasy ObiektGraficzny.
 */


#include <iostream>
#include <fstream>
#include <vector>
#include <QObject>

#include "Wektor3D.hh"
#include "Vertices.hh"
#include "gjk_collision_detection.h"



#define RADTODEG 57.2957795131
#define DOUBLEPI 6.28318530718
#define PI 3.14159265359

/*!
 * \brief Modeluje obiekt, który ma swoją reprezentację graficzną
 *
 * Modeluje obiekt, który ma swoją reprezentację graficzną
 * w postaci łamanej. Może ona być łamaną zamkniętą w postaci
 * wieloboku lub otwartą. Ilość jej wierzchołków nie jest jawnie
 * ograniczona. Jedynym ograniczeniem jest dostępność pamięci
 * komputera.
 */
class ObiektGraficzny {

    /*!
     * \brief Wektor położenia w układzie globalnym
     */
    Wektor3D _location;
    /*!
     * \brief Zbiór wierzchołków
     *
     * Pole zawiera wektor obiektów ShapeVertices,
     * złożonych z krzywych łamancyh LineVertives,
     * złożonych z wierzchołków Wektor3D
     *
     */
    Vertices<ShapeVertices> _vertices;

    ShapeVertices _collisionRectangle;

public:


    /*!
     * \brief Getter wektora lokalizacji
     * \return Wektor lokalizacji obiektu w postaci modyfikowalnej
     */
    Wektor3D & getLoc () { return _location; }


    /*!
     * \brief Getter wektora lokalizacji
     * \return Wektor lokalizacji obiektu w postaci modyfikowalnej
     */
    const Wektor3D & getLoc () const { return _location; }


    /*!
     * \brief Getter zbioru wierzchołków
     * \return Wektor elementów składowych obiektu w postaci modyfikowalnej.
     */
    Vertices<ShapeVertices> & get_ver() { return _vertices; }

    /*!
     * \brief Getter zbioru wierzchołków
     * \return Wektor elementów składowych obiektu w postaci modyfikowalnej.
     */
    const Vertices<ShapeVertices> & get_ver() const { return _vertices; }

    /*!
     * \brief Getter zbioru wierzchołków prostopadłościanu od kolizji.
     * \return Wektor typu LineVertices wierchołków prostopadłościanu.
     */
    ShapeVertices & get_colRect() { return _collisionRectangle; }

    /*!
     * \brief Getter zbioru wierzchołków prostopadłościanu od kolizji.
     * \return Wektor typu LineVertices wierchołków prostopadłościanu.
     */
    const ShapeVertices & get_colRect() const { return _collisionRectangle; }

    /*!
     * \brief Dodanie kształtu do zbioru wierzchołków.
     * \param sha - obiekt do dodania, zawierający krzywe łamane
     */
    void _addShape(const ShapeVertices sha) { _vertices.push_back(sha); }

    void scanBounds(Vertices<ShapeVertices> obj, ShapeVertices & sha);

    /*!
     * \brief Dodanie wektora na koniec.
     * Dodaje wektor na koniec ostatniej krzywej ostatniego kształtu.
     *
     * \param v - wektor wierzchołka do dodania.
     */
    void _push_back(const Wektor3D v) { _vertices[_vertices.size() - 1][_vertices[_vertices.size() - 1].size() - 1].push_back(v); }

    virtual bool collides(const ObiektGraficzny & obj) = 0;
};

#endif
