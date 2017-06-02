#include "fastamf.h"
#include <algorithm>

void bubbleSort(double arr[], int n) {
      bool swapped = true;
      int j = 0;
      int tmp;
      while (swapped) {
            swapped = false;
            j++;
            for (int i = 0; i < n - j; i++) {
                  if (arr[i] > arr[i + 1]) {
                        tmp = arr[i];
                        arr[i] = arr[i + 1];
                        arr[i + 1] = tmp;
                        swapped = true;
                  }
            }
      }
}


FASTAMF::FASTAMF(void)
{
    size = 3;
    ProgVal = 80;
}


FASTAMF::FASTAMF(int _size){

    size = _size;

}

FASTAMF::~FASTAMF() {


}

void FASTAMF::setProgVal(double_t pv){

    ProgVal = pv;
}

double_t FASTAMF::getProgVal() const{

    return ProgVal;
}




QImage FASTAMF::filtr(){


    int * maskR;
    int * maskG;
    int * maskB;
    double * maskSSD;
    double * maskOIP;
    int * M;
    int * maskM;
    double * sumas;
    double suma =0;
    int amountof1;
    double aveR =0;
    double aveG =0;
    double aveB =0;
    QRgb chosen;

    int * SSD = new int[img.height() * img.width()];


    maskR = new int [size*size]; //!!!
    maskG = new int [size*size]; //!!!
    maskB = new int [size*size]; //!!!
    maskSSD = new double [size*size]; //!!!
    maskOIP = new double [img.height() * img.width()]; //!!!
    M = new int [img.height() * img.width()]; //!!!
    maskM = new int [size*size]; //!!!



    sumas = new double [size*size-1]; //!!!

    size_t central_px = (size*size)/2;



    for (int wsp_x =0; wsp_x<img.height(); wsp_x++){

        for (int wsp_y =0; wsp_y<img.width(); wsp_y++){


        suma = 0;





        for (int i = 0; i<size; i++){
            for (int x = 0; x<size; x++){

                *(maskR + (i*size+x)) = Matrix_R[wsp_x+i][wsp_y+x];
                *(maskG + (i*size+x)) = Matrix_G[wsp_x+i][wsp_y+x];
                *(maskB + (i*size+x)) = Matrix_B[wsp_x+i][wsp_y+x];//!!!

            }
        }


//        for (int i = 0; i<size; i++){
//            for (int x = 0; x<size; x++){

//                qInfo()<<*(maskR + (i*size+x));
//               qInfo()<< *(maskG + (i*size+x));
//                qInfo()<<*(maskB + (i*size+x));//!!!

//            }
//        }




     double p;


     int mv = 0;

             for(int i=0; i<size*size; i++){  //!!!

                    if (i==central_px){
                        mv=1;
                    } else {
                     p = sqrt((maskR[i] - maskR[central_px])*(maskR[i] - maskR[central_px]) + (maskG[i] - maskG[central_px])*(maskG[i] - maskG[central_px])+ (maskB[i] - maskB[central_px])*(maskB[i] - maskB[central_px]));
//                    qInfo()<<"P "<<p;
//                    qInfo()<<" maskR[central_px] "<< maskR[central_px];
//                     qInfo()<<" maskR[i] "<<maskR[i];

                     sumas[i-mv] = p;
                    }



          }

//             for (int i = 0; i<8; i++){
//                 qInfo()<<"Suma "<<i<<" "<<sumas[i];
//             }




        bubbleSort(sumas,8);

//        for (int i = 0; i<8; i++){
//            qInfo()<<"Suma "<<i<<" "<<sumas[i];
//        }

        SSD[wsp_x * img.height() + wsp_y] = sumas[0] + sumas[1];


//                       for (int i = 0; i<9; i++){
//                             qInfo()<<"Suma "<<i<<" "<<sumas[i];
//                       }
        //qInfo()<<"SSD "<<SSD[wsp_x * img.height() + wsp_y];



             for (int i = 0; i<size*size-1; i++){
                 sumas[i] =0;
             }










        }

    }



    for (int wsp_x =0; wsp_x<img.height(); wsp_x++){

        for (int wsp_y =0; wsp_y<img.width(); wsp_y++){

            for (int i = 0; i<size; i++){
                for (int x = 0; x<size; x++){

                    *(maskSSD + (i*size+x)) = SSD[(wsp_x * img.height() + wsp_y) + (i*size+x)];
                    //qInfo()<<"Mask "<< i*size+x << *(maskSSD + (i*size+x));

                }
            }

            double smallest = INT_MAX;
            for (int i = 0; i < size*size; i++) {  //!!!
                if (maskSSD[i] < smallest) {
                    smallest = maskSSD[i];

                }
            }

            //qInfo()<<"Smallest: "<<smallest;

           maskOIP[wsp_x * img.height() + wsp_y] = SSD[wsp_x * img.height() + wsp_y] - smallest;
           //qInfo()<<"MaskOIP "<<maskOIP[wsp_x * img.height() + wsp_y]<<" SSD "<<SSD[wsp_x * img.height() + wsp_y]<<" Smallest: "<<smallest;

        }
    }

    for (int wsp_x =0; wsp_x<img.height(); wsp_x++){

        for (int wsp_y =0; wsp_y<img.width(); wsp_y++){

            if(maskOIP[wsp_x * img.height() + wsp_y] < ProgVal)
                M[wsp_x * img.height() + wsp_y] = 1;
            else
                M[wsp_x * img.height() + wsp_y] = 0;

             //qInfo()<<"MaskM "<<M[wsp_x * img.height() + wsp_y];
        }

    }

//                           for (int i = 0; i<9; i++){
//                                 qInfo()<<"Suma "<<i<<" "<<sumas[i];
//                           }

    for (int wsp_x =0; wsp_x<img.height(); wsp_x++){

        for (int wsp_y =0; wsp_y<img.width(); wsp_y++){


            if(M[wsp_x * img.height() + wsp_y] == 0){

                for (int i = 0; i<size; i++){
                    for (int x = 0; x<size; x++){

                        *(maskM + (i*size+x)) = M[(wsp_x * img.height() + wsp_y) + (i*size+x)];
                        //qInfo()<<"Mask "<< i*size+x << *(maskSSD + (i*size+x));
                        *(maskR + (i*size+x)) = Matrix_R[wsp_x+i][wsp_y+x];
                        *(maskG + (i*size+x)) = Matrix_G[wsp_x+i][wsp_y+x];
                        *(maskB + (i*size+x)) = Matrix_B[wsp_x+i][wsp_y+x];

                    }
                }

                for (int i = 0; i < size*size; i++)
                    if (maskM[i]) amountof1++;






                for (int i = 0; i<size; i++){
                    for (int x = 0; x<size; x++){

                        aveR +=  *(maskR + (i*size+x)) * *(maskM + (i*size+x));


                        aveG += *(maskG + (i*size+x)) * *(maskM + (i*size+x));


                        aveB += *(maskB + (i*size+x)) * *(maskM + (i*size+x));


//                        *(maskM + (i*size+x)) = M[(wsp_x * img.height() + wsp_y) + (i*size+x)];
//                        //qInfo()<<"Mask "<< i*size+x << *(maskSSD + (i*size+x));
//                        *(maskR + (i*size+x)) = Matrix_R[wsp_x+i][wsp_y+x];
//                        *(maskG + (i*size+x)) = Matrix_G[wsp_x+i][wsp_y+x];
//                        *(maskB + (i*size+x)) = Matrix_B[wsp_x+i][wsp_y+x];//!!!

                    }
                }

                aveR /= amountof1;
                aveG /= amountof1;
                aveB /= amountof1;


//                qInfo()<<"aveR"<<aveR<<" "<< wsp_x<<" "<<wsp_y;
//                qInfo()<<"aveG"<<aveG<<" "<< wsp_x<<" "<<wsp_y;
//                qInfo()<<"aveB"<<aveB<<" "<< wsp_x<<" "<<wsp_y;

                chosen = qRgb(aveR, aveG, aveB);
                aveR = 0;
                aveG = 0;
                aveB = 0;
                amountof1 = 0;

                img.setPixel(wsp_y,wsp_x,chosen);

            }




        }

    }

    delete [] maskR;
    delete [] maskG;
    delete [] maskB;
    delete [] sumas;
    delete maskOIP;
    delete maskSSD;
    delete M;
    delete maskM;

return img;


}
