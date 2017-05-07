#ifndef FILTR_H
#define FILTR_H

#include <QImage>
#include <QDebug>
#include <Qpainter>
#include <QRgb>

#include <QObject>

class Filtr : public QObject
{
    Q_OBJECT
protected:

    int size;
    QImage destImage;
    QImage img;

    int **Matrix_R;
    int **Matrix_G;
    int **Matrix_B;

public:
    explicit Filtr(QObject *parent = 0);






    void set_winsize(int);
    int get_winsize();
    void load_img(QImage&);
    virtual QImage filtr() =0
    {}


signals:

public slots:
};

#endif // FILTR_H
