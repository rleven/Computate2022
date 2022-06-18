#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <Eigen/Dense>

using namespace Eigen;

double gFunction(VectorXd t);
VectorXd gradientGFunction(VectorXd t);
MatrixXd determineSupportingPoints(VectorXd xvec_0, VectorXd pvec);
VectorXd bisection(VectorXd xvec_0, VectorXd pvec, MatrixXd M_supportingPoints, double epsilon_bisection, double epsilon);
VectorXd steepestDescent(VectorXd xvec_0, double epsilon);
VectorXd conjugatedDescent(VectorXd xvec_0, double epsilon_bisection, double epsilon);

uint counter = 1;

// ========================================================================================================
// a function to test the self-implemented methods
double fFunction(VectorXd t)
{
    double x = t(0);
    double y = t(1);
    double g = 1/(1 + (exp(-10*(x*y-3)*(x*y-3))) / (x*x + y*y));
    return g;
}


// ========================================================================================================
// a function to test the self-implemented methods
double gFunction(VectorXd t)
{
    double x = t(0);
    double y = t(1);
    double g = x*x*y*y + x*x + y*y;
    return g;
}

VectorXd gradientGFunction(VectorXd t)
{
    double x = t(0);
    double y = t(1);
    VectorXd g(t.size());
    g(0) = 2*x + 2*x*y*y;
    g(1) = 2*y + 2*x*y*y;
    return g;
}

// ========================================================================================================
// determine the supporting points (Stützstellen) of the starting intervall from the given starting point "xvec_0" and return the vectors of the supporting points as the columns of a Nx3-Matrix
MatrixXd determineSupportingPoints(VectorXd xvec_0, VectorXd pvec)
{   
    int N = xvec_0.size();
    MatrixXd supportingPoints(N, 3);
    VectorXd yvec_0(N), zvec_0(N);
    VectorXd stepvec = pvec / pvec.norm();
    stepvec *= 0.1;

    uint i;
    if(gFunction(xvec_0) >= gFunction(xvec_0+stepvec))
    {
        yvec_0 = xvec_0;
        zvec_0 = xvec_0 + stepvec;

        for(i = 2; gFunction(zvec_0) < gFunction(yvec_0); i++)
        {
            yvec_0 = zvec_0;
            zvec_0 += stepvec;
        }
    }
    else if(gFunction(xvec_0) > gFunction(xvec_0-stepvec))
    {
        yvec_0 = xvec_0;
        zvec_0 = xvec_0 - stepvec;

        for(i = 2; gFunction(zvec_0) < gFunction(yvec_0); i++)
        {
            yvec_0 = zvec_0;
            zvec_0 -= stepvec;
        }   
        VectorXd tempvec = zvec_0;
        zvec_0 = xvec_0;
        xvec_0 = tempvec;
    }

    supportingPoints.col(0) = xvec_0;
    supportingPoints.col(1) = yvec_0;
    supportingPoints.col(2) = zvec_0;

    return supportingPoints;
}


// ========================================================================================================
// implement the bisection method (Intervallhalbierungsverfahren) along a given direction "pvec"
VectorXd bisection(VectorXd xvec_0, VectorXd pvec, MatrixXd M_supportingPoints, double epsilon)
{
    VectorXd xvec = xvec_0;
    VectorXd yvec = M_supportingPoints.col(1);
    VectorXd zvec = M_supportingPoints.col(2);
    VectorXd uvec(xvec.size());
    // counter = 1;
    // std::cout << (xvec-yvec).norm() << std::endl;
    do
    {
        // std::cout << counter << std::endl;
        // counter++;
        if((xvec-yvec).norm() >= (yvec-zvec).norm())
        {
            uvec = (xvec + yvec)/2;                                 /*Intervallhalbierung*/

            if(gFunction(uvec) <= gFunction(yvec))                   /*generate new interval*/
            {
                xvec = yvec;
                yvec = uvec;
            }
            else if(gFunction(uvec) > gFunction(yvec))
            {
                xvec = uvec;
            }
        }
        else if ((xvec-yvec).norm() < (yvec-zvec).norm())
        {
            uvec = (yvec + zvec)/2;                                 /*Intervallhalbierung*/

            if(gFunction(uvec) <= gFunction(yvec))                   /*generate new interval*/
            {
                xvec = yvec;
                yvec = uvec;
            }
            else if(gFunction(uvec) > gFunction(yvec))
            {
                zvec = uvec;
            }
        }
    }    
    while((zvec - xvec).norm() > epsilon);

    return xvec;
}


