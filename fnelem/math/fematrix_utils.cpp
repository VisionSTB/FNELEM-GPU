/**
FEMATRIX-UTILS
Utilitary functions that use FEMatrix.

@package fnelem.math
@author ppizarror
@date 21/11/2018
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

// Include header
#include "fematrix_utils.h"

/**
 * Creates an identity matrix.
 *
 * @param n Dimension
 * @return
 */
FEMatrix *FEMatrix_identity(int n) {
    FEMatrix *mat = new FEMatrix(n, n);
    for (int i = 0; i < n; i++) {
        mat->set(i, i, 1);
    }
    return mat;
}

/**
 * Creates an vector.
 *
 * @param n Vector length
 * @return
 */
FEMatrix *FEMatrix_vector(int n) {
    return new FEMatrix(n, 1);
}