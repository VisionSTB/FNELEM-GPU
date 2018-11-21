/**
FNELEM-GPU - TEST
Test matrix.

@package test
@author ppizarror
@date 19/11/2018
@license
	MIT License
	Copyright (c) 2018 Pablo Pizarro R.

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

// Include sources
#include "../fnelem/math/FEMatrix.h"
#include "../fnelem/math/matrix_inversion_cpu.h"
#include <iostream>
#include <cassert>

void test_matrix_init() {
    FEMatrix matrix = FEMatrix(3, 5);
    matrix.fill_zeros();
    int *dim = matrix.size();
    assert(dim[0] == 3);
    assert(dim[1] == 5);
    matrix.set(0, 0, 10);
    assert(matrix.get(0, 0) == 10);
    delete[] dim;
}

void test_matrix_disp() {
    FEMatrix matrix = FEMatrix(3, 3);
    matrix.fill_ones();
    matrix.disp();
    assert(matrix.is_square());
}

void test_matrix_cpu_inverse() {
    FEMatrix mat = FEMatrix(3, 3);
    mat.set(0, 0, 1);
    mat.set(0, 1, 2);
    mat.set(0, 2, 3);
    mat.set(1, 0, 5);
    mat.set(1, 1, 2);
    mat.set(1, 2, 1);
    mat.set(2, 0, 2);
    mat.set(2, 1, 2);
    mat.set(2, 2, 3);
    mat.save_to_file("test-matrix-pre-inversion.txt");
    mat.disp();
}

void test_matrix_array() {
    FEMatrix mat = FEMatrix(2, 2);
    double *arr = mat.get_array();
    assert(arr[0] == 0);
    delete[] arr;
}

int test_cpu_inversion() {
    int n = 3;
    auto *L = new double[n * n];
    L[0 * 3 + 0] = 1;
    L[0 * 3 + 1] = 2;
    L[0 * 3 + 2] = 3;
    L[1 * 3 + 0] = 5;
    L[1 * 3 + 1] = 2;
    L[1 * 3 + 2] = 1;
    L[2 * 3 + 0] = 2;
    L[2 * 3 + 1] = 2;
    L[2 * 3 + 2] = 3;
    FEMatrix mat = FEMatrix(n, n, L);
    FEMatrix matInverse = matrix_inverse_cpu(&mat);
    matInverse.disp();
    delete[] L;
}

void test_add() {
    FEMatrix m1 = FEMatrix(3, 3);
    m1.fill_ones();
    FEMatrix m2 = FEMatrix(3, 3);
    m2.fill_ones();
    m2.set(0, 0, 3);
    m2.set(1, 1, 5);
    m2.disp();

    // Adds
    m2 += m1;
    assert(m2.get(0, 0) == 4);
    assert(m2.get(1, 1) == 6);

    // Assignation
    m1 = m2;
    assert(m1.get(0, 0) == 4);
    assert(m1.get(1, 1) == 6);
}

void test_substract() {
    FEMatrix m1 = FEMatrix(3, 3);
    m1.fill_ones();
    FEMatrix m2 = FEMatrix(3, 3);
    m2.fill_ones();
    m2.set(0, 0, 3);
    m2.set(1, 1, 5);
    FEMatrix m3 = m2 - m1;
    assert(m3.get(0, 0) == 2);
    m3 = -m3;
    assert(m3.get(0, 0) == -2);
}

void test_transpose() {
    FEMatrix m1 = FEMatrix(2, 3);
    m1.set(0, 0, 1);
    m1.set(0, 1, 1);
    m1.set(0, 2, 5);
    m1.set(1, 0, 9);
    m1.set(1, 1, 10);
    m1.set(1, 1, -1);
    m1.disp();
    m1.transpose_self();
    m1.disp();
}

void test_multiplication() {
    FEMatrix m1 = FEMatrix(2, 3);
    m1.set(0, 0, 1);
    m1.set(0, 1, 2);
    m1.set(0, 2, 3);
    m1.set(1, 0, 4);
    m1.set(1, 1, 5);
    m1.set(1, 2, 6);
    m1.disp();
    FEMatrix m2 = m1.clone();
    m2.transpose_self();
    m1 *= m2;
    m1.disp();
    assert(m1.max() == 77);
    assert(m1.min() == 14);
}

void test_identity() {
    FEMatrix m = FEMatrix(4, 4);
    m.set_origin(1);
    m.set(1, 1, 1);
    m.set(1, 2, 5);
    m.set(1, 3, 7);
    m.set(1, 4, 8);
    m.set(2, 1, 123);
    m.set(2, 2, 2432);
    m.set(2, 3, 22);
    m.set(2, 4, 2);
    m.set(3, 1, 45);
    m.set(3, 2, 345);
    m.set(3, 3, 65);
    m.set(3, 4, 7);
    m.set(4, 1, 2);
    m.set(4, 2, 8);
    m.set(4, 3, 22);
    m.set(4, 4, 34);
    m.disp();

    // Multiply by inverse
    FEMatrix im = matrix_inverse_cpu(&m);
    im.disp();
    m *= im;
    m.disp();

    // Check identity
    assert(m.is_identity());
}

void test_symmetric() {
    FEMatrix m = FEMatrix(3, 3);
    m.set_origin(1);
    m.set(1, 1, 3);
    m.set(2, 2, 6);
    m.set(3, 3, 7);
    m.set(1, 2, 5);
    m.set(2, 1, 5);
    m.disp();
    assert(m.is_symmetric());
    m.transpose_self();
    assert(m.is_symmetric());
}

void test_make_symmetric() {
    FEMatrix m = FEMatrix(3, 3);
    m.set_origin(1);
    m.set(1, 1, 3);
    m.set(2, 2, 6);
    m.set(3, 3, 7);
    m.set(1, 2, 5);
    m.set(2, 3, 8);
    m.disp();
    assert(!m.is_symmetric());
    m.make_symmetric();
    m.disp();
    assert(m.is_symmetric());
}

void test_constant_multiplication() {
    FEMatrix m = FEMatrix(5, 7);
    m.fill_ones();
    m *= 5;
    m.disp();
    assert(m.sum() == 5 * 7 * 5);
}

void test_row_column() {
    FEMatrix m = FEMatrix(4, 4);
    m.set_origin(1);
    m.set(1, 1, 1);
    m.set(1, 2, 2);
    m.set(1, 3, 3);
    m.set(1, 4, 4);
    m.set(2, 1, 5);
    m.set(2, 2, 6);
    m.set(2, 3, 7);
    m.set(2, 4, 8);
    m.set(3, 1, 9);
    m.set(3, 2, 10);
    m.set(3, 3, 11);
    m.set(3, 4, 12);
    m.set(4, 1, 13);
    m.set(4, 2, 14);
    m.set(4, 3, 15);
    m.set(4, 4, 16);
    m.disp();

    // Test row
    FEMatrix row1 = m.get_row(1, 1, 4); // [1, 2, 3, 4]
    row1.disp();
    assert(row1.get(1) == 1 && row1.get(2) == 2 && row1.get(3) == 3 && row1.get(4) == 4);
    FEMatrix row4 = m.get_row(4); // [13, 14, 15, 16]
    row4.disp();
    assert(row4.get(1) == 13 && row4.get(2) == 14 && row4.get(3) == 15 && row4.get(4) == 16);
    FEMatrix r = m.get_row(3, 2, 2); // [9, 10, 11, 12]
    assert(r.get(1) == 10);
    r = m.get_row(3, 1, 3); // [9, 10, 11, 12]
    r.disp();
    assert(r.length() == 3);

    // Test column
    FEMatrix col1 = m.get_column(1); // [1, 5, 9, 13]
    col1.disp();
    assert(col1.length() == 4);

    // Test multipication
    FEMatrix colt = col1.clone().transpose();
    colt.disp();
    colt *= col1;
    colt.disp();
    assert(colt.get(1) == 1 + 5 * 5 + 9 * 9 + 13 * 13);
}

void test_equal() {
    FEMatrix a = FEMatrix(12, 4);
    a.fill(2);
    a *= 0.5;
    FEMatrix b = FEMatrix(12, 4);
    b.fill_ones();
    assert(a == b);
    b *= 0.3;
    assert(a != b);
}

int main() {
    test_matrix_init();
    test_matrix_disp();
    test_matrix_cpu_inverse();
    test_matrix_array();
    test_cpu_inversion();
    test_add();
    test_substract();
    test_transpose();
    test_multiplication();
    test_identity();
    test_symmetric();
    test_make_symmetric();
    test_constant_multiplication();
    test_row_column();
    test_equal();
    return 0;
}