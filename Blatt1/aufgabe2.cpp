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

//a)

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

//b)

/* This function iterates and saves according to the Midpoint rule */
double midpoint(function blank, double a, double b, int N){

    /* Calculation of the step size h and initial values of the integration */
    double h=(b-a)/N;
    double integration = 0;

    /* Generating of savefile */
    ofstream midpoint;
    midpoint.open("data/midpoint.txt", ios_base::trunc);
    midpoint << "#h   y";

    /* Iteration of midpoint rule */
    for (int i=1; i<=N; i++){
        integration = integration + blank(a-h/2+i*h);
        midpoint << "\n" << i*h << "    " << integration*h;
    }

    /* Returns final integration value after N iterations */
    return integration*h;
}

//c)

/* This function iterates and saves according to the Midpoint rule */
double simpson(function blank, double a, double b, int N){

    /* Calculation of the step size h and initial values of the integration */
    double h = (b-a)/N;
    double integration = (1.0/3.0)*blank(a) + (1.0/3.0)*blank(b);

    /* Generating of savefile */
    ofstream simpson;
    simpson.open("data/simpson.txt", ios_base::trunc);
    simpson << "#h   y";

    /* Iteration of simpson rule */
    for (int i=1; i<=N-1; i++){
        /* Checks if step i is odd */
        if (i % 2 != 0) {
        integration = integration + (4.0/3.0)*blank(a+i*h);
        }
        /* Checks if step i is even */
        if (i % 2 == 0){
        integration = integration + (2.0/3.0)*blank(a+i*h);
        }
        simpson << "\n" << i*h << " " << integration*h;
    }

    /* Returns final integration number after N-1 iterations */
    return integration*h;
}

int main(){
    return 0;
}