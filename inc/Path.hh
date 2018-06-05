#ifndef PATH_HH
#define PATH_HH

/*!
  * \file
  * \brief Definicja klasy Path
  */

#include "ObiektGraficzny.hh"


/*!
 * \brief Klasa ścieżki. Udostępnia interfejs tworzenia łamanej.
 *
 * Modeluje pojęcie prostej łąmanej.
 * Dziedziczy po klasie ObiektGraficzny wektor kształtów,
 * do którego zapisuje jeden kształt ShapeVertices, skłądający sie z
 * jednej łamanej LineVertices, składającej się z wierzchołków Wektor3D.
 */
class Path : ObiektGraficzny {

public:
    /*!
     * \brief Konstruktor
     *
     * Dodaje do listy kształtów kształt z pustą łamaną.
     */
    Path();

    /*!
     * \brief Dodaje kształt do listy.
     * \param sha - kształt do dodania.
     */
    void addShape(const ShapeVertices sha) { _addShape(sha); }

    /*!
     * \brief Dodaje wierzchołek - Wektor3D na koniec łamanej.
     * \param v - werzchołek, Wektor3D do dodania.
     */
    void addVertix(const Wektor3D & v);

    /*!
     * \brief Modyfikuje ostatni wierzchołek łamanej.
     * \param v - nowy wektor na który ma być zamieniony ten już istniejący.
     */
    void setLast(const Wektor3D & v);

    /*!
     * \brief Getter zbioru kształtów, w tym wypadku wierzchołków łamanej.
     * \return Wektor zawierający kształt, który zawiera łamaną.
     */
    Vertices<ShapeVertices> ver() { return get_ver(); }

    /*!
     * \brief Czyści łamaną.
     */
    void clear();

    bool collides(const ObiektGraficzny & obj) {}
};


#endif
