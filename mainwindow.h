#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <cdatensatz.h>

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QVector>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Ui::MainWindow *ui;

    QStringList         Merkmal;
    QVector<double>     Messwert;

    QStringList nameReferenz;
    QVector<double> minimum;
    QVector<double> maximum;

    QStringList Undefinierte;





private:



public slots:
    //void leseKonfiguration;


    void readCSVFile();
    void readGrenzwerte();
    void sucheUndefinierte();
    void sucheNio();

    void auswerten();

};

#endif // MAINWINDOW_H
