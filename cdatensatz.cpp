#include "cdatensatz.h"

cDatensatz::cDatensatz(QString merkmalName)
{
    merkmal = merkmalName;
}


void cDatensatz::setMerkmal(QString merkmalName)
{
    merkmal = merkmalName;
}

void cDatensatz::setMesswert(double Messwert)
{
    messwert = Messwert;
}

void cDatensatz::setUntereGrenze(double UntereGrenze)
{
    untereGrenze = UntereGrenze;
}

void cDatensatz::setObereGrenze(double ObereGrenze)
{
    obereGrenze = ObereGrenze;
}

QString cDatensatz::getMerkmal()
{
    return merkmal;
}

double cDatensatz::getMesswert()
{
    return messwert;
}

double cDatensatz::getObereGrenze()
{
    return obereGrenze;
}

double cDatensatz::getUntereGrenze()
{
    return untereGrenze;
}
