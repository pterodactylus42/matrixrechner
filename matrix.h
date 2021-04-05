#ifndef MATRIX_H
#define MATRIX_H


class Matrix
{
public:
    Matrix();
    Matrix(int r, int c);
    ~Matrix();

    void randomize();

private:
    int rows;
    int cols;
    double * values;
};

#endif // MATRIX_H
