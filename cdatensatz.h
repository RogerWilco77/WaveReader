#ifndef CDATENSATZ_H
#define CDATENSATZ_H

#include <QString>


class cDatensatz
{
public:
    cDatensatz(QString merkmalName);

    void setMerkmal(QString merkmalName);
    void setMesswert(double Messwert);
    void setUntereGrenze(double UntereGrenze);
    void setObereGrenze(double ObereGrenze);

    QString getMerkmal();
    double getMesswert();
    double getUntereGrenze();
    double getObereGrenze();



private:
    QString     merkmal;
    double      messwert;
    double      untereGrenze;
    double      obereGrenze;


};

#endif // CDATENSATZ_H
