#include <ios>
#include <iostream>
#include <cmath>
#include <fstream>

typedef double (*Function) (double);

double midpoint(Function blank, double a, double b, double h){

    /* Calculation of the step size number N and initial values of the integration */
    double N=(b-a)/h;
    double integration = 0;

    /* Iteration of midpoint rule */
    for (int i=1; i<=N; i++){
        integration = integration + blank(a-h/2+i*h);
    }

    /* Returns final integration value after N iterations */
    return integration*h;
}

double hauptmidpoint(Function blank, Function down, double a, double b, double h, double z){

    /* Calculation of the step size number N and initial values of the integration */
    double N=(b-a)/h;
    double integration = 0;

    /* Iteration of midpoint rule */
    for (int i=1; i<=N; i++){
        if (a-h/2+i*h == 0){
            continue;
        }
        integration = integration + (blank((a-h/2+i*h)*h)-blank(z))/down(a-h/2+i*h);
    }

    /* Returns final integration value after N iterations */
    return integration*h;
}

/* section a) */
double hauptwert(double t){
    return std::exp(t)/t;
}

double hauptwertU(double t){
    return std::exp(t);
}
double hauptwertD(double t){
    return t;
}

/* section b) */
double funktion1(double t){
    return std::exp(-t)/std::sqrt(t);
}

int main(){
    double h = std::pow(10, -5);
    /* Berechnung des Hauptwertintegrals aus a) */
    double first = midpoint(hauptwert, -1, -h, h)+midpoint(hauptwert, h, 1, h);
    std::cout << "Numerical value of regular integrals: " << first << std::endl;
    double second = hauptmidpoint(hauptwertU, hauptwertD, -1, 1, h, 0);
    std::cout << "Hauptwert value of substituted integral: " << second << std::endl;
    std::cout << "Total value of integral: " << first+second << std::endl;

    /* Berechnung aus b) */
    double aufb;
    for (double i=2; i>0; i+=0.1){
        aufb = midpoint(funktion1, 0, i , h);
        double wahr = 1.77245385;
        double check = std::abs(aufb-wahr)/wahr;
        if (check<std::pow(10, -5)){
            std::cout << "Wert: " << aufb << " bei i " << i << std::endl;
        }
    }


    return 0;
}
