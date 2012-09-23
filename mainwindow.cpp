#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QMenu *FileMenu = new QMenu(tr("Datei"), this);
    menuBar()->addMenu(FileMenu);
    FileMenu->addAction("csv Datei einlesen", this, SLOT(readCSVFile()));
    FileMenu->addAction("lese Referenzdatei", this , SLOT(readGrenzwerte()) );


    connect(ui->btn_MessdatenLesen, SIGNAL(clicked()), this, SLOT(readCSVFile()));
    connect(ui->btn_ReferenzEinlesen, SIGNAL(clicked()), this, SLOT(readGrenzwerte()));
    connect(ui->btnAuswerten, SIGNAL(clicked()), this, SLOT(auswerten()));




}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::readCSVFile () {


    //reset
    Merkmal.clear();
    Messwert.clear();
    ui->txtNio->clear();
    ui->txtUndefinierte->clear();
    ui->lblDatensaetzeDurchsucht->setText("-----");
    ui->lblDatensaetzeNio->setText("-----");
    ui->lblDatensaetzeDurchsucht->setText("-----");



    QString FileName;
    QString Text;

    FileName = QFileDialog::getOpenFileName(this, "Datei öffnen", "", "(*.*)", 0, 0);

    ui->lblMessdatei->setText(FileName);

    if (!FileName.isEmpty())
    {
        QFile File(FileName);


        if (File.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream ds(&File);      //ein Textstream, der mit einem String arbeitet
            QStringList::const_iterator ConstIterator;
            bool FirstColumn = true;
            bool Header = true;


            //Zeile für Zeile
            Text = ds.readLine();
            while (!ds.atEnd())
            {
                while (Header == true)
                {

                    Text = ds.readLine();

                    if (Text.contains("*", Qt::CaseInsensitive))    //"*" markiert Ende des Headers
                    {
                        Header = false;
                    }
                }                                                   // Ende Auslesen des Headers


                Text = ds.readLine();
                while (!Text.contains(';', Qt::CaseInsensitive))    //ignoriere Zeilen ohne Semikolon
                {
                    Text = ds.readLine();
                }

                QStringList Fields = Text.split(";");
                for (ConstIterator = Fields.constBegin(); ConstIterator != Fields.constEnd(); ++ ConstIterator)
                {
                    if (FirstColumn)
                    {
                        FirstColumn = false;
                        Merkmal.append((*ConstIterator).toLocal8Bit().constData());

                    }

                    else
                    {
                            Messwert.append((*ConstIterator).toDouble());

                    }
                }

                FirstColumn = true;
            }


            ui->lblAnzahlDatensaetze->setNum(Merkmal.count());
            File.close();

            }

        }
}



void MainWindow::readGrenzwerte() {

    QString FileName;
    QString Text;

    FileName = QFileDialog::getOpenFileName(this, "Datei öffnen", "", "(*.*)", 0, 0);

    ui->lblReferenzdatei->setText(FileName);

    if (!FileName.isEmpty())
    {
        QFile File(FileName);

        if (File.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream ds(&File);      //ein Textstream, der mit einem String arbeitet

            QStringList::const_iterator ConstIterator;

            bool FirstColumn = true;
            bool SecondColumn = true;
            bool Header = true;

            //Zeile für Zeile
            Text = ds.readLine();

            while (!ds.atEnd())
            {
                while (Header == true)
                {
                    Text = ds.readLine();

                    if (Text.contains("*", Qt::CaseInsensitive))
                    {
                        Header = false;
                    }
                }

                Text = ds.readLine();

                while (!Text.contains(';', Qt::CaseInsensitive))
                {
                    Text = ds.readLine();
                }


                QStringList Fields = Text.split(";");
                for (ConstIterator = Fields.constBegin(); ConstIterator != Fields.constEnd(); ++ ConstIterator)
                {
                    if (FirstColumn)
                    {
                        FirstColumn = false;
                        nameReferenz.append((*ConstIterator).toLocal8Bit().constData());
                    }

                    else
                    {
                        if (SecondColumn)
                        {
                            minimum.append((*ConstIterator).toDouble());
                            SecondColumn = false;
                        }
                        else
                        {
                            maximum.append((*ConstIterator).toDouble());
                        }
                    }


                }
                FirstColumn = true;
                SecondColumn = true;

            }


            ui->lblAnzahlreferenzwerte->setNum(nameReferenz.count());
            File.close();
        }
    }

 }




void MainWindow::sucheUndefinierte() {

    QStringList::ConstIterator Iterator;
    QString Text;

    int counterDurchsucht = 0;
    int counterUndefiniert = 0;

    for (Iterator = Merkmal.constBegin(); Iterator != Merkmal.constEnd(); ++Iterator){


        if (!nameReferenz.contains((*Iterator)))
        {
            Undefinierte.append((*Iterator));
            Text.append(*Iterator);
            Text.append('\n');
            counterUndefiniert++;

            ui->txtUndefinierte->setPlainText(Text);
            ui->lblDatensaetzeUndefiniert->setNum(counterUndefiniert);

        }
        counterDurchsucht++;
        ui->lblDatensaetzeDurchsucht->setNum(counterDurchsucht);

    }
}




void MainWindow::sucheNio() {

    QString Text;
    int counterNio = 0;


    for (int i=0; i < Merkmal.size(); i++)
    {
        for (int k=0; k < Merkmal.size(); k++)
        {
            if (Merkmal.value(i) == nameReferenz.value(k))
            {
                if (Messwert.value(i) < minimum.value(k))
                {
                    Text.append(Merkmal.value(i));
                    Text.append(('\n'));
                    counterNio++;

                }
                if (Messwert.value(i) > maximum.value(k))
                {
                    Text.append(Merkmal.value(i));
                    Text.append(('\n'));
                    counterNio++;
                }
            }

        }


    }

    ui->txtNio->setPlainText(Text);
    ui->lblDatensaetzeNio->setNum(counterNio);



}

void MainWindow::auswerten()
{
    sucheUndefinierte();
    sucheNio();
}

//
//void MainWindow::leseKonfiguration()
//{
//
//}
