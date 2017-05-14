#include "filtr.h"
#include <QDebug>

Filtr::Filtr(QObject *parent) : QObject(parent)
{

}


void Filtr::load_img(QImage& _img){


    img = _img;
    destImage = QImage(img.width()+(size-1),img.height()+(size-1), QImage::Format_RGB32); //pomocniczy, większy obraz do którego pakowany jest prawdziwy. //!!!//!!!
    QPoint destPoint = QPoint((size-1)/2,(size-1)/2);



    QPainter painter(&destImage);
    painter.drawImage(destPoint, img);
    painter.end();
    QRgb ** values_tab_up = new QRgb * [size];
    QRgb ** values_tab_down = new QRgb * [size];

     for(int i=0; i<((size-1)/2); i++)
    values_tab_up[i] = reinterpret_cast<QRgb *>(img.scanLine(i)); // wskaźnik do górnego szeregu pikseli prawdziwego obrazu

     for(int i=0; i<((size-1)/2); i++)
    values_tab_down[i] = reinterpret_cast<QRgb *>(img.scanLine(img.height()-1-i)); // wskaźnik do dolnego szeregu pikseli prawdziwego obrazu


 for(int x=0; x<((size-1)/2); x++){
   for(int i =((size-1)/2); i<destImage.width()-((size-1)/2); i++){                                                         //pętla dodająca dodatkowy szereg pikseli u góru
    destImage.setPixel(i,x, qRgb(qRed(values_tab_up[x][i-((size-1)/2)]),qGreen(values_tab_up[x][i-((size-1)/2)]),qBlue(values_tab_up[x][i-((size-1)/2)])));
   }
 }

 for(int x=0; x<((size-1)/2); x++){
   for(int i =((size-1)/2); i<destImage.width()-((size-1)/2); i++){                                                        //pętla dodająca dodatkowy szereg pikseli na dole
    destImage.setPixel(i,destImage.height()-1, qRgb(qRed(values_tab_down[x][i-((size-1)/2)]),qGreen(values_tab_down[x][i-((size-1)/2)]),qBlue(values_tab_down[x][i-((size-1)/2)])));
   }
 }





 for(int x=((size-1)/2)-1; x>=0; x--){
 for(int i=0 ; i<destImage.height(); i++){                                           //pętla dodająca dodatkowy szereg pikseli po lewej

  destImage.setPixel(x,i,qRgb(qRed(destImage.pixel(((size-1)/2),i)),qGreen(destImage.pixel(((size-1)/2),i)),qBlue(destImage.pixel(((size-1)/2),i))));

 }
 }

 for(int x=((size-1)/2)-1; x>=0; x--){
 for(int i=0 ; i<destImage.height(); i++){                                           //pętla dodająca dodatkowy szereg pikseli po prawej

  destImage.setPixel(destImage.width()-1-x,i,qRgb(qRed(destImage.pixel(destImage.width()-1-x,i)),qGreen(destImage.pixel(destImage.width()-1-x,i)),qBlue(destImage.pixel(destImage.width()-1-x,i))));

 }
 }

 int destWidth = destImage.width();
 int destHeight = destImage.height();





 Matrix_R = new int*[destHeight];
 Matrix_G = new int*[destHeight];
 Matrix_B = new int*[destHeight];

 Matrix_R[0] = new int[destHeight*destWidth];
 Matrix_G[0] = new int[destHeight*destWidth];
 Matrix_B[0] = new int[destHeight*destWidth];

 for (int i = 1; i < destHeight; i++)
 {
     Matrix_R[i] = Matrix_R[0] + i*destWidth;
     Matrix_G[i] = Matrix_G[0] + i*destWidth;
     Matrix_B[i] = Matrix_B[0] + i*destWidth;
 }



  for (int x =0; x<destHeight-1; x++){
       for (int i =0; i<destWidth-1; i++){

      Matrix_R[x][i] = qRed(destImage.pixel(i,x));
      Matrix_G[x][i] =  qGreen(destImage.pixel(i,x));
      Matrix_B[x][i] = qBlue(destImage.pixel(i,x));

  }
  }


  delete values_tab_down;
  delete values_tab_up;
  values_tab_down = nullptr;
  values_tab_up = nullptr;








}
void Filtr::set_winsize(int w){

    size = w;

}

int Filtr::get_winsize(){

   return size;

}


