#ifndef SCENE_HH
#define SCENE_HH

/*!
  * \file
  * \brief Zawiera definicję klasy Scene.
  */


#include <iostream>
#include <fstream>
#include <list>
#include <memory>
#include <QThread>
#include <QDebug>


#include "lacze_do_gnuplota.hh"
#include "Robot.hh"
#include "Path.hh"
#include "obstacle.h"
#include "gjk_collision_detection.h"


#define INIT_XMIN -500
#define INIT_XMAX 500
#define INIT_YMIN -500
#define INIT_YMAX 500
#define INIT_ZMIN 0
#define INIT_ZMAX 450

template<typename T>
class lista : public std::list<T>
{
public:
    T operator [] (const int index)
    {
        int i = 0;
        for(T r : (*this))
        {
            if(i == index)
                return r;
            i++;
        }
    }
};

/*!
 * \brief Klasa sceny. Modeluje pojęcie sceny jako obiektu zawierającego obiekty
 * do wyrysowania i łącze do gnuplota.
 */
class Scene : public QThread{

    /*!
     * \brief Obiekt udostepniajacy interfejst do gnuplota w kodzie.
     */
    PzG::LaczeDoGNUPlota Lacze;

    Robot robot;
    Path path;


    lista<std::shared_ptr<Robot>> robots;
    lista<std::shared_ptr<ObiektGraficzny>> objects;

    int activeRobot;

    /*!
     * \brief Kierunek przemieszczenia
     *
     * Zmienna odpowiedzialna za określenia kierunku przemieszczenia
     * w przód lub w tył. Przyjmuje wartość -1 lub 1
     */
    int movement_direction;

    /*!
     * \brief Kierunek obrotu
     *
     * Zmienna odpowiedzialna za określenia kierunku obrotu
     * w lewo lub w prawo. Przyjmuje wartość -1 lub 1
     */
    int rotation_direction;

    /*!
     * \brief Ilość klatek na sekundę
     *
     * Przechowuje informację jak często ekran jest aktualizowany podczas ruchu
     */
    int fps;

    bool _moving;           /** flaga przemieszczania klawiaturą */
    bool _rotating;         /** flaga obrotu klawiaturą */
    bool _threadRunning;    /** flaga sygnalizująca, że wątek sterowania klawiaturą jest odpalony */
    bool _cameraFollow;     /** flaga mowiąca czy kamera ma podążać za robotem */
    bool _drawPath;         /** flaga mówiąca czy ścieżka ma być rysowana */

    /*!
     * \brief Zapis wszystkich obiektów do jednego pliku
     * \return Powodzenie operacji.
     */
    bool save() ;
public:

    /*!
     * \brief Konstruktor
     *
     * Ustawia flagi, kierunki i fps;
     * Konfiguruje obszar roboczy gnuplota.
     */
    Scene();

    /*!
     * \brief Kod wykonywany w wątku sterowania klawiaturą.
     *
     * Wykonuje algorytmy przemieszczenia i obrotu robota,
     * jeśli ich flagi są ustawione.
     * Zapisuje i aktualizuje obszar roboczy.
     */
    void run();

    void addRobot();
    void deleteActiveRobot();
    void activateRobot(int i);

    int getActiveRobotIndex() {return activeRobot;}
    const std::shared_ptr<Robot> getActiveRobot() {return robots[activeRobot];}

    bool activeRobotCollision();
    /*!
     * \brief Animowane przemieszczenie robota o dystans.
     *
     * Wykonuje w pętli ruch robota co (1/fps) sekundy,
     * dopóki nie osiągnie zadanego dystansu.
     * Stosowane do dużych odległości.
     *
     * \param distance - odległość do pokonania.
     */
    void moveRobot(double distance);

    /*!
     * \brief Natychmiastowe przemieszczenie robota o dystans.
     *
     * Wykonuje natychmiastowe przemieszczenie robota
     * o zadaną odległość do przodu. Stosowane do krótkich, jednostkowych dystansów.
     *
     * \param distance - odległość do pokonania.
     */
    void moveRobotInsta(double distance);

