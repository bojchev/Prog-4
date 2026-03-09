#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

void mnozhenje(const double A[4][4], const double B[4][4], double rez[4][4]) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            rez[i][j] = 0;
            for (int k = 0; k < 4; k++)
                rez[i][j] += A[i][k] * B[k][j];
        }
}

void mnozhenje_vektor(const double M[4][4], const double v[4], double rez[4]) {
    for (int i = 0; i < 4; i++) {
        rez[i] = 0;
        for (int j = 0; j < 4; j++)
            rez[i] += M[i][j] * v[j];
    }
}

int main() {
    ifstream file("monkey.obj");
    string red;
    vector<double> xk, yk, zk;

    while (getline(file, red)) {
        if (red.rfind("v ", 0) == 0) {
            istringstream iss(red);
            char v;
            double x, y, z = 0.0;
            iss >> v >> x >> y >> z;
            xk.push_back(x);
            yk.push_back(y);
            zk.push_back(z);
        }
    }
    file.close();

    int n = xk.size();
    const double pi = 3.141592653589793;


    double ax = 45.0 * pi / 180.0;
    double ay = 27.0 * pi / 180.0;
    double az = 10.0 * pi / 180.0;

    double cx = cos(ax), sx_r = sin(ax);
    double cy = cos(ay), sy_r = sin(ay);
    double cz = cos(az), sz_r = sin(az);

    double Rx[4][4] = {
        {1,    0,     0,    0},
        {0,   cx,  -sx_r,  0},
        {0,  sx_r,   cx,   0},
        {0,    0,     0,    1}
    };

    double Ry[4][4] = {
        { cy,  0,  sy_r, 0},
        {  0,  1,    0,  0},
        {-sy_r, 0,  cy,  0},
        {  0,  0,    0,  1}
    };

    double Rz[4][4] = {
        {cz,  -sz_r, 0, 0},
        {sz_r,  cz,  0, 0},
        { 0,    0,   1, 0},
        { 0,    0,   0, 1}
    };

    double S[4][4] = {
        {1.5,  0,  0,  0},
        { 0,  -1,  0,  0},
        { 0,   0,  1,  0},
        { 0,   0,  0,  1}
    };


    double t1[4][4], t2[4][4], rez[4][4];
    mnozhenje(Ry, Rx, t1);
    mnozhenje(Rz, t1, t2);
    mnozhenje(S,  t2, rez);

    vector<double> x_t, y_t, z_t;

    for (int i = 0; i < n; i++) {
        double a[4] = {xk[i], yk[i], zk[i], 1.0};
        double b[4] = {0, 0, 0, 0};
        mnozhenje_vektor(rez, a, b);
        x_t.push_back(b[0]);
        y_t.push_back(b[1]);
        z_t.push_back(b[2]);
    }

    for (int i = 0; i < n; i++) {
        cout << "(" << x_t[i] << ", " << y_t[i] << ", " << z_t[i] << ")\n";
    }

    return 0;
}
