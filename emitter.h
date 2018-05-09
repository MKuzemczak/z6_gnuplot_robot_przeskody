#ifndef EMITTER_H
#define EMITTER_H

#include <QWidget>
#include <QThread>
#include <QDebug>

class Emitter : public QThread
{
    Q_OBJECT
public:
    Emitter();

    void run();

signals:
    void loop();
};

#endif // EMITTER_H
