#pragma once
#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

template <class T>

class Matrix {
private:
    vector<vector<T>> matrix;
    pair<int, int> size;
public:
    Matrix(const int n, const int m) {
        size = { n, m };
        matrix.resize(n);
        for (int i = 0; i < n; i++) {
            matrix[i].resize(m);
        }
    }
    Matrix(const vector<vector<T>> raw) {
        if (raw.size() == 0)
            return;
        matrix = raw;
        size = { raw.size(), raw[0].size() };
    }
    vector<T>& operator[](const int i) {
        return matrix[i];
    }
    const vector<T> operator[](const int i) const {
        return matrix[i];
    }
    Matrix operator+(const Matrix& a) {
        try {
            if (a.size != size) {
                throw string("Exception of addition of matrices\n");
            }
            Matrix c(size.first, size.second);
            for (int i = 0; i < size.first; i++) {
                for (int j = 0; j < size.second; j++) {
                    c[i][j] = matrix[i][j] + a[i][j];
                }
            }
            return c;
        }
        catch (const string mess) {
            cout << mess;
            return Matrix(0, 0);
        }
    }
    Matrix operator*(const int k) {
        Matrix a(size.first, size.second);
        for (int i = 0; i < size.first; i++) {
            for (int j = 0; j < size.second; j++) {
                a[i][j] = matrix[i][j] * k;
            }
        }
        return a;
    }
    Matrix transposed() {
        Matrix a(size.second, size.first);
        for (int i = 0; i < size.first; i++) {
            for (int j = 0; j < size.second; j++) {
                a[j][i] = matrix[i][j];
            }
        }
        return a;
    }
    Matrix operator-()const {
        Matrix a(size.first, size.second);
        for (int i = 0; i < size.first; i++) {
            for (int j = 0; j < size.second; j++) {
                a[i][j] = -matrix[i][j];
            }
        }
        return a;
    }
    Matrix operator-(const Matrix& a) {
        return (*this) + (-a);
    }
    Matrix operator*(const Matrix& a) {
        try {
            if (size.second != a.size.first) {
                throw string("Exception of multiply of matrices\n");
            }
            Matrix c(size.first, size.first);
            for (int i = 0; i < size.first; i++) {
                for (int j = 0; j < size.first; j++) {
                    for (int c1 = 0; c1 < size.second; c1++) {
                        c[i][j] += matrix[i][c1] * a[c1][j];
                    }
                }
            }
            return c;
        }
        catch (const string mes) {
            cout << mes;
            return Matrix(0, 0);
        }
    }
    bool operator==(const Matrix& a) {
        if (a.size != size)
            return false;
        for (int i = 0; i < size.first; i++)
            for (int j = 0; j < size.second; j++)
                if (matrix[i][j] != a[i][j])
                    return false;
        return true;
    }
    friend istream& operator>>(istream& in, Matrix& a) {
        for (int i = 0; i < a.size.first; i++) {
            for (int j = 0; j < a.size.second; j++) {
                in >> a[i][j];
            }
        }
        return in;
    }
    friend ostream& operator<<(ostream& out, const Matrix& a) {
        out << "{";
        vector<int> margin(a.size.second);
        for (int i = 0; i < a.size.first; i++) {
            for (int j = 0; j < a.size.second; j++) {
                margin[j] = max(margin[j], (int)to_string(a[i][j]).size() + 1);
            }
        }
        for (int i = 0; i < a.size.first; i++) {
            if (i != 0)
                out << " ";
            out << "{";
            for (int j = 0; j < a.size.second; j++) {
                out << setw(margin[j]) << a.matrix[i][j];
            }
            out << "}";
            if (i != a.size.first - 1)
                out << "\n";
        }
        out << "}\n";
        return out;
    }
    T determinant() {
        try {
            if (size.first != size.second) {
                throw string("Determinant of non-square matrix is not defined\n");
            }
            if (size.first == 1 && size.second == 1)
                return matrix[0][0];
            T ans = 0;
            for (int i = 0; i < size.first; i++) {
                Matrix m(size.first - 1, size.first - 1);
                for (int j = 0, j1 = 0; j < size.first; j++, j1++) {
                    if (j == 0) {
                        j1--;
                        continue;
                    }
                    for (int c = 0, c1 = 0; c < size.first; c++, c1++) {
                        if (c == i) {
                            c1--;
                            continue;
                        }
                        m[j1][c1] = matrix[j][c];
                    }
                }
                int d = matrix[0][i] * m.determinant();
                ans += ((i & 1) ? -1 : 1) * d;
            }
            return ans;
        }
        catch (string mes) {
            cout << mes;
            return 0;
        }
    }
};
#endif