#include "matrix.h"
#include <stdlib.h>
#include <time.h>

Matrix::Matrix(int r, int c)
{
    this->rows = r;
    this->cols = c;
    // pseudo - multi dimension
    this->values = new double[rows*cols];
}

Matrix::Matrix() {
    this->rows = 3;
    this->cols = 3;
    this->values = new double[rows*cols];
}

void Matrix::randomize() {
    srand(time(nullptr));
    for (int i = 0; i < this->cols * this->rows; i++) {
        this->values[i] = rand()%10;
    }
}
