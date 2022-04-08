#include <ios>
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

/* Definitions of the functions 1 till 3 */
double result1(double x){
    return 1/(sqrt(x))-1/(sqrt(x+1));
}

double result2(double x){
    return (1-cos(x))/sin(x);
}

double result3(double x, double delta){
    return sin(x+delta)-sin(x);
}

int main(){
    /* Definitions of variables */
    double bigX[100], smallX[100], smallD[100], x[100];

    /* Set arbitrary scale, that only abides single rule (this rule is the variables name) */
    for (int i=0; i<100; i++) {
    bigX[i] = 1000.0 + double(i);
    smallX[i] = 0.01 + double(i)/1000;
    smallD[i] = 0.01 + double(i)/1000;
    x[i] = i;
    }

    /* Set output files */
    ofstream teil1, teil2, teil3;
    teil1.open("teil1.log", ios_base::app);
    teil2.open("teil2.log", ios_base::app);
    teil3.open("teil3.log", ios_base::app);
    
    return 0;
}