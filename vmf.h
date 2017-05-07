#ifndef VMF_H
#define VMF_H

#include "filtr.h"
#include <QObject>

class Vmf :  public Filtr
{
    Q_OBJECT
public:


    Vmf();
    ~Vmf();
    Vmf(int);
    virtual QImage filtr();

signals:

public slots:
};

#endif // VMF_H
