#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include "generator.h"
#include <QKeyEvent>

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


protected:
    virtual void keyPressEvent(QKeyEvent * event);


private slots:
    void on_loadafile_clicked();

    void on_execute_clicked();

    void on_dealDMG_clicked();

    void on_horizontalSlider_valueChanged(int value);



    void on_Set_clicked();



public:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
