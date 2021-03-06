#include <iostream>
#include <QCoreApplication>
#include <QDebug>
#include <QThread>

#include "okno.h"

using namespace  std;



Okno::Okno(QWidget *parent) : QWidget(parent)
{

    setFocusPolicy(Qt::ClickFocus);

    // ustawienie wielkosci okna
    setFixedSize(400, 550);

    validator = new QIntValidator(-100000, 100000, this);

    // stworzenie przycisku przemieszczenia robota
    moveButton = new QPushButton("Idź", this);
    moveButton->setGeometry(50, 225, 100, 50);
    moveButton->setFocusPolicy(Qt::NoFocus);

    // stworzenie przycisku obrotu robota
    rotateButton = new QPushButton("Obróć", this);
    rotateButton->setGeometry(250, 225, 100, 50);
    rotateButton->setFocusPolicy(Qt::NoFocus);

    setVelButton = new QPushButton("Ustaw\nprędkość", this);
    setVelButton->setGeometry(50, 100, 100, 50);
    setVelButton->setFocusPolicy(Qt::NoFocus);

    setRotVelButton = new QPushButton("Ustaw\nprędkość\nobrotu", this);
    setRotVelButton->setGeometry(250, 100, 100, 50);
    setRotVelButton->setFocusPolicy(Qt::NoFocus);


    moveVal = new QLineEdit(this);
    moveVal->setPlaceholderText("Odległość");
    moveVal->setGeometry(50, 180, 100, 25);
    moveVal->setValidator(validator);

    rotateVal = new QLineEdit(this);
    rotateVal->setPlaceholderText("Kąt");
    rotateVal->setGeometry(250, 180, 100, 25);
    rotateVal->setValidator(validator);

    moveValLabel = new QLabel("units", this);
    rotateValLabel = new QLabel("stopni", this);
    moveValLabel->move(moveVal->x() + moveVal->width() + 5, moveVal->y()+5);
    rotateValLabel->move(rotateVal->x() + rotateVal->width() + 5, rotateVal->y()+5);


    moveVelocityVal = new QLineEdit(this);
    moveVelocityVal->setPlaceholderText("Prędkość");
    moveVelocityVal->setGeometry(50, 50, 100, 25);
    moveVelocityVal->setText(QString::number(INIT_VELOCITY));
    moveVelocityVal->setValidator(validator);

    rotateVelocityVal = new QLineEdit(this);
    rotateVelocityVal->setPlaceholderText("Prędkość obrotu");
    rotateVelocityVal->setGeometry(250, 50, 100, 25);
    rotateVelocityVal->setText(QString::number(INIT_ROTATION_VELOCITY));
    rotateVelocityVal->setValidator(validator);

    moveVelocityValLabel = new QLabel("unit/s", this);
    rotateVelocityValLabel = new QLabel("rad/s", this);
    moveVelocityValLabel->move(moveVelocityVal->x() + moveVelocityVal->width() + 5, moveVelocityVal->y()+5);
    rotateVelocityValLabel->move(rotateVelocityVal->x() + rotateVelocityVal->width() + 5, rotateVelocityVal->y()+5);


    cameraFollow = new QCheckBox("Podążaj za robotem", this);
    cameraFollow->setGeometry(5, 5, cameraFollow->width() + 60, cameraFollow->height());
    cameraFollow->setFocusPolicy(Qt::NoFocus);

    keepAxisValsRatio = new QCheckBox("Zachowaj proporcje", this);
    keepAxisValsRatio->move(125,460);
    keepAxisValsRatio->setFocusPolicy(Qt::NoFocus);

    for(int i = 0; i < 6; i++)
    {
        axisVals.push_back(new QLineEdit(this));
        axisVals[i]->setFixedSize(50, axisVals[i]->height());
        axisVals[i]->move(70 + ((int)i/2) * 125, 300 + 50 * (i%2));
        axisVals[i]->setValidator(validator);

        axisValsLabels.push_back(new QLabel(this));
        axisValsLabels[i]->setFixedSize(50, axisValsLabels[i]->height());
        axisValsLabels[i]->move(30 + ((int)i/2) * 125, 300 + 50 * (i%2));
    }

    axisVals[0]->setText(QString::number(INIT_XMIN));
    axisVals[1]->setText(QString::number(INIT_XMAX));
    axisVals[2]->setText(QString::number(INIT_YMIN));
    axisVals[3]->setText(QString::number(INIT_YMAX));
    axisVals[4]->setText(QString::number(INIT_ZMIN));
    axisVals[5]->setText(QString::number(INIT_ZMAX));


    axisValsLabels[0]->setText("Xmin");
    axisValsLabels[1]->setText("Xmax");
    axisValsLabels[2]->setText("Ymin");
    axisValsLabels[3]->setText("Ymax");
    axisValsLabels[4]->setText("Zmin");
    axisValsLabels[5]->setText("Zmax");

    setAxisVals = new QPushButton("Ustaw\nzakresy\nosi", this);
    setAxisVals->setGeometry(150, 400, 100, 50);
    setAxisVals->setFocusPolicy(Qt::NoFocus);



    selectRobot = new QComboBox(this);
    selectRobot->setGeometry(230, 510, selectRobot->width(), selectRobot->height()-5);
    selectRobot->setFocusPolicy(Qt::NoFocus);

    selectRobotLabel = new QLabel("Aktywny robot:", this);
    selectRobotLabel->move(selectRobot->x() - 110, selectRobot->y() + 3);

    for(int i = 0; i < sc.getRobotAmount(); i++)
        selectRobot->addItem(QString::number(i));

    addRobot = new QPushButton("+", this);
    addRobot->setGeometry(selectRobot->x() + selectRobot->width() + 5, selectRobot->y(),
                          selectRobot->height(), selectRobot->height());
    addRobot->setFocusPolicy(Qt::NoFocus);

    deleteActiveRobot = new QPushButton("-", this);
    deleteActiveRobot->setGeometry(addRobot->x() + addRobot->width() + 5, addRobot->y(),
                                   addRobot->width(), addRobot->height());
    deleteActiveRobot->setFocusPolicy(Qt::NoFocus);

    addObstacle = new QPushButton("Dodaj\nprzeszkodę", this);
    addObstacle->move(5, height() - 50);
    addObstacle->setFocusPolicy(Qt::NoFocus);

    connect(selectRobot, SIGNAL(activated(int)), this, SLOT(setActiveRobot()));
    connect(addRobot, SIGNAL(pressed()), this, SLOT(sendAddRobot()));
    connect(deleteActiveRobot, SIGNAL(pressed()), this, SLOT(sendDeleteRobot()));

    connect(addObstacle, SIGNAL(pressed()), this, SLOT(sendAddObstacle()));

    connect(moveButton, SIGNAL(pressed()), this, SLOT(sendMoveRobot()));
    connect(rotateButton, SIGNAL(pressed()), this, SLOT(sendRotateRobot()));
    connect(setVelButton, SIGNAL(pressed()), this, SLOT(sendRobotVel()));
    connect(setRotVelButton, SIGNAL(pressed()), this, SLOT(sendRobotRotVel()));
    connect(setAxisVals, SIGNAL(pressed()), this, SLOT(sendAxisVals()));
    connect(cameraFollow, SIGNAL(stateChanged(int)), this, SLOT(sendCameraFollow()));

    SWektorAmount = new QLabel("Ilosc obiektow SWektor: 0", this);
    SWektorAmount->setGeometry(180, SWektorAmount->y(), 400, SWektorAmount->height());

    emiter = new Emitter();
    connect(emiter, SIGNAL(loop()), this, SLOT(updateSWektorAmount()));
    emiter->start();

    createRobotDialog = new createRobot();
    createObstacleDialog = new createObstacle();
}


