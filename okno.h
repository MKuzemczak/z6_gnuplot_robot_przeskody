#ifndef OKNO_H
#define OKNO_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QKeyEvent>
#include <QCheckBox>
#include <QLabel>
#include <QValidator>
#include <QComboBox>
#include <list>


#include "emitter.h"
#include "SWektor.hh"
#include "Wektor3D.hh"
#include "Scene.hh"

class Okno : public QWidget
{
    Q_OBJECT

private:
    QPushButton *moveButton, *rotateButton;                 /** Przyciski do ruszenia robota */

    QPushButton *setVelButton, *setRotVelButton;            /** Przyciski do ustawiania prędkości ruchu */

    QLineEdit *moveVal, *rotateVal;                         /** Pola tekstowe z wartościami do ruszenia */

    QLabel *moveValLabel, *rotateValLabel;                  /** Etykiety powyższych z jednostkami */

    QLineEdit *moveVelocityVal, *rotateVelocityVal;         /** Pola tesktowe z wartościami prędkości */

    QLabel *moveVelocityValLabel, *rotateVelocityValLabel;  /** Etykiety powyższych z jednostkami */

    QCheckBox *cameraFollow, *keepAxisValsRatio;            /** Checkboxy do śledzenia robota i zachowywania proporcji osi */

    std::vector<QLineEdit*> axisVals;                       /** Pola tekstowe z zakresami osi */

    std::vector<QLabel*> axisValsLabels;                    /** Etykiety powyższych */

    QPushButton *setAxisVals;                               /** Przycisk ustawienia zakresów osi */

    QValidator *validator;                                  /** Obiekt przypisywany do pól tekstowych aby ograniczyc
                                                              * tekst do nich wprowadzany do integerów */

    QComboBox *selectRobot;                                 /** Lista rozwijana wyboru robota */

    QLabel *selectRobotLabel;                               /** Etykieta listy rozwijanej wyboru robota */

    QPushButton *addRobot;

    Emitter *emiter;                                        /** Emituje cykliczny sygnal w wątku */
    QLabel *SWektorAmount;                                  /** Wyswietla ilosc stworzonych obecnie obiektow SWektor */

    Scene sc;       /** Scena */

protected:
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);

public:
    explicit Okno(QWidget *parent = nullptr);
signals:

public slots:
    void sendRotateRobot();
    void sendMoveRobot();
    void sendRobotVel();
    void sendRobotRotVel();
    void sendCameraFollow();
    void sendAxisVals();
    void updateSWektorAmount();
    void setActiveRobot();
    void sendAddRobot();
};

#endif // OKNO_H