    /*!
     * \brief Animowany obrót robota.
     *
     * Wykonuje w pętli obrót robota co (1/fps) sekundy,
     * dopóki nie osiągnie zadanego kąta.
     * Stosowane do dużych kątów.
     *
     * \param angle - kąt o który ma się obrócić robot z aktualnej pozycji.
     */
    void rotateRobot(double angle);

    /*!
     * \brief Natychmiastowy obrót robota.
     *
     * Wykonuje natychmiastowy obrót robota
     * o zadany kąt. Stosowane do krótkich, jednostkowych obrotów.
     *
     * \param angle - kąt o który ma się obrócić robot z aktualnej pozycji.
     */
    void rotateRobotInsta(double angle);

    /*!
     * \brief Setter prędkości - atrybutu klasy Robot
     * \param v - prędkość do ustawienia w unit/s
     */
    void setRobotVelocity(double v);


    /*!
     * \brief Getter prędkości - atrybutu klasy Robot
     */
    double getRobotVelocity() { return robots[activeRobot]->getVel();}


    /*!
     * \brief Setter prędkości obrotu - atrybutu klasy Robot
     * \param v - prędkość kątowa do ustawienia w rad/s
     */
    void setRobotRotVelocity(double v);


    /*!
     * \brief Getter prędkości obrotu - atrybutu klasy Robot
     */
    double getRobotRotVelocity() { return robots[activeRobot]->getRotVel();}

    /*!
     * \brief Setter kierunku przesuwania - atrybutu klasy Robot
     * \param d - kierunek: \n 1 - do przodu, \n -1 - do tyłu.
     */
    void setMovementDirection(const int d) { movement_direction = d; }

    /*!
     * \brief Setter kierunku obrotu - atrybutu klasy Robot
     * \param d - kierunek: \n 1 - w prawo, \n-1 - w lewo.
     */
    void setRotationDirection(const int d) { rotation_direction = d; }

    /*!
     * \brief Getter flagi sygnalizującej, czy wątek ruchu jest odpalony.
     * \return true - wątek działa, false - nie działa.
     */
    bool isThreadRunnig() { return _threadRunning; }

    /*!
     * \brief Setter flagi sygnalizującej, że w wątku ruchu należy przesuwać robota.
     */
    void setThreadMoving() { _moving = true; }

    /*!
     * \brief Setter flagi sygnalizującej, że w wątku ruchu należy obracać robota.
     */
    void setThreadRotating() { _rotating = true; }

    /*!
     * \brief Unsetter flagi sygnalizującej, że w wątku ruchu należy przesuwać robota.
     */
    void clearThreadMoving() { _moving = false; if(!_rotating) _threadRunning = false; }

    /*!
     * \brief Unsetter flagi sygnalizującej, że w wątku ruchu należy obracać robota.
     */
    void clearThreadRotating() { _rotating = false; if(!_moving) _threadRunning = false; }

    /*!
     * \brief Setter flagi śledzenia robota przez kamerę.
     * \param s - stan flagi do ustawienia:\n true - podąża za robotem,\n false - nie podąża.
     */
    void setCameraFollow(const bool s);

    /*!
     * \brief Setter zakresów osi obszaru roboczego
     * \param tab - tablica wartości. Sześć elementów: Xmin, Xmax, Ymin, Ymax, Zmin, Zmax.
     * \param keep - powiadamia, czy należy zachować proporcje.
     */
    void setAxisVals(int *tab, bool keep);

    /*!
     * \brief Getter zakresów osi obszaru roboczego.
     * \param tab - tablica sześciu liczb: Xmin, Xmax, Ymin, Ymax, Zmin, Zmax,
     *               do której metoda zapisuje zakresy osi.
     */
    void getAxisVals(int *tab);

    /*!
     * \brief Przełącznik flagi decydującej o rysowaniu ścieżki.
     */
    void toggleDrawPath();


    /*!
     * \brief Getter ilości robotów na scenie.
     * \return Ilość robotów.
     */
    int getRobotAmount() {return robots.size();}

    /*!
   * \brief Metoda zapisuje do pliku współrzędne wierzchołków
   */
    template <typename Typ>
    bool ZapiszDoPliku(const char *sNazwaPliku, Vertices<Typ> ver) const;

};

#endif

