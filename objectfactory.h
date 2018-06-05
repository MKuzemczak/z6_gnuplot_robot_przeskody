#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <memory>

#include "Robot.hh"
#include "obstacle.h"

typedef enum
{
    robotType,
    obstacleType
} objectType;


class ObjectFactory
{
private:
    ObjectFactory();

    static ObjectFactory * _instance;

public:
    static ObjectFactory * getInstance();

    std::shared_ptr<ObiektGraficzny> makeObject(const objectType type);
};

#endif // OBJECTFACTORY_H
