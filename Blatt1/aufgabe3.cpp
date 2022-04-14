#include <ios>
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

/* Here we define a passing of a function */
typedef double (*Function) (double);

/* This function iterates and saves according to the Trapezoidal rule */
double trapez(Function blank, double a, double b, int N){

    /* Calculation of the step size h and initial values of the integration */
    double h = (b -a)/N;
    double integration = blank(a+h) + blank(b);

    /* Iteration of trapezoidal rule */
    for (int i=1; i<=N-1; i++){
        double step = a +i*h;
        integration = integration + 2*blank(step);
    }

    /* Returns final integration value after N-1 iterations */
    return integration*(h/2);
}

/* This function iterates and saves according to the Midpoint rule */
double midpoint(Function blank, double a, double b, int N){

    /* Calculation of the step size h and initial values of the integration */
    double h=(b-a)/N;
    double integration = 0;

    /* Iteration of midpoint rule */
    for (int i=1; i<=N; i++){
        integration = integration + blank(a-h/2+i*h);
    }

    /* Returns final integration value after N iterations */
    return integration*h;
}

/* This function iterates and saves according to the Midpoint rule */
double simpson(Function blank, double a, double b, int N){

    /* Calculation of the step size h and initial values of the integration */
    double h = (b-a)/N;
    double integration = (1.0/3.0)*blank(a+h) + (1.0/3.0)*blank(b);

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
    }

    /* Returns final integration number after N-1 iterations */
    return integration*h;
}

//a)

double fkta(double x){
  return exp(-x)/x;
}

//b)

double fktb(double x){
  return x*sin(1/x);
}

int main(){

  /* Chunk for initializing savefiles */
  ofstream trapeza, trapezb, midpointa, midpointb, simpsona, simpsonb;
  trapeza.open("data/trapez_a.txt", ios_base::trunc);
  trapezb.open("data/trapez_b.txt", ios_base::trunc);
  midpointa.open("data/midpoint_a.txt", ios_base::trunc);
  midpointb.open("data/midpoint_b.txt", ios_base::trunc);
  simpsona.open("data/simpson_a.txt", ios_base::trunc);
  simpsonb.open("data/simpson_b.txt", ios_base::trunc);
  trapeza << "#N   y";
  trapezb << "#N   y";
  midpointa << "#N   y";
  midpointb << "#N   y";
  simpsona << "#N   y";
  simpsonb << "#N   y";

  for (int i=1; i<12; i++){

    /* Writing all rules in files depending on stepsize */
    trapeza << "\n" << pow(2, i)*10 << "  " << trapez(fkta, 1, 100, pow(2, i)*10);
    trapezb << "\n" << pow(2, i)*10 << "  " << trapez(fktb, 0, 1, pow(2, i)*10);
    midpointa << "\n" << pow(2, i)*10 << "  " << midpoint(fkta, 1, 100, pow(2, i)*10);
    midpointb << "\n" << pow(2, i)*10 << "  " << midpoint(fktb, 0, 1, pow(2, i)*10);
    simpsona << "\n" << pow(2, i)*10 << "  " << simpson(fkta, 1, 100, pow(2, i)*10);
    simpsonb << "\n" << pow(2, i)*10 << "  " << simpson(fktb, 0, 1, pow(2, i)*10);
  }
  return 0;
}