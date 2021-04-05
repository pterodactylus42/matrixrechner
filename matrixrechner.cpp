#include "matrixrechner.h"

// MatrixRechner subclasses QWidget...
MatrixRechner::MatrixRechner(QWidget *parent)
    : QWidget(parent)
{
    // init array of rational numbers
    initQ();
    ui.setupUi(this);
    // signals are passed as memory addresses to functions ... so are slots ;-)
    QObject::connect(ui.randomButton, &QPushButton::clicked, this, &MatrixRechner::randomMatrix);
    QObject::connect(ui.tauschZeileButton, &QCommandLinkButton::clicked, this, &MatrixRechner::tauschZeile);
    QObject::connect(ui.additionZeileButton, &QCommandLinkButton::clicked, this, &MatrixRechner::addiereZeile);
    QObject::connect(ui.multiplikationButton, &QCommandLinkButton::clicked, this, &MatrixRechner::multipliziereZeile);
    QObject::connect(ui.clearButton, &QPushButton::clicked, this, &MatrixRechner::clearConsole);
}

MatrixRechner::~MatrixRechner()
{
    // no need to implement this
}

void MatrixRechner::initQ() {
    for(int i = 0; i < 36; i++) {
        this->rz[i] = new RationaleZahl(0);
    }
}

void MatrixRechner::randomMatrix()
{
    for(int i = 0; i < 36; i++) {
        this->rz[i]->wuerfeln();
        //qDebug() << i << " " << rz[i]->getZaehler();
    }
    ausgabe();
}

void MatrixRechner::ausgabe() {
    QTextCursor consoleCursor;
    consoleCursor = ui.console->textCursor();
    consoleCursor.movePosition(QTextCursor::Start);
    for(int zeile = 1; zeile <= ui.spinBoxZeilen->value(); zeile++) {
        for(int spalte = 1; spalte <= ui.spinBoxSpalten->value(); spalte++) {
            //what's my number
            consoleCursor.insertText(QString::fromStdString(std::to_string(rz[mapToQIndex(zeile,spalte)]->getZaehler())));
            if(rz[mapToQIndex(zeile,spalte)]->getNenner() != 1) {
                consoleCursor.insertText("/");
                consoleCursor.insertText(QString::fromStdString(std::to_string(rz[mapToQIndex(zeile,spalte)]->getNenner())));
                consoleCursor.insertText(" | ");
            } else {
                consoleCursor.insertText(" | ");
            }
        }
        // carriage return :-)
        consoleCursor.insertText("\n");
    }
    for(int i = 1; i <= ui.spinBoxSpalten->value(); i++) {
        consoleCursor.insertText("- ");
    }
    consoleCursor.insertText("\n");
}

int MatrixRechner::mapToQIndex(int zeile, int spalte) {
    return (spalte -1) + ((zeile-1) * ui.spinBoxSpalten->value());
}

void MatrixRechner::clearConsole() {
    ui.console->clear();
    ausgabe();
    ui.messageLabel->setText("... Matrixrechner ...");
}

void MatrixRechner::tauschZeile() {
    RationaleZahl * tmp;
    if(ui.zeileTausch1->value() > ui.spinBoxZeilen->value() || ui.zeileTausch2->value() > ui.spinBoxZeilen->value()) {
        ui.messageLabel->setText("Zeilenindex außerhalb der Grenzen");
    } else if(ui.zeileTausch1->value() == ui.zeileTausch2->value()) {
        ui.messageLabel->setText("Wähle unterschiedliche Zeilen");
    } else {
        for(int spalte = 1; spalte <= ui.spinBoxSpalten->value(); spalte++) {
           tmp = rz[mapToQIndex(ui.zeileTausch1->value(),spalte)];
           rz[mapToQIndex(ui.zeileTausch1->value(),spalte)] = rz[mapToQIndex(ui.zeileTausch2->value(),spalte)];
           rz[mapToQIndex(ui.zeileTausch2->value(),spalte)] = tmp;
        }
        ui.messageLabel->setText("Zeilentausch durchgeführt");
        ausgabe();
    }
}

// no longer needed
void MatrixRechner::swapFieldText(QLabel *field1, QLabel *field2) {
    QString tmp = field1->text();
    field1->setText(field2->text());
    field2->setText(tmp);
}

