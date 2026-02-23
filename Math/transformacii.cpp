#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <string>
 
using namespace std;
 
 
void mnozhenje(const double A[3][3], const double B[3][3], double rez[3][3]) {
    for (int i=0;i<3;i++)
        for (int j=0;j<3; j++) {
            rez[i][j]= 0;
            for (int k=0; k<3; k++){
                rez[i][j]+=A[i][k]*B[k][j];
            }
 
        }
}
 
void mnozhenje_vektor(const double M[3][3], const double v[3], double rez[3]) {
    for (int i=0;i<3; i++) {
        rez[i]=0;
        for (int j=0;j<3; j++)
            rez[i]+=M[i][j]*v[j];
    }
}
 
int main()
{
    ifstream file("C:/Users/MIG-L32/Downloads/square.obj");
    string red;
    vector<double> xk;
    vector<double> yk;
 
    while (getline(file, red)) {
        if (red.rfind("v ", 0) == 0) {
            istringstream iss(red);
            char v;
            double x, y;
 
            iss >> v >> x >> y;
 
            xk.push_back(x);
            yk.push_back(y);
        }
    }
 
    file.close();
 
    int n = xk.size();
    double pi=3.141592653589;
    double c=cos(pi/4);
    double s=sin(pi/4);
 
    double T[3][3]=
    {
        {1,0,2},
        {0,1,0},
        {0,0,1}
    };
 
    double R[3][3]=
    {
        { c, -s, 0 },
        { s,  c, 0 },
        { 0,  0, 1 }
    };
 
    double S[3][3]=
    {
        {4, 0, 0},
        {0, 4, 0},
        {0, 0, 1}
    };
 
 
    double t[3][3], rez[3][3];
    mnozhenje(R, T, t);
    mnozhenje(S, t, rez);
 
    vector<double> x_t, y_t;
 
    for (int i=0;i<n;i++) {
        double a[3]={xk[i], yk[i], 1};
        double b[3]={0, 0, 0};
 
        mnozhenje_vektor(rez, a, b);
 
        x_t.push_back(b[0]);
        y_t.push_back(b[1]);
    }
 
    for(int i=0;i<n;i++)
    {
        int kx=x_t[i];
        int ky=y_t[i];
        cout<<"("<<kx<<", "<<ky<<"),\n";
    }

    return 0;
}