#include "vmf.h"

//#define STARA_WERSJA

Vmf::Vmf(){

    size = 3;

}

Vmf::Vmf(int _size){

    size = _size;

}

QImage Vmf::filtr(){



    if ((size%2) && size >=3){
    int yuy;

    int * maskR;
    int * maskG;
    int * maskB;
    double * sumas;
    double suma =0;




    maskR = new int [size*size]; //!!!
    maskG = new int [size*size]; //!!!
    maskB = new int [size*size]; //!!!

    sumas = new double [size*size]; //!!!

    QRgb chosen;



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




     double p;


             for(int i=0; i<size*size-1; i++){  //!!!
                 for(int x=i+1; x<size*size; x++){

                     p = sqrt((maskR[i] - maskR[x])*(maskR[i] - maskR[x]) + (maskG[i] - maskG[x])*(maskG[i] - maskG[x])+ (maskB[i] - maskB[x])*(maskB[i] - maskB[x]));

                     suma += p;
                     sumas[x] += p;

                 }

                 sumas[i] += suma;
                 suma =0;

          }






             double smallest = INT_MAX;
             for (int i = 0; i < size*size; i++) {  //!!!
                 if (sumas[i] < smallest) {
                     smallest = sumas[i];
                     chosen = qRgb(maskR[i], maskG[i], maskB[i]);
                 }
             }


             for (int i = 0; i<size*size; i++){
                 sumas[i] =0;
             }



             img.setPixel(wsp_y,wsp_x,chosen);






        }

    }




    delete [] maskR;
    delete [] maskG;
    delete [] maskB;
    delete [] sumas;





    qInfo()<< "Successfully converted!";

    return img;
    } else
        qInfo()<< "Incorrect size!";


    return img;



}

Vmf::~Vmf(){

    delete [] Matrix_R;
    delete [] Matrix_G;
    delete [] Matrix_B;

    Matrix_R = NULL;
    Matrix_G = NULL;
    Matrix_B = NULL;
}