void Okno::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_W && !(e->isAutoRepeat()))
    {
        sc.setMovementDirection(1);

        sc.setThreadMoving();
        if(!sc.isThreadRunnig())
        {
            sc.start();
        }
        e->accept();
    }

    if(e->key() == Qt::Key_S && !(e->isAutoRepeat()))
    {
        sc.setMovementDirection(-1);

        sc.setThreadMoving();
        if(!sc.isThreadRunnig())
        {
            sc.start();
        }
        e->accept();
    }

    if(e->key() == Qt::Key_A && !(e->isAutoRepeat()))
    {
        sc.setRotationDirection(-1);

        sc.setThreadRotating();

        if(!sc.isThreadRunnig())
        {
            sc.start();
        }
        e->accept();
    }
    if(e->key() == Qt::Key_D && !(e->isAutoRepeat()))
    {
        sc.setRotationDirection(1);

        sc.setThreadRotating();

        if(!sc.isThreadRunnig())
        {
            sc.start();
        }
        e->accept();
    }
    if(e->key() == Qt::Key_Space && !(e->isAutoRepeat()))
    {
        sc.toggleDrawPath();
    }
    if(e->key() == Qt::Key_C)
        createObstacleDialog->exec();
}

void Okno::keyReleaseEvent(QKeyEvent *e)
{
    if((e->key() == Qt::Key_W || e->key() == Qt::Key_S) && !(e->isAutoRepeat()))
    {
        int *tab = (int*)malloc(6*sizeof(int));

        sc.clearThreadMoving();
        sc.quit();

        sc.getAxisVals(tab);

        for(int i = 0; i < 6; i++)
            axisVals[i]->setText(QString::number(tab[i]));
    }
    if((e->key() == Qt::Key_A || e->key() == Qt::Key_D) && !(e->isAutoRepeat()))
    {
        int *tab = (int*)malloc(6*sizeof(int));

        sc.clearThreadRotating();
        sc.quit();

        sc.getAxisVals(tab);

        for(int i = 0; i < 6; i++)
            axisVals[i]->setText(QString::number(tab[i]));
    }
    e->accept();
}



