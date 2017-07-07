#include "generator.h"
#include <QImage>
#include <QMessageBox>
#include <QRgb>
#include <QDebug>
#include <random>
#include "Stoper.h"

Generator::Generator(double _p): p(_p){}
Generator::Generator(): p(0.0){}



 QImage Generator::deal_dmg(QImage obraz, void(Generator::*ptrfun)(QImage*)){

     (this->*ptrfun)(&obraz);

     return obraz;
 }

 double Generator::get_p(){return p;}

 void Generator::set_p(double _p){p = _p;}



 void Generator::ctri(QImage* obraz){

     std::random_device rseed;
     std::mt19937 rgen(rseed());
     std::uniform_int_distribution<int> range(0,255);

     int Width = obraz->width();
     int Height = obraz->height();
     unsigned int ran;
     QPoint px;





     unsigned long size = Width*Height;

     allPixels = new QPoint[size];
     if(allPixels!=nullptr)
     {
         for (unsigned long i = 0; i<size; i++)
         {
             allPixels[i]  = QPoint(i%Width,i/Width);
         }
     }
     else
     {
         qInfo()<< "Błąd deklaracji";
     }


        int amount = p * size;
        size--;


        for (int i = 0; i<amount; i++){

         std::uniform_int_distribution<int> idist(0,size);
         ran= idist(rgen);






         obraz->setPixel(allPixels[ran].x(), allPixels[ran].y() , qRgb(range(rgen),range(rgen),range(rgen)));


         if (ran != size)
             allPixels[ran] = allPixels[size];
         size--;
 }


        delete [] allPixels;
        allPixels = nullptr;
 }

 void Generator::ciri(QImage* obraz){

     std::random_device rseed;
     std::mt19937 rgen(rseed());
     std::uniform_int_distribution<int> range(0,255);

     int Width = obraz->width();
     int Height = obraz->height();
     unsigned int ran;
     QPoint px;


     unsigned long size = Width*Height;

     allPixels = new QPoint[size];
     if(allPixels!=nullptr)
     {
         for (unsigned long i = 0; i<size; i++)
         {
             allPixels[i]  = QPoint(i%Width,i/Width);
         }
     }
     else
     {
         qInfo()<< "Błąd deklaracji";
     }







            int amount = p * size;
            size--;
            int blue,red,green;
            int quantity =0;


             for (int i = 0; i<amount; i++){

                std::uniform_int_distribution<int> idist(0,size);
                ran= idist(rgen);




                px = allPixels[ran];
                blue = qBlue(obraz->pixel(px));
                red = qRed(obraz->pixel(px));
                green = qGreen(obraz->pixel(px));



                std::uniform_int_distribution<int> idist2(1,3);

                quantity = idist2(rgen);
                int chosen;

                for (int i=1; i<=quantity; i++){

                chosen = idist2(rgen);
                bool ch_b = false;
                bool ch_g = false;
                bool ch_r = false;

                if (chosen == 1 && !(ch_r)){

                    red = range(rgen);
                    ch_r = true;

                } else if (chosen == 2 && !(ch_g) ){

                     green = range(rgen);
                     ch_g = true;

                } else if (!(ch_b)) {

                     blue = range(rgen);
                     ch_b = true;

                } else {
                    i--;
                }



                }


                obraz->setPixel(px, qRgb(red,green,blue));

                if (ran != size)
                    allPixels[ran] = allPixels[size];
                size--;


             }



             delete [] allPixels;
             allPixels = nullptr;

        }
