#include <ios>
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

/* Any function can be implemented here */
double f(double x){
    return 1/(1+pow(x,2));
}

/* Here we define a passing of a function */
typedef double (*function) (double);

/* This function iterates and saves according to the Trapezoidal rule */
double trapez(function blank, double a, double b, int N){
    /* Calculation of the step size h and initial values of the integration */
    double h = (b -a)/N;
    double integration = blank(a) + blank(b);

    /* Generating of savefile */
    ofstream trapez;
    trapez.open("data/trapez.txt", ios_base::trunc);
    trapez << "#h   y";

    /* Iteration of trapezoidal rule */
    for (int i=1; i<=N-1; i++){
        double step = a +i*h;
        integration = integration + 2*blank(step);
        trapez << "\n" << i*h << "  " << integration*(h/2);
    }

    /* Returns final integration value after N-1 iterations */
    return integration*(h/2);
}

int main(){
    
    cout << trapez(f, 10, 15, 100);
    return 0;
}