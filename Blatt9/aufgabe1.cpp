#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <Eigen/Dense>

using namespace Eigen;

double gFunction(VectorXd t);
MatrixXd determineSupportingPoints(VectorXd xvec_0, VectorXd pvec);
void bisection(VectorXd xvec_0, VectorXd pvec);

// ========================================================================================================
// a function to test the self-implemented bisection method
double gFunction(VectorXd t)
{
    double x = t(0);
    double y = t(1);
    double g = 2*x*x + x*x * y*y;
    return g;
}


// ========================================================================================================
// determine the supporting points (Stützstellen) of the starting intervall from the given starting point "xvec_0"
MatrixXd determineSupportingPoints(VectorXd xvec_0, VectorXd pvec)
{   
    int N = xvec_0.size();
    MatrixXd supportingPoints(N, 3);
    VectorXd yvec_0(N), zvec_0(N);
    zvec_0 = xvec_0;

    uint i;
    for(i = 1; gFunction(xvec_0) > gFunction(zvec_0); i++)
    {
        yvec_0 = zvec_0;
        zvec_0 += pvec;
    }

    supportingPoints.col(0) = xvec_0;
    supportingPoints.col(1) = yvec_0;
    supportingPoints.col(2) = zvec_0;

    if(i == 1) {
        std::cout << "In der Richtung von p " << std::endl;
    }

    return supportingPoints;
}


// ========================================================================================================
// implement the bisection method (Intervallhalbierungsverfahren) along a given direction "pvec"
void bisection(VectorXd xvec_0, VectorXd pvec)
{

}


int main()
{
    VectorXd startingVector(4);
    startingVector << 1, 2, 3, 4;
    std::cout << startingVector.size() << std::endl;
    return 0;
}
