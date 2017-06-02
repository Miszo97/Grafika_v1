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
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images (*.png *.jpg *.jpeg *.bmp *.gif"));

    if (QString::compare(filename, QString())!= 0){


        bool valid = image1.load(filename);
        image2.load(filename);


        if(valid)
        {

            image1 = image1.scaledToWidth(ui->Image_bar_1->width(), Qt::SmoothTransformation);



            ui->Image_bar_1->setPixmap(QPixmap::fromImage(image1));
            loaded = true;


        } else {
            //error handle
        }
    }
}

void MainWindow::on_execute_clicked()
{

    if(loaded){

   if(ui->comboBox->currentText() ==  "VMF" && demaged){

    filrt_vmf.set_winsize(5);
    filrt_vmf.load_img(image2);

    qInfo()<< "Execute clicked...";
    Stoper st;
    st.Start();
    image3 = filrt_vmf.filtr();
    st.Stop();

   qInfo()<<"Czas wykonywnia: "<<st.GetMs()<<" ms";

    image3 = image3.scaledToWidth(ui->Image_bar_3->width(), Qt::SmoothTransformation);

    ui->Image_bar_3->setPixmap(QPixmap::fromImage(image3));



   } else if (ui->comboBox->currentText() ==  "FASTAMF" ) {
       filtr_fastamf.set_winsize(5);
       filtr_fastamf.load_img(image2);

       qInfo()<< "Execute clicked...";
       Stoper st;
       st.Start();
       image3 = filtr_fastamf.filtr();
       st.Stop();

       qInfo()<<"Czas wykonywnia: "<<st.GetMs()<<" ms";
       ui->Image_bar_3->setPixmap(QPixmap::fromImage(image3));
   }

    }
   else
   {

       msgBox.setText("Load a image first");
       msgBox.exec();
   }

}

void MainWindow::on_dealDMG_clicked()
{
    if(ui->radioButton->isChecked()){





        image2 = generator.deal_dmg(image1,&Generator::ciri);


        demaged = true;
        ui->Image_bar_2->setPixmap(QPixmap::fromImage(image2));

    } else if (ui->radioButton_2->isChecked()){




        image2 = generator.deal_dmg(image1,&Generator::ctri);
        demaged = true;
        ui->Image_bar_2->setPixmap(QPixmap::fromImage(image2));



    } else {

        msgBox.setText("Select type of impuls first");
        msgBox.exec();

    }

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


