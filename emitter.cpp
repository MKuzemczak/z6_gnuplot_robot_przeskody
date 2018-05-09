#include <unistd.h>

#include "emitter.h"


Emitter::Emitter()
{

}

void Emitter::run()
{
    while(1)
    {
        emit loop();
        usleep(50000);
    }
}
