#include "objectfactory.h"

using namespace std;

ObjectFactory * ObjectFactory::_instance = NULL;


ObjectFactory::ObjectFactory()
{

}

ObjectFactory * ObjectFactory::getInstance()
{
    if(_instance == NULL)
        _instance = new ObjectFactory();

    return _instance;
}

shared_ptr<ObiektGraficzny> ObjectFactory::makeObject(const objectType type)
{
    switch(type)
    {
    case robotType:
        return make_shared<Robot>();
    case obstacleType:
        return make_shared<Obstacle>();
    }
}
