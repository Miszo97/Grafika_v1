#include "fastamf.h"
#include <algorithm>
#include <iostream>
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
    int ** M;
    int * maskM;
    double * sumas;
    double suma =0;
    int amountof1;
    double aveR =0;
    double aveG =0;
    double aveB =0;

    QRgb chosen;
    int height = img.height();
    int width  = img.width();
    int ** SSD = new int * [height];
    SSD = new int*[height];
    SSD[0] = new int[height*width];
    for (int i = 1; i < height; i++)
    {
        SSD[i] = SSD[0] + i*width;
    }
    M = new int*[height+2*(size/2)];
    M[0] = new int[(height+2*(size/2))*(width+2*(size/2))];
    for (int i = 1; i < height+2*(size/2); i++)
    {
        M[i] = M[0] + i*(width+2*(size/2));
    }
    for (int x =0; x<height+2*(size/2); x++){
        for (int i =0; i<width+2*(size/2); i++){
            M[x][i] =1;
        }
    }
    maskR = new int [size*size]; //!!!
    maskG = new int [size*size]; //!!!
    maskB = new int [size*size]; //!!!
    maskSSD = new double [size*size]; //!!!
    maskOIP = new double [height * width]; //!!!
    maskM = new int [size*size]; //!!!
    int curr_win_index = 0;
    sumas = new double [size*size-1]; //!!!
    size_t central_px = (size*size)/2;
    for (int wsp_x =0; wsp_x<height; wsp_x++){
        for (int wsp_y =0; wsp_y<width; wsp_y++){
            suma = 0;
            for (int i = 0; i<size; i++){
                for (int x = 0; x<size; x++){
                    curr_win_index = i*size+x;
                    *(maskR + curr_win_index) = Matrix_R[wsp_x+i][wsp_y+x];
                    *(maskG + curr_win_index) = Matrix_G[wsp_x+i][wsp_y+x];
                    *(maskB + curr_win_index) = Matrix_B[wsp_x+i][wsp_y+x];//!!!
                }
            }

            double p;
            int mv = 0;
            for(int i=0; i<size*size; i++){  //!!!
                if (i==central_px){
                    mv=1;
                } else {
                    p = sqrt((maskR[i] - maskR[central_px])*(maskR[i] - maskR[central_px]) + (maskG[i] - maskG[central_px])*(maskG[i] - maskG[central_px])+ (maskB[i] - maskB[central_px])*(maskB[i] - maskB[central_px]));
                    //qInfo()<<p;
                    sumas[i-mv] = p;
                }
            }
            bubbleSort(sumas,size*size-1);
            SSD[wsp_x][wsp_y] = sumas[0] + sumas[1];
            for (int i = 0; i<size*size-1; i++){
                sumas[i] =0;
            }
        }
    }

    for (int wsp_x =0; wsp_x< height; wsp_x++){
        for (int wsp_y =0; wsp_y < width; wsp_y++){
            if(wsp_x>(size/2)-1 && wsp_x<height-(size/2) && wsp_y>(size/2)-1 && wsp_y<width-(size/2)){
                for (int i = 0; i<size; i++){
                    for (int x = 0; x<size; x++){
                        *(maskSSD + (i*size+x)) = SSD[wsp_x-(size/2)+i][wsp_y-(size/2)+x];
                    }
                }
                double smallest = INT_MAX;
                for (int i = 0; i < size*size; i++) {  //!!!
                    if (maskSSD[i] < smallest) {
                        smallest = maskSSD[i];
                    }
                }
                maskOIP[wsp_x * width + wsp_y] = SSD[wsp_x][wsp_y] - smallest;
            }
            else
                maskOIP[wsp_x * width + wsp_y] = SSD[wsp_x][wsp_y];
        }
    }

    for (int wsp_x =0; wsp_x < height; wsp_x++){
        for (int wsp_y =0; wsp_y < width; wsp_y++){
            if(maskOIP[(wsp_x) * width + (wsp_y)] < ProgVal)
                M[wsp_x+(size/2)][wsp_y+(size/2)] = 1;
            else
                M[wsp_x+(size/2)][wsp_y+(size/2)] = 0;
        }
    }

    for (int wsp_x =0; wsp_x < height; wsp_x++){
        for (int wsp_y =0; wsp_y < width; wsp_y++){
            if(M[wsp_x+1][wsp_y+1] == 0){
                for (int i = 0; i<size; i++){
                    for (int x = 0; x<size; x++){
                        curr_win_index = i*size+x;
                        *(maskM + curr_win_index) = M[wsp_x+i][wsp_y+x];
                        *(maskR + curr_win_index) = Matrix_R[wsp_x+i][wsp_y+x];
                        *(maskG + curr_win_index) = Matrix_G[wsp_x+i][wsp_y+x];
                        *(maskB + curr_win_index) = Matrix_B[wsp_x+i][wsp_y+x];

                    }
                }
                for (int i = 0; i < size*size; i++)
                    if (maskM[i]) amountof1++;
                for (int i = 0; i<size; i++){
                    for (int x = 0; x<size; x++){
                        curr_win_index = i*size+x;
                        aveR +=  *(maskR + curr_win_index) * *(maskM + curr_win_index);
                        aveG += *(maskG + curr_win_index) * *(maskM + curr_win_index);
                        aveB += *(maskB + curr_win_index) * *(maskM + curr_win_index);
                    }
                }
                aveR /= amountof1;
                aveG /= amountof1;
                aveB /= amountof1;
                chosen = qRgb(aveR, aveG, aveB);
                aveR = 0;
                aveG = 0;
                aveB = 0;
                amountof1 = 0;
                img.setPixel(wsp_y,wsp_x,chosen);
                M[wsp_x][wsp_y] = 1;
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
