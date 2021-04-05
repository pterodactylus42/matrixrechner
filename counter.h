#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>

class Counter
{
public:
    Counter() {m_value = 0;}
    //const member functions implemented in header??
    int value() const { return m_value; }
public slots:
    void setValue(int value);
signals:
    void valueChanged(int newValue);
private:
    int m_value;
};

#endif // COUNTER_H
