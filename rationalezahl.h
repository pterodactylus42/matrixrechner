#ifndef RATIONALEZAHL_H
#define RATIONALEZAHL_H

#include <stdlib.h>
#include <QDebug>

class RationaleZahl
{
public:
    RationaleZahl();
    RationaleZahl(int z);
    RationaleZahl(int z, int n);
    ~RationaleZahl();

    void setZaehler(int zahl);
    void setNenner(int zahl);
    void wuerfeln();

    void addiere(RationaleZahl plus);
    void addiere(RationaleZahl plus, RationaleZahl faktor);
    void subtrahiere(RationaleZahl minus);
    void subtrahiere(RationaleZahl minus, RationaleZahl faktor);
    void eigenProdukt(RationaleZahl faktor);

    int getZaehler();
    int getNenner();
    bool istPositiv();
    void setVorzeichen(bool v);

private:
    int zaehler;
    int nenner;
    bool vorzeichen; // true = positive

    RationaleZahl produkt(RationaleZahl p1, RationaleZahl p2);
    int euklid(int a, int b);
};

#endif // RATIONALEZAHL_H
