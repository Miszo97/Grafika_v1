#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QList>
#include <QDebug>
#include <Qpainter>
#include <QRgb>
#include "Stoper.h"
#include <iostream>
#include "filtr.h"
#include "vmf.h"
#include "fastamf.h"
#include "functions.h"
#include <tuple>

 Vmf filrt_vmf;
 FASTAMF filtr_fastamf;

 bool loaded, demaged;
 QImage image1;
 QImage image2;
 QImage image3;


 void MainWindow::keyPressEvent(QKeyEvent * a)
 {
     if (ui->lineEditOfp->isModified()){
         if( a->key() == Qt::Key_Return || a->key() == Qt::Key_Enter)
         {
             QString text = ui->lineEditOfp->text();
             double number = text.toDouble();
             generator.set_p(number/100);
         }
     }
 }




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadafile_clicked()

{

    if(loaded)
        ui->drop_down_list->clear();

    QString filename = QFileDialog::getOpenFileName(this,tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg *.bmp)"));

    if (QString::compare(filename, QString())!= 0){


        bool valid = image1.load(filename);



        if(valid)
        {





            ui->Image_bar_1->setPixmap(QPixmap::fromImage(image1.scaledToWidth(ui->Image_bar_1->width(), Qt::SmoothTransformation)));
            loaded = true;
            ui->drop_down_list->addItem(tr("image1"));


        } else {
            //error handle
        }
    }
}

void MainWindow::on_execute_clicked()
{


    if(loaded && demaged){

        if (generator.get_p()!=0 && (filtr_fastamf.get_winsize()%2) && filtr_fastamf.get_winsize() >=3){

            if(ui->comboBox->currentText() ==  "VMF" && demaged){


                filrt_vmf.load_img(image2);


                qInfo()<< "Execute clicked...";
                Stoper st;
                st.Start();
                image3 = filrt_vmf.filtr();
                st.Stop();

                qInfo()<<"Czas wykonywnia: "<<st.GetMs()<<" ms";


                ui->Image_bar_3->setPixmap(QPixmap::fromImage(image3.scaledToWidth(ui->Image_bar_3->width(), Qt::SmoothTransformation)));






            } else if (ui->comboBox->currentText() ==  "FASTAMF" ) {

                filtr_fastamf.load_img(image2);

                qInfo()<< "Execute clicked...";
                Stoper st;
                st.Start();
                image3 = filtr_fastamf.filtr();
                st.Stop();

                qInfo()<<"Czas wykonywnia: "<<st.GetMs()<<" ms";

                ui->Image_bar_3->setPixmap(QPixmap::fromImage(image3.scaledToWidth(ui->Image_bar_3->width(), Qt::SmoothTransformation)));

            }
            if (ui->drop_down_list->count() != 3)
                ui->drop_down_list->addItem(tr("image3"));





            auto PSNR_MAE_img_1_3 = getPSNR_MAE(image1, image3);
            auto PSNR_MAE_img_1_2 = getPSNR_MAE(image1, image2);

            ui->psnr_result->setText(QString::number(std::get<0>(PSNR_MAE_img_1_3)));
            ui->mae_result->setText(QString::number(std::get<1>(PSNR_MAE_img_1_3)));

            ui->psnr_result_2->setText(QString::number(std::get<0>(PSNR_MAE_img_1_2)));
            ui->mae_result_2->setText(QString::number(std::get<1>(PSNR_MAE_img_1_2)));

        }

        else {
            msgBox.setText("Either param p is 0 or incorrect winsize value");
            msgBox.exec();
        }
    }
    else
    {

        msgBox.setText("Demage a image first");
        msgBox.exec();
    }





}

void MainWindow::on_dealDMG_clicked()
{
    if(ui->radioButton->isChecked()){







        image2 = generator.deal_dmg(image1,&Generator::ciri);


        demaged = true;
        ui->Image_bar_2->setPixmap(QPixmap::fromImage(image2.scaledToWidth(ui->Image_bar_2->width(), Qt::SmoothTransformation)));

    } else if (ui->radioButton_2->isChecked()){




        image2 = generator.deal_dmg(image1,&Generator::ctri);
        demaged = true;
        ui->Image_bar_2->setPixmap(QPixmap::fromImage(image2.scaledToWidth(ui->Image_bar_2->width(), Qt::SmoothTransformation)));



    } else {

        msgBox.setText("Select type of impuls first");
        msgBox.exec();
        return;

    }

    if (ui->drop_down_list->count() == 1)
    ui->drop_down_list->addItem(tr("image2"));

}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    generator.set_p(value/100.0);
    ui->label_5->setText(QString::number(value) + "%");



}

void MainWindow::on_Set_clicked()
{
    QString text = ui->lineEditOfp->text();
    double number = text.toDouble();
    generator.set_p(number/100);
}



void MainWindow::on_Save_clicked()
{
    if (ui->drop_down_list->count() != 0){
    int index = ui->drop_down_list->currentIndex();
    QString filename;
    switch( index )
    {
    case 0:

        filename = QFileDialog::getSaveFileName(this, tr("Save file"), "ORG.png", tr("Images (*.png *.jpg *.jpeg *.bmp *.gif"));
        image1.save(filename);
        break;

    case 1:
        filename = QFileDialog::getSaveFileName(this, tr("Save file"), "NOISY.png", tr("Images (*.png *.jpg *.jpeg *.bmp *.gif"));
        image2.save(filename);
        break;

        //...
    case 2:
        filename = QFileDialog::getSaveFileName(this, tr("Save file"), "FILTRED.png", tr("Images (*.png *.jpg *.jpeg *.bmp *.gif"));
        image3.save(filename);
        break;

    }

} else
    {

        msgBox.setText("No images exist right now!");
        msgBox.exec();
    }

}

void MainWindow::on_winsize_line_editingFinished()
{
    filrt_vmf.set_winsize(ui->winsize_line->text().toInt());
    filtr_fastamf.set_winsize(ui->winsize_line->text().toInt());
}

void MainWindow::on_prog_val_line_editingFinished()
{
    filtr_fastamf.setProgVal(ui->prog_val_line->text().toInt());
}
