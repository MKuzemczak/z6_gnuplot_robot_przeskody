#ifndef CREATE_H
#define CREATE_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QDebug>
#include <QButtonGroup>
#include <QRadioButton>

#include "obstacle.h"

class createRobot : public QDialog
{
    Q_OBJECT


    QPushButton *add, *cancel;
    QLineEdit *heightInput, *nameInput;
    QLabel *heightLabel, *nameLabel;

    double height;
    QString name;

    bool ret;

public:
    createRobot();
    bool execute(double & h, QString & n);

public slots:
    void saveData();
    void setCancelRet();
    void setAddRet();
};

class createObstacle : public QDialog
{
    Q_OBJECT

    QPushButton *add, *cancel;

    QLineEdit *widthInput, *heightInput,
              *vertixAmtInput,
              *xInput, *yInput, *zInput;

    QLabel *widthLabel, *heightLabel,
           *vertixAmtLabel,
           *xLabel, *yLabel, *zLabel;


    QButtonGroup *selectObstacleTypeButtonGroup;

    QRadioButton *selectPolygonType,
                 *selectSquareType,
                 *selectPenisType;

    ObstacleType selectedObstacleType;

    double w, h,
           xPos, yPos, zPos;

    int vertixAmt;

    bool ret;


public:
    createObstacle();

    bool execute(double &x, double &y, double &z,
                 double & width, double & height,
                 int & vertixAmount, ObstacleType & type);

public slots:
    void saveData();
    void setCancelRet();
    void setAddRet();
    void obstacleTypeSelected(int choice);
};

#endif // CREATE_H
