#ifndef MATRIXRECHNER_H
#define MATRIXRECHNER_H

#include <QWidget>
#include "rationalezahl.h"
#include "ui_matrixrechner.h"
#include <string.h>
#include <QDebug>


class MatrixRechner : public QWidget
{
    Q_OBJECT

public:
    MatrixRechner(QWidget *parent = nullptr);
    ~MatrixRechner();

signals:

public slots:
    void randomMatrix();
    void tauschZeile();
    void addiereZeile();
    void multipliziereZeile();

private:
    Ui::Matrixrecher ui;
    void initQ();
    void ausgabe();
    const QString randomIntAsString();
    void swapFieldText(QLabel *field1, QLabel *field2);
    int mapToQIndex(int zeile, int spalte);
    void clearConsole();
    RationaleZahl parseFaktor(QString faktorString);

    // todo: allocate numbers dynamically
    RationaleZahl * rz[36];

private slots:

};

#endif // MATRIXRECHNER_H
