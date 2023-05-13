#ifndef TESTMATRIX_H
#define TESTMATRIX_H

#include <QTest>

class TestMatrix: public QObject
{
    Q_OBJECT
private slots:
    void base_constructor();
    void copy_constructor();
    void sum_matrix();
    void sub_matrix();
    void mul_matrix();
    void mul_matrix_2();
    void mul_number();
    void change_columns();
    void change_rows();
    void add_column();
    void add_row();
    void delete_column();
    void delete_row();
    void get_matrix_element();
    void transpose();
};

#endif // TESTMATRIXROW_H