RationaleZahl MatrixRechner::parseFaktor(QString faktorString) {
    /*
     * is the given string numerically only?
     *      return the integer value as zaehler
     *      and 1 as nenner
     * else
     *      does it contain a backslash?
     *          separate zaehler and nenner by the slash
     * */
    RationaleZahl * faktorZahl = new RationaleZahl();
    bool allDigit = true;
    for(int i = 0; i < faktorString.size(); i++) {
        if(!faktorString[i].isDigit()) {
            allDigit = false;
        }
    }
    if(allDigit) {
        faktorZahl->setZaehler(faktorString.toInt());
        return *faktorZahl;
    } else {
        if(!faktorString.contains("/")) {
            ui.messageLabel->setText("Rationale Zahlen mit / eingeben");
            return RationaleZahl();
        }
        //the real parsing here:
        QString zaehler, nenner;
        int pos = 0;
        while(faktorString.at(pos) != '/') {
            zaehler.append(faktorString.at(pos));
            pos++;
        }
        faktorZahl->setZaehler(zaehler.toInt());
        pos++;
        while(pos<faktorString.size()) {
            nenner.append(faktorString.at(pos));
            pos++;
        }
        faktorZahl->setNenner(nenner.toInt());
        qDebug() << "I have parsed " << faktorZahl->getZaehler() << " / " << faktorZahl->getNenner() << " for you ...";
        return *faktorZahl;
    }
}

void MatrixRechner::addiereZeile() {
    if(ui.additionFaktor->text().isEmpty()) {
        ui.messageLabel->setText("Kein Faktor angegeben");
        return; // return escapes the function
    }
    if(     ui.dialZeileIn->value() > ui.spinBoxZeilen->value() ||
            ui.dialZeileOut->value() > ui.spinBoxZeilen->value()) {
        ui.messageLabel->setText("Zeile außerhalb der Grenzen");
        return;
    }
    if(ui.dialZeileIn->value() == ui.dialZeileOut->value()) {
        ui.messageLabel->setText("Wähle unterschiedliche Zeilen");
        return;
    }

    // we support integer and rational numbers here ...
    RationaleZahl faktor = parseFaktor(ui.additionFaktor->text());
    if(faktor.getZaehler() != 0) {
        // this zaehler value seems to be sane ...
        for(int spalte = 1; spalte <= ui.spinBoxSpalten->value(); spalte++) {
            if(ui.additionVorzeichen->currentText() == "+") {
                rz[mapToQIndex(ui.dialZeileOut->value(),spalte)]->addiere(*rz[mapToQIndex(ui.dialZeileIn->value(),spalte)],faktor);
            } else {
                rz[mapToQIndex(ui.dialZeileOut->value(),spalte)]->subtrahiere(*rz[mapToQIndex(ui.dialZeileIn->value(),spalte)],faktor);
            }
        }
        ui.messageLabel->setText("Addition durchgeführt");
        ausgabe();
    } else {
        // parsing error, faktor == 0
        ui.messageLabel->setText("Nur natürliche oder rationale Zahlen eingeben, Beispiel: 1/2 ");
    }
}

void MatrixRechner::multipliziereZeile() {
    if(ui.multiplikationFaktor->text().isEmpty()) {
        ui.messageLabel->setText("Kein Faktor angegeben");
        return; // return escapes the function
    }
    if(ui.multiplikationZeile->value() > ui.spinBoxZeilen->value()) {
        ui.messageLabel->setText("Zeile außerhalb der Grenze");
        return;
    } else {
        RationaleZahl faktor = parseFaktor(ui.multiplikationFaktor->text());
        //get vorzeichen from ui
        // currentIndex 0 == + ... 1 == -
        // positive numbers are defined as "true"
        faktor.setVorzeichen( ui.multiplikationVorzeichen->currentIndex() == 0 );
        if(faktor.getZaehler() != 0) {
            // this zaehler value seems to be sane ...
            for(int spalte = 1; spalte <= ui.spinBoxSpalten->value(); spalte++) {
                    rz[mapToQIndex(ui.multiplikationZeile->value(),spalte)]->eigenProdukt(faktor);
            }
            ui.messageLabel->setText("Multiplikation durchgeführt");
            ausgabe();
        } else {
            // parsing error, faktor == 0
            ui.messageLabel->setText("Nur natürliche oder rationale Zahlen eingeben, Beispiel: 1/2 ");
        }
    }
}



const QString MatrixRechner::randomIntAsString() {
    int randomNumber = rand();
    // signed int has 31 bits for numbers... and one for minus.
    randomNumber = randomNumber >> 28;
    return QString::number(randomNumber);
}