// ========================================================================================================
// implement the steepest descent method using the implemented method "bisection"
VectorXd steepestDescent(VectorXd xvec_0, double epsilon_bisection, double epsilon)
{
    VectorXd xvec = xvec_0, pvec;
    MatrixXd M_supportingPoints(xvec_0.size(), 3);

    do
    {
        pvec = -gradientGFunction(xvec);
        M_supportingPoints = determineSupportingPoints(xvec, pvec);
        xvec = bisection(xvec, pvec, M_supportingPoints, epsilon);
    }
    while(gradientGFunction(xvec).norm() > epsilon);
    
    return xvec;
}


// ========================================================================================================
// implement the conjugated descent method using the implemented method "bisection"
VectorXd conjugatedDescent(VectorXd xvec_0, double epsilon_bisection, double epsilon)
{
    VectorXd xvec, xvec_prev, pvec, pvec_prev, grad, grad_prev;
    double mu;
    MatrixXd M_supportingPoints(xvec_0.size(), 3);

    xvec = xvec_0;
    grad = -gradientGFunction(xvec);
    pvec = grad;

    do
    {
        xvec_prev = xvec;
        pvec_prev = pvec;
        grad_prev = grad;

        M_supportingPoints = determineSupportingPoints(xvec, pvec);
        xvec = bisection(xvec, pvec, M_supportingPoints, epsilon);

        grad = -gradientGFunction(xvec);
        mu = (grad.adjoint()*grad);
        mu /= (grad_prev.adjoint()*grad_prev);
        pvec = grad + mu * pvec_prev;
    }
    while(gradientGFunction(xvec).norm() > epsilon);
    
    return xvec;
}


int main()
{
    VectorXd startingVector(2), directionVector(2), minimum(2);
    MatrixXd M_supportingPoints(startingVector.size(), 3);
    double epsilon, epsilon_bisection;

    // Aufgabe 1a) ===================================================
    startingVector << 1, 0;
    directionVector << -2, 0;
    M_supportingPoints = determineSupportingPoints(startingVector, directionVector);
    epsilon = pow(10, -7);
    std::cout << bisection(startingVector, directionVector, M_supportingPoints, epsilon) << std::endl;

    startingVector << 1, 1;
    M_supportingPoints = determineSupportingPoints(startingVector, directionVector);
    std::cout << bisection(startingVector, directionVector, M_supportingPoints, epsilon) << std::endl;


    // Aufgabe 1b) ===================================================
        MatrixXd startingVectors(2, 3);
        startingVectors << 1.5, 100, 100,
                           1,    80, 100;
        epsilon_bisection = pow(10, -5);                        /*the bigger the less bisection steps*/
        epsilon = pow(10, -5);                                  /*the smaller the closer the result to the actual value*/

    std::cout << "Startpunkte für Aufgabe 1b) und 1c):\n" << startingVectors << std::endl;

    for(uint i = 0; i < startingVectors.cols(); i++)
    {
        startingVector = startingVectors.col(i);
        minimum = steepestDescent(startingVector, epsilon_bisection, epsilon);
        std::cout << "Minimum vom " << i+1 << ". Startpunkt aus mit SD:\n" << minimum << std::endl;
    }


    // Aufgabe 1c) ===================================================
    for(uint i = 0; i < startingVectors.cols(); i++)
    {
        startingVector = startingVectors.col(i);
        minimum = conjugatedDescent(startingVector, epsilon_bisection, epsilon);
        std::cout << "Minimum vom " << i+1 << ". Startpunkt aus mit CD:\n" << minimum << std::endl;
    }


    // // Aufgabe 1d) ===================================================
    //     startingVectors << 1.5, -1.7, 0.5,
    //                        2.3, -1.9, 0.6;

    // std::cout << "Startpunkte für Aufgabe 1d):\n" << startingVectors << std::endl;
    
    // for(uint i = 0; i < startingVectors.cols(); i++)
    // {
    //     startingVector = startingVectors.col(i);
    //     minimum = steepestDescent(startingVector, epsilon_bisection, epsilon);
    //     std::cout << "Minimum vom " << i+1 << ". Startpunkt aus mit SD:\n" << minimum << std::endl;
    // }

    // for(uint i = 0; i < startingVectors.cols(); i++)
    // {
    //     startingVector = startingVectors.col(i);
    //     minimum = conjugatedDescent(startingVector, epsilon_bisection, epsilon);
    //     std::cout << "Minimum vom " << i+1 << ". Startpunkt aus mit CD:\n" << minimum << std::endl;
    // }

    return 0;
}
