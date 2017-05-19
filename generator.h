#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>

class Generator : public QObject
{
    Q_OBJECT



public:

    QList<QPoint> pixels;

    void ctri(QImage*);
    void ciri(QImage*);


    QImage deal_dmg(QImage, void(Generator::*ptrfun)(QImage*));


    Generator(double);
    Generator();

    double get_p();


    void set_p(double);




private:

    double p;



signals:

public slots:



};

#endif // GENERATOR_H
