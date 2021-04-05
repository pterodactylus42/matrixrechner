#include "rationalezahl.h"

RationaleZahl::RationaleZahl()
{
    this->nenner = 1;
    this->zaehler = 0;
    this->vorzeichen = true;
}

RationaleZahl::RationaleZahl(int z) {
    this->nenner = 1;
    this->zaehler = z;
    this->vorzeichen = true;
}

RationaleZahl::RationaleZahl(int z, int n) {
    this->nenner = n;
    this->zaehler = z;
    this->vorzeichen = true;
}

RationaleZahl::~RationaleZahl() {
    // ...
}

bool RationaleZahl::istPositiv() {
    return vorzeichen;
}

void RationaleZahl::setVorzeichen(bool v) {
    this->vorzeichen = v;
}

void RationaleZahl::wuerfeln() {
    int randomNumber = rand();
    // signed int has 31 bits for numbers... and one for minus.
    randomNumber = randomNumber >> 28;
    // you get values from 0 - 7
    this->zaehler = randomNumber;
    this->nenner = 1;
    // todo : maybe randomize vorzeichen
    this->vorzeichen = true;
}

int RationaleZahl::getZaehler() {
    return zaehler;
}

int RationaleZahl::getNenner() {
    return nenner;
}

void RationaleZahl::setZaehler(int zahl) {
    this->zaehler = zahl;
}

void RationaleZahl::setNenner(int zahl) {
    this->nenner = zahl;
}

int RationaleZahl::euklid(int a, int b) {
    if(b==0) {
        return a;
    } else {
        return euklid(b, a%b);
    }
}

void RationaleZahl::addiere(RationaleZahl plus) {
    /*
     * a   c   ad + cb
     * - + - = -------
     * b   d      bd
     * */
    int z, n;
    if(plus.istPositiv()) {
        z = (this->zaehler * plus.getNenner()) + (plus.getZaehler() * this->nenner);
        n = this->nenner * plus.getNenner();
    } else {
        z = (this->zaehler * plus.getNenner()) - (plus.getZaehler() * this->nenner);
        n = this->nenner * plus.getNenner();
    }
    int e = euklid(z,n);
    this->zaehler = z/e;
    this->nenner = n/e;
    if(this->zaehler >= 0 && this->nenner >= 0) {
        this->vorzeichen = true;
    } else {
        this->vorzeichen = false;
    }
}

void RationaleZahl::addiere(RationaleZahl plus, RationaleZahl faktor) {
    /*
     * a    c   e    ad + cb
     * - + (- * -) = -------
     * b    d   f       bd
     * */
    addiere(produkt(plus,faktor));
}

void RationaleZahl::eigenProdukt(RationaleZahl faktor) {
    /*
     *  c   e    ce
     * (- * -) = --
     *  d   f    df
     * */
    int z, n;
    if(faktor.istPositiv()) {
        z = zaehler * faktor.getZaehler();
    } else {
        z = zaehler * faktor.getZaehler() * (-1);
    }
    n = nenner * faktor.getNenner();
    int e = euklid(z,n);
    setZaehler(z/e);
    setNenner(n/e);
    if(this->zaehler >= 0 && this->nenner >= 0) {
        this->vorzeichen = true;
    } else {
        this->vorzeichen = false;
    }
}

RationaleZahl RationaleZahl::produkt(RationaleZahl p1, RationaleZahl p2) {
    /*
     *  c   e    ce
     * (- * -) = --
     *  d   f    df
     * */
    int z, n;
    z = p1.getZaehler() * p2.getZaehler();
    n = p1.getNenner() * p2.getNenner();
    int e = euklid(z,n);
    z = z/e;
    n = n/e;
    if(this->zaehler >= 0 && this->nenner >= 0) {
        this->vorzeichen = true;
    } else {
        this->vorzeichen = false;
    }
    return RationaleZahl(z,n);
}

void RationaleZahl::subtrahiere(RationaleZahl minus) {
    /*
     * a   c   ad - cb
     * - - - = -------
     * b   d      bd
     * */
    int z, n;
    z = (this->zaehler * minus.getNenner()) - (minus.getZaehler() * this->nenner);
    n = this->nenner * minus.getNenner();
    int e = euklid(z,n);
    this->zaehler = z/e;
    this->nenner = n/e;
    if(this->zaehler >= 0 && this->nenner >= 0) {
        this->vorzeichen = true;
    } else {
        this->vorzeichen = false;
    }
}

void RationaleZahl::subtrahiere(RationaleZahl minus, RationaleZahl faktor) {
    /*
     * a    c   e    ad + cb
     * - + (- * -) = -------
     * b    d   f       bd
     * */
    subtrahiere(produkt(minus,faktor));
}
