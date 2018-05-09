#ifndef ROBOT_HH
#define ROBOT_HH

/*!
  * \file
  * \brief Definicja klasy Robot
  */

#include "Vertices.hh"
#include "ObiektGraficzny.hh"

#define INIT_VELOCITY 500
#define INIT_ROTATION_VELOCITY 4


/*!
 * \brief Klasa Robota. Udostepnia interfejsc budowania i poruszania robotem.
 *
 * Tworzy obiekt Robot, który jest obiektem graficznym.
 * Składa się ze zbioru kształtów, ich wektor dziedziczy po klasie
 * ObiektGraficzny.
 * Zawiera pola pamiętające prędkość ruchu i obrotu robota, a także kąt
 * Obrotu wokół osi Z od kąta zero.
 */
class Robot : public ObiektGraficzny {
    /*!
     * \brief Kąt obrotu robota od kąta zero.
     */
    double angle;

    /*!
     * \brief Prędkość robota w jednostkach na sekundę.
     */
    double velocity;

    /*!
     * \brief Prędkość robota w radianach na sekundę.
     */
    double rotVelocity;

    
public:
    /*!
     * \brief Konstruktor
     *
     * Ustawia odpowiednie prędkości, kąt 0.
     * Dodaje do zbioru kształtów odpowiednie obiekty tworzące ciało robota.
     */
    Robot();

    /*!
     * \brief Przesuwa robota zadany dystans.
     *
     * Przesuwa robota o distance w kierunku okreslonym przez pole Robot::angle.
     *
     * \param distance - Odleglosc o jaką robot ma się poruszyć.
     */
    void move(const double distance);

    /*!
     * \brief Przesuwa robota o zadany wektor.
     *
     * Dodaje do wektora lokalizacji bezwzględnej  podany wektor.
     *
     * \param translation - wektor przesunięcia do zastosowania.
     */
    void move(const Wektor3D translation);

    /*!
     * \brief Obraca robota o podany kąt w radianach.
     *
     * Metoda zmienia pole prywatne Robot::angle, które jest poźniej używane przy
     * zapisaniu i wyświetlaniu odpowiedniego zbioru punktów.
     *
     * \param angle - kąt o który należy obrócić obrota.
     */
    void rotate(double angle);

    /*!
     * \brief Metoda tworzy prostopadłościan.
     *
     * Tworzy prostopadłościan o zadanych wymiarach z prostych łamanych
     * i zapisuje go w podanym kształcie.
     *
     * \param sha - obiekt ShapeVertices przechowujący stworzony prostopadłościan.
     * \param width - szerokość, wymiar X.
     * \param depth - głębokość, wymiar Y.
     * \param height - wysokość, wymiar Z.
     * \param loc - wektor położenia kształtu względem układu lokalnego robota.
     */
    void make_box(ShapeVertices & sha, int width, int depth, int height, Wektor3D loc);

    /*!
     * \brief Metoda tworzy koło pojazdu.
     *
     * Metoda ta w pętli obraca przekrój koła aby uzyskać pełny model 3D.
     *
     * \param sha - obiekt ShapeVertices przechowujący stworzony prostopadłościan.
     * \param radius - promień koła.
     * \param facingAngle - kąt obrotu osi koła wokół osi Z
     * \param loc - wektor położenia kształtu względem ukłądu lokalnego robota.
     */
    void make_tire(ShapeVertices & sha, double radius, double facingAngle, const Wektor3D & loc);

    /*!
     * \brief Getter zbioru wierzchołków.
     * \return Wektor kształtów dziedziczony po klasie ObiektGraficzny w postaci modyfikowalnej.
     */
    Vertices<ShapeVertices> & ver() { return _ver(); }


    /*!
     * \brief Getter kąta obrotu od zera.
     * \return Kąt obrotu w radianach.
     */
    double & ang() {return angle;}

    /*!
     * \brief Getter prędkosci przesunięcia.
     * \return Wartość prędkości w jednostkach na sekundę.
     */
    double & vel() {return velocity;}

    /*!
     * \brief Getter prędkości obrotu.
     * \return Wartość prędkości w radianach na sekundę.
     */
    double & rotVel() {return rotVelocity;}

};

#endif
