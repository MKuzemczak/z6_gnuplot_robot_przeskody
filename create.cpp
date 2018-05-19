#include "create.h"

///////////////////////////////////////////////// createRobot
createRobot::createRobot()
{
    setFixedSize(300, 150);

    ret = true;

    nameInput = new QLineEdit(this);
    heightInput = new QLineEdit(this);
    nameInput->setGeometry(90, 5, 200, nameInput->height());
    heightInput->setGeometry(90, 40, 200, heightInput->height());
    nameInput->setPlaceholderText("Nazwa robota");
    heightInput->setPlaceholderText("Wysokość robota");
    nameInput->setText("Robot");
    heightInput->setText("350");

    nameLabel = new QLabel("Nazwa:", this);
    heightLabel = new QLabel("Wysokość:", this);
    nameLabel->move(nameInput->x() - 60, nameInput->y() + 7);
    heightLabel->move(heightInput->x() - 80, heightInput->y() + 7);


    add = new QPushButton("Dodaj", this);
    cancel = new QPushButton("Anuluj", this);

    add->move(30, 100);
    cancel->move(190, 100);

    connect(add, SIGNAL(pressed()), this, SLOT(saveData()));
    connect(add, SIGNAL(pressed()), this, SLOT(setAddRet()));
    connect(add, SIGNAL(pressed()), this, SLOT(close()));
    connect(cancel, SIGNAL(pressed()), this, SLOT(setCancelRet()));
    connect(cancel, SIGNAL(pressed()), this, SLOT(close()));

    setWindowTitle(tr("Dodaj robota"));
}

bool createRobot::execute(double &h, QString &n)
{
    exec();

    if(ret)
    {
        h = height;
        n = name;
    }

    return ret;
}

void createRobot::saveData()
{
    name = nameInput->text();
    height = heightInput->text().toDouble();
}

void createRobot::setCancelRet()
{
    ret = false;
}

void createRobot::setAddRet()
{
    ret = true;
}
///////////////////////////////////////////////// createObstacle
createObstacle::createObstacle()
{
    setFixedSize(350, 200);

    selectObstacleTypeButtonGroup = new QButtonGroup(this);

    selectPolygonType = new QRadioButton("Wielokąt", this);
    selectSquareType = new QRadioButton("Kwadrat", this);
    selectPenisType = new QRadioButton("Penis", this);

    selectPolygonType->move(20, 5);
    selectSquareType->move(selectPolygonType->x() + 100, selectPolygonType->y());
    selectPenisType->move(selectSquareType->x() + 100, selectPolygonType->y());

    selectObstacleTypeButtonGroup->addButton(selectPolygonType);
    selectObstacleTypeButtonGroup->addButton(selectSquareType);
    selectObstacleTypeButtonGroup->addButton(selectPenisType);

    selectObstacleTypeButtonGroup->setId(selectPolygonType, POLYGON);
    selectObstacleTypeButtonGroup->setId(selectSquareType, SQUARE);
    selectObstacleTypeButtonGroup->setId(selectPenisType, PENIS);

    selectPolygonType->setChecked(true);
    selectedObstacleType = POLYGON;

    xInput = new QLineEdit(this);
    yInput = new QLineEdit(this);
    zInput = new QLineEdit(this);
    widthInput = new QLineEdit(this);
    heightInput = new QLineEdit(this);
    vertixAmtInput = new QLineEdit(this);

    xInput->setGeometry(70, 30, 50, xInput->height());
    yInput->setGeometry(xInput->x(), xInput->y() + xInput->height() + 5,
                        xInput->width(), xInput->height());
    zInput->setGeometry(xInput->x(), yInput->y() + yInput->height() + 5,
                        xInput->width(), xInput->height());

    widthInput->setGeometry(260, 30, 50, widthInput->height());
    heightInput->setGeometry(widthInput->x(), widthInput->y() + widthInput->height() + 5,
                             widthInput->width(), widthInput->height());
    vertixAmtInput->setGeometry(widthInput->x(), heightInput->y() + heightInput->height() + 5,
                                widthInput->width(), widthInput->height());

    xLabel = new QLabel("X:", this);
    yLabel = new QLabel("Y:", this);
    zLabel = new QLabel("Z:", this);
    widthLabel = new QLabel("Szerokość:", this);
    heightLabel = new QLabel("Wysokość:", this);
    vertixAmtLabel = new QLabel("Wierzchołki:", this);

    xLabel->move(xInput->x() - 20, xInput->y() + 7);
    yLabel->move(yInput->x() - 20, yInput->y() + 7);
    zLabel->move(zInput->x() - 20, zInput->y() + 7);
    widthLabel->move(widthInput->x() - 80, widthInput->y() + 7);
    heightLabel->move(heightInput->x() - 80, heightInput->y() + 7);
    vertixAmtLabel->move(vertixAmtInput->x() - 90, vertixAmtInput->y() + 7);

    add = new QPushButton("Dodaj", this);
    cancel = new QPushButton("Anuluj", this);

    add->move(50, 150);
    cancel->move(220, 150);

    connect(this, SIGNAL(destroyed(QObject*)), this, SLOT(setCancelRet()));
    connect(selectObstacleTypeButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(obstacleTypeSelected(int))); //// TODO: slot dla zmiany typu przeszkody
    connect(add, SIGNAL(pressed()), this, SLOT(saveData()));
    connect(add, SIGNAL(pressed()), this, SLOT(setAddRet()));
    connect(add, SIGNAL(pressed()), this, SLOT(close()));
    connect(cancel, SIGNAL(pressed()), this, SLOT(setCancelRet()));
    connect(cancel, SIGNAL(pressed()), this, SLOT(close()));

    setWindowTitle(tr("Dodaj przeszkodę"));

    ret = true;
}

bool createObstacle::execute(double &x, double &y, double &z,
                             double & width, double & height,
                             int & vertixAmount, ObstacleType & type)
{
    exec();

    if(ret)
    {
        x = xPos;
        y = yPos;
        z = zPos;
        width = w;
        height = h;
        vertixAmount = vertixAmt;
        type = selectedObstacleType;
    }

    return ret;
}

void createObstacle::saveData()
{
    xPos = xInput->text().toDouble();
    yPos = yInput->text().toDouble();
    zPos = zInput->text().toDouble();
    h = heightInput->text().toDouble();

    if(selectObstacleTypeButtonGroup->checkedId() == POLYGON ||
       selectObstacleTypeButtonGroup->checkedId() == SQUARE)
    {
        w = widthInput->text().toDouble();
    }
    else
    {
        w = 0;
    }

    if(selectObstacleTypeButtonGroup->checkedId() == POLYGON)
    {
        vertixAmt = vertixAmtInput->text().toInt();
    }
    else
    {
        vertixAmt = 0;
    }
}
void createObstacle::setCancelRet()
{
    ret = false;
}
void createObstacle::setAddRet()
{
    ret = true;
}

void createObstacle::obstacleTypeSelected(int choice)
{
    switch(choice)
    {
    case POLYGON:
        widthInput->setEnabled(true);
        vertixAmtInput->setEnabled(true);
        selectedObstacleType = POLYGON;
        break;
    case SQUARE:
        widthInput->setEnabled(true);
        vertixAmtInput->setEnabled(false);
        selectedObstacleType = SQUARE;
        break;
    case PENIS:
        widthInput->setEnabled(false);
        vertixAmtInput->setEnabled(false);
        selectedObstacleType = PENIS;
        break;
    }
}
