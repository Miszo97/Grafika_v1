#include "generator.h"
#include <QImage>
#include <QMessageBox>
#include <QRgb>
#include <QDebug>
#include <random>





Generator::Generator(Generator::type _typ, double _p){


   p = _p;
   typ = _typ;




}


Generator::Generator(){

   p = 0.0;
   typ = Generator::CTRI;

}




 QImage Generator::operator<<(QImage obraz){


     std::random_device rseed;
     std::mt19937 rgen(rseed());
     std::uniform_int_distribution<int> range(0,255);

     int x = obraz.width();
     int y = obraz.height();
     unsigned int ran;
     QPoint px;

     int size = x*y;





     for (int i = 0; i<y; i++){

         for (int z = 0; z<x; z++){

             pixels.append(QPoint(z,i));



         }

     }

    if(typ == CTRI){

    int amount = p * size;


     for (int i = 0; i<amount; i++){

        std::uniform_int_distribution<int> idist(0,size-1);
        ran= idist(rgen);

        pixels_demaged.append(pixels[ran]);


        px = pixels[ran];
        obraz.setPixel(px, qRgb(range(rgen),range(rgen),range(rgen)));
        pixels.removeAt(ran);
        size--;


     }


    } else if(typ == CIRI){

        int amount = p * size;
        int blue,red,green;
        int quantity =0;


         for (int i = 0; i<amount; i++){

            std::uniform_int_distribution<int> idist(0,size-1);
            ran= idist(rgen);

            pixels_demaged.append(pixels[ran]);


            px = pixels[ran];
            blue = qBlue(obraz.pixel(px));
            red = qRed(obraz.pixel(px));
            green = qGreen(obraz.pixel(px));



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


            obraz.setPixel(px, qRgb(red,green,blue));
            pixels.removeAt(ran);
            size--;


         }



    }

     pixels.clear();
     pixels_demaged.clear();
     return obraz;
 }

 double Generator::get_p(){
     return p;
 }


 Generator::type Generator::get_type(){
     return typ;
 }

 void Generator::set_p(double _p){

     p = _p;

 }

 void Generator::set_type(Generator::type _typ){

     typ = _typ;

 }
