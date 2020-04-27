#include <iostream>
#include <fstream>
#include "Matrix.h"

using namespace std;

int main() {
    // ћожно заменить на стандартный поток ввода/вывода, если удобнее через консоль
#ifdef _DEBUG
    ifstream in("input.txt");
    ofstream out("output.txt");
    cin.rdbuf(in.rdbuf());
    cout.rdbuf(out.rdbuf());
#endif
    Matrix <int> a(3, 3), b(3, 3);
    cin >> a >> b;
    cout << a << b;
    cout << a * b;
    cout << a + b;
    cout << a - b;
    cout << a.determinant() << "\n" << b.determinant() << "\n";
    cout << a.transposed();
    cout << b * 2;
    Matrix <int> c(2, 3);
    cin >> c;
    cout << c;
    cout << c * b;
    cout << b * c;
    cout << c + b;
    cout << c - b;
    cout << c.determinant() << "\n";
    cout << c.transposed();
    cout << c * -1;
	return 0;
}