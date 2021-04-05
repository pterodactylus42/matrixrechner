#include "counter.h"

//Counter::Counter()
//{

//}

void Counter::setValue(int newValue) {
    if(m_value != newValue) {
        m_value = newValue;
        emit valueChanged(newValue);
    }
}
