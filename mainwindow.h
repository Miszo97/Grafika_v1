#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include "generator.h"
#include <QKeyEvent>
#include "fastamf.h"
#include <math.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Generator generator;
    QMessageBox msgBox;
    QImage vmf(QImage img, int);
    double PSNR, MAE, MSE, RMSE;


protected:
    virtual void keyPressEvent(QKeyEvent * event);


private slots:
    void on_loadafile_clicked();

    void on_execute_clicked();

    void on_dealDMG_clicked();

    void on_horizontalSlider_valueChanged(int value);



    void on_Set_clicked();



    void on_Save_clicked();

    void on_winsize_line_editingFinished();

    void on_prog_val_line_editingFinished();

public:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
