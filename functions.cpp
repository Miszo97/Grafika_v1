#include "functions.h"
#include <QImage>
#include <tuple>


std::tuple<double, double> getPSNR_MAE(QImage & image1, QImage & image3){

    auto sum_of_mse = 0;
    auto sum_of_mae = 0;
    double PSNR = 0.0;
    double MAE = 0.0;
    double RMSE = 0.0;
    double MSE = 0.0;

    double N = image1.width() * image1.height();

    for (int wsp_x =0; wsp_x<image1.width(); wsp_x++){

        for (int wsp_y =0; wsp_y<image1.height(); wsp_y++){




            sum_of_mse += (qRed( image1.pixel(wsp_x,wsp_y)) - qRed( image3.pixel(wsp_x,wsp_y))) * (qRed( image1.pixel(wsp_x,wsp_y)) - qRed( image3.pixel(wsp_x,wsp_y))) +
                    (qGreen( image1.pixel(wsp_x,wsp_y)) - qGreen( image3.pixel(wsp_x,wsp_y))) * (qGreen( image1.pixel(wsp_x,wsp_y)) - qGreen( image3.pixel(wsp_x,wsp_y))) +
                    (qBlue( image1.pixel(wsp_x,wsp_y)) - qBlue( image3.pixel(wsp_x,wsp_y))) * (qBlue( image1.pixel(wsp_x,wsp_y)) - qBlue( image3.pixel(wsp_x,wsp_y)));

            sum_of_mae += abs(qRed( image1.pixel(wsp_x,wsp_y)) - qRed( image3.pixel(wsp_x,wsp_y))) +
                   abs(qGreen( image1.pixel(wsp_x,wsp_y)) - qGreen( image3.pixel(wsp_x,wsp_y)))+
                    abs(qBlue( image1.pixel(wsp_x,wsp_y)) - qBlue( image3.pixel(wsp_x,wsp_y)));




    }
   }


   MSE = (1/(3*N)) * sum_of_mse;
   RMSE = sqrt(MSE);

   if(MSE == 0)
       PSNR = 100;
   else
       PSNR = 20 * log10(255/RMSE);

   MAE = (1/(3*N) ) * sum_of_mae;

    return std::make_tuple(PSNR, MAE);
}
