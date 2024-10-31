
#include <iostream>
#include <fstream>

using namespace std;

class Matrix {
public:
    int matrix_size;
    double** matrix_data;

    Matrix(int size = 0) : matrix_size(size) {
        matrix_data = new double*[matrix_size];
        for (int i = 0; i < matrix_size; ++i) {
            matrix_data[i] = new double[matrix_size];
        }
    }

     Matrix& operator=(const Matrix& other) {
        if (this == &other) {
            return *this;
        }

        for (int i = 0; i < matrix_size; ++i) {
            delete[] matrix_data[i];
        }
        delete[] matrix_data;

        matrix_size = other.matrix_size;

        matrix_data = new double*[matrix_size];
        for (int i = 0; i < matrix_size; ++i) {
            matrix_data[i] = new double[matrix_size];
            for (int j = 0; j < matrix_size; ++j) {
                matrix_data[i][j] = other.matrix_data[i][j];
            }
        }

        return *this;
     }

    ~Matrix() {
        for (int i = 0; i < matrix_size; ++i) {
            delete[] matrix_data[i];
        }
        delete[] matrix_data;
    }
};

void read_matrix_from_file(const string& file_name, Matrix& matrix_1, Matrix& matrix_2) {
    ifstream file_obj (file_name);
    if (file_obj.is_open()) {
        int size;
        file_obj >> size;

        matrix_1 = Matrix(size);
        matrix_2 = Matrix(size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                file_obj >> matrix_1.matrix_data[i][j];
            }
        }
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                file_obj >> matrix_2.matrix_data[i][j];
            }
        }
        file_obj.close();
    }
}

void print_matrix(const Matrix& matrix) {
    for (int i = 0; i < matrix.matrix_size; i++) {
        for (int j = 0; j < matrix.matrix_size; j++) {
            cout << matrix.matrix_data[i][j] << " ";
        }
        cout << endl;
    }
}

void print_matrix(const Matrix& matrix_1, const Matrix& matrix_2) {
    print_matrix(matrix_1);
    print_matrix(matrix_2);
}

Matrix add_matrices(const Matrix& matrix_1, const Matrix& matrix_2) {
    if (matrix_1.matrix_size != matrix_2.matrix_size) {
        cerr << "error: cannot add two matrices with different dimensions" << endl;
    }

    Matrix res(matrix_1.matrix_size);
    for (int i = 0; i < matrix_1.matrix_size; i++) {
        for (int j = 0; j < matrix_1.matrix_size; j++) {
            res.matrix_data[i][j] = matrix_1.matrix_data[i][j] + matrix_2.matrix_data[i][j];
        }
    }
    return res;
}

Matrix multiply_matrices(const Matrix& matrix_1, const Matrix& matrix_2) {
    Matrix res(matrix_1.matrix_size);
    for (int i = 0; i < matrix_1.matrix_size; i++) {
        for (int j = 0; j < matrix_1.matrix_size; j++) {
            for (int k = 0; k < matrix_1.matrix_size; k++) {
                res.matrix_data[i][j] += (matrix_1.matrix_data[i][k] * matrix_2.matrix_data[k][j]);
            }
        }
    }
    return res;
}

// Overloaded + operator for matrix addition
Matrix operator+(const Matrix& matrix_1, const Matrix& matrix_2) {
    return add_matrices(matrix_1, matrix_2);
}

// Overloaded * operator for matrix multiplication
Matrix operator*(const Matrix& matrix_1, const Matrix& matrix_2) {
    return multiply_matrices(matrix_1, matrix_2);
}

void get_diagonal_sum(const Matrix& matrix) {
    int res = 0;
    for (int i = 0; i < matrix.matrix_size; i++) {
        res += matrix.matrix_data[i][i];
    }
    cout << res << endl;
}

void swap_matrix_row(Matrix& matrix, int row1, int row2) {
    if (max(row1, row2) >= matrix.matrix_size) {
        cerr << "error: swap_matrix_row indices row1 and row2 need to be in range" << endl;
    }

    for (int i = 0; i < matrix.matrix_size; i++) {
        double temp = matrix.matrix_data[row1][i];
        matrix.matrix_data[row1][i] = matrix.matrix_data[row2][i];
        matrix.matrix_data[row2][i] = temp;
    }

    print_matrix(matrix);
}

int main(int argc, char* argv[]) {
    Matrix matrix_1, matrix_2;
    read_matrix_from_file("matrix.txt", matrix_1, matrix_2);

    cout << "print_matrix" << endl;
    print_matrix(matrix_1, matrix_2);

    cout << "add_matrices result:" << endl;
    Matrix add_result_1 = add_matrices(matrix_1, matrix_2);
    Matrix add_result_2 = matrix_1 + matrix_2;
    print_matrix(add_result_1);
    print_matrix(add_result_2);

    cout << "multiply_matrices result:" << endl;
    Matrix multiply_result_1 = multiply_matrices(matrix_1, matrix_2);
    Matrix multiply_result_2 = matrix_1 * matrix_2;
    print_matrix(multiply_result_1);
    print_matrix(multiply_result_2);

    cout << "get matrix diagonal sum" << endl;
    get_diagonal_sum(matrix_1);

    cout << "swap matrix rows" << endl;
    swap_matrix_row(matrix_1, 0, 1);

    return 0;
}