void Okno::sendMoveRobot()
{
    QString dist = moveVal->text();

    sc.moveRobot(dist.toDouble());
}

void Okno::sendRotateRobot()
{
    QString ang = rotateVal->text();

    sc.rotateRobot(RADTODEG*ang.toDouble());
}

void Okno::sendRobotVel()
{
    sc.setRobotVelocity(moveVelocityVal->text().toDouble());
}
void Okno::sendRobotRotVel()
{
    sc.setRobotRotVelocity(rotateVelocityVal->text().toDouble());
}

void Okno::sendCameraFollow()
{
    sc.setCameraFollow(cameraFollow->checkState());
}

void Okno::sendAxisVals()
{
    int tab[6];

    for(int i = 0; i < 6; i++)
        tab[i] = axisVals[i]->text().toInt();

    sc.setAxisVals(tab, keepAxisValsRatio->isChecked());

    if(keepAxisValsRatio->isChecked())
    {
        for(int i = 0; i < 6; i++)
            axisVals[i]->setText(QString::number(tab[i]));
    }
}


void Okno::updateSWektorAmount()
{
    SWektorAmount->setText("Ilosc obiektow SWektor: " + QString::number(Wektor3D::liczba_Wektorow));
}

void Okno::setActiveRobot()
{
    sc.activateRobot(selectRobot->currentIndex());

    moveVelocityVal->setText(QString::number(sc.getActiveRobot()->getVel()));

    rotateVelocityVal->setText(QString::number(sc.getActiveRobot()->getRotVel()));
}

void Okno::sendAddRobot()
{
    QString n;
    double h;

    if(createRobotDialog->execute(h, n))
    {
        sc.addRobot(h);
        selectRobot->addItem(n);
    }


}

void Okno::sendDeleteRobot()
{
    sc.deleteActiveRobot();

    selectRobot->removeItem(selectRobot->currentIndex());
}


void Okno::sendAddObstacle()
{
    double x, y, z,
            width, height;
    int vertixAmt;
    ObstacleType type;

    if(createObstacleDialog->execute(x, y, z, width, height, vertixAmt, type))
    {
        sc.addObstacle(x, y, z, width, height, vertixAmt, type);
    }
}
