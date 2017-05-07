#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>

class Generator : public QObject
{
    Q_OBJECT



public:
    enum  type {CTRI, CIRI};
    QList<QPoint> pixels;
    QList<QPoint> pixels_demaged;



    QImage operator<<(QImage);


    Generator(type , double);
    Generator();

    double get_p();
    type get_type();

    void set_p(double);
    void set_type(Generator::type);



private:
    type typ;
    double p;


signals:

public slots:



};

#endif // GENERATOR_H
