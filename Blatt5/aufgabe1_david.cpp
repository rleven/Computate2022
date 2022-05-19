#include <iostream>

#include <cmath>
#include <fstream>
#include <Eigen/Dense>

using namespace Eigen;

MatrixXd startingChargeDistribution(uint numberOfLaticeRows, char subTask);
MatrixXd startingPotential(uint numberOfLaticeRows, char subTask);
void gaussSeidel(MatrixXd startingRho, MatrixXd startingPhi, double spaceBetweenLaticePoints, double epsilon, char aufgabe);
MatrixXd gaussSeidelOneStep(MatrixXd startingRho, MatrixXd phi_old, double spaceBetweenLaticePoints);
void analyticalGaussSeidel(MatrixXd startingRho, double epsilon);

//==============================================================================================================================
// Gauß-Seidel scheme (calls "gaussSeidelOneStep()")
void gaussSeidel(MatrixXd startingRho, MatrixXd startingPhi, double spaceBetweenLaticePoints, double epsilon, char aufgabe)
{
    std::string subTask(1, aufgabe);
    std::ofstream outputFile_phi;
    outputFile_phi.open("data/Potential_" + subTask + ".csv", std::ios_base::trunc);
    outputFile_phi << startingPhi << std::endl;
    
    MatrixXd phi_old = gaussSeidelOneStep(startingRho, startingPhi, spaceBetweenLaticePoints);
    MatrixXd phi;

    outputFile_phi << phi_old << std::endl;

    double errorBar;
    do
    {
        phi = gaussSeidelOneStep(startingRho, phi_old, spaceBetweenLaticePoints);
        
        errorBar = (phi - phi_old).norm();
        
        phi_old = phi;

        outputFile_phi << phi_old << std::endl;
    }
    while (errorBar > epsilon);

    outputFile_phi.close();
}



//==============================================================================================================================
// one step of the Gauß-Seidel scheme computes the values for each inner lattice point
MatrixXd gaussSeidelOneStep(MatrixXd startingRho, MatrixXd phi_old, double spaceBetweenLaticePoints)
{
    uint N = startingRho.rows();

    MatrixXd phi = phi_old;

    for(uint i = 1; i < (N-1); i++)         /*change only the inner values*/
    {
        for(uint j = 1; j < (N-1); j++)     /*change only the inner values*/
        {
            phi(i,j) = (phi_old(i+1,j) + phi(i-1,j) + phi_old(i,j+1) + phi(i,j-1))/4 + (std::pow(spaceBetweenLaticePoints, 2) * startingRho(i,j))/4;
        }
    }
    return phi;
}



//==============================================================================================================================
// computes the analytical result for the starting conditions of subtask b)
void analyticalGaussSeidel(MatrixXd startingRho, MatrixXd startingPhi, double epsilon)
{
    std::ofstream outputFile_phi_anal;
    outputFile_phi_anal.open("data/Potential_b_anal.csv", std::ios_base::trunc);
    
    uint N = startingRho.rows();
    VectorXd x(N);
    VectorXd y(N);
    for(uint n = 0; n < N; n++)
    {
        x(n) = 1/(double)(N-1) * (double)n;
        y(n) = 1/(double)(N-1) * (double)n;
    }

    MatrixXd analyticPhi = startingPhi;

    double summand;
    double angle;
    uint counter;
    for(uint i = 1; i < (N-1); i++)         /*change only the inner values*/
    {
        for(uint j = 1; j < (N-1); j++)     /*change only the inner values*/
        {
            counter = 1;
            do
            {
                angle = counter*M_PI;
                summand = 2*(1 - cos(angle)) / (angle*sinh(angle)) * sin(angle*x(j)) * sinh(angle*y(i));
                // std::cout << counter << std::endl;
                analyticPhi(i,j) += summand;
                counter++;
            }
            while (summand > epsilon);
        }
    }
    outputFile_phi_anal << analyticPhi << std::endl;

    outputFile_phi_anal.close();
}



//==============================================================================================================================
// creates a starting charge distribution for each subtask a), b), c) and d)

MatrixXd startingChargeDistribution(uint numberOfLaticeRows, char subTask)
{
    MatrixXd startingRho = MatrixXd::Zero(numberOfLaticeRows, numberOfLaticeRows);
    
    switch(subTask)
    {
    case 'a':
        break;
    case 'b':
        break;
    case 'c':
        startingRho((numberOfLaticeRows-1)/2, (numberOfLaticeRows-1)/2) = 1;
        break;
    case 'd':
        startingRho(5, 5) = 1;
        startingRho(15, 15) = 1;
        startingRho(5, 15) = -1;
        startingRho(15, 5) = -1;
        break;
    }

    return startingRho;
}



//==============================================================================================================================
// creates a starting potential considering the dirichlet boundry conditions for each subtask a), b), c) and d)

MatrixXd startingPotential(uint numberOfLaticeRows, char subTask)
{
    MatrixXd startingPhi = MatrixXd::Zero(numberOfLaticeRows, numberOfLaticeRows);
    
    switch(subTask)
    {
    case 'a':
        startingPhi.block(1, 1, numberOfLaticeRows-2, numberOfLaticeRows-2) = MatrixXd::Constant(numberOfLaticeRows-2, numberOfLaticeRows-2, 1.);
        break;
    case 'b':
        for(uint i = 0; i < numberOfLaticeRows; i++)
        {
            startingPhi(numberOfLaticeRows-1, i) = 1.;
        }
        break;
    case 'c':
        break;
    case 'd':
        break;
    }
    return startingPhi;
}



int main()
{
    uint length = 1;
    double spaceBetweenLaticePoints = 0.05;
    uint numberOfLaticeRows = length/spaceBetweenLaticePoints + 1;

    double epsilon = std::pow(10, -5);
    
    std::string aufgabe = "abcd";
    for(uint i = 0; i < aufgabe.length()-1; i++)
    {
        gaussSeidel(startingChargeDistribution(numberOfLaticeRows, aufgabe[i])
                ,startingPotential(numberOfLaticeRows, aufgabe[i])
                ,spaceBetweenLaticePoints
                ,epsilon
                ,aufgabe[i]);
    }

    analyticalGaussSeidel(startingChargeDistribution(numberOfLaticeRows, 'b')
        ,startingPotential(numberOfLaticeRows, 'b')
        ,epsilon);


    return 0;
}
