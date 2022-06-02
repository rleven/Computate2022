#include <iostream>
#include <cmath>
#include <fstream>
#include <Eigen/Dense>

using namespace Eigen;


uint orbitSize = 0;


double logisticMappingWarmlaufen(double r, double x_0, uint N_steps);
double cubicMappingWarmlaufen(double r, double x_0, uint N_steps);
VectorXd logisticMapping(double r, double x_0, double epsilon);
VectorXd cubicMapping(double r, double x_0, double epsilon);
void logisticBifurcationDiagram(uint x_0_count, double delta_r);
VectorXd linearlySpacedVector(double start, double end, uint count);



//==============================================================================================================================
// executes N steps of the logistic mapping for a given parameter r and the starting point x_0

double logisticMappingWarmlaufen(double r, double x_0, uint N_steps)
{   
    double x_next, x_old;
    x_old = x_0;

    for(uint n = 1; n < N_steps+1; n++)
    {
        x_next = r * x_old * (1 - x_old);
        x_old = x_next;
    }

    return x_next;
}



//==============================================================================================================================
// executes N steps of the cubic mapping for a given parameter r and the starting point x_0

double cubicMappingWarmlaufen(double r, double x_0, uint N_steps)
{   
    double x_next, x_old;
    x_old = x_0;
    
    for(uint n = 1; n < N_steps+1; n++)
    {
        x_next = r * x_old - pow(x_old, 3);
        x_old = x_next;
    }

    return x_next;
}



//==============================================================================================================================
// searches for the fixpoints or orbitals of the logistic mapping for a given parameter r and the starting point x_0

VectorXd logisticMapping(double r, double x_0, double epsilon)
{   
    VectorXd x = VectorXd::Zero(64);                        /*assuming there is chaos after an orbit size of 64*/
    x(0) = x_0;

    for(uint i = 1; i < 64; i++)
    {
        x(i) = r * x(i-1) * (1 - x(i-1));                   /*logistic mapping as iterating scheme*/
        orbitSize = 1;

        for(int j = i-1; j >= 0; j--)
        {
            orbitSize++;
            if(abs(x(i) - x(j)) < epsilon)                  /*check for a fixpoint or an orbital*/
            {
                return x;
            }
        }
    }

    return x;
}



//==============================================================================================================================
// searches for the fixpoints or orbitals of the cubic mapping for a given parameter r and the starting point x_0

VectorXd cubicMapping(double r, double x_0, double epsilon)
{   
    VectorXd x = VectorXd::Zero(64);                        /*assuming there is chaos after an orbit size of 64*/
    x(0) = x_0;

    for(uint i = 1; i < 64; i++)
    {
        x(i) = r * x(i-1) - pow(x(i-1), 3);                 /*cubic mapping as iterating scheme*/
        orbitSize = 1;

        for(int j = i-1; j >= 0; j--)
        {
            orbitSize++;
            if(abs(x(i) - x(j)) < epsilon)                  /*check for a fixpoint or an orbital*/
            {
                return x;
            }
        }
    }

    return x;
}



//==============================================================================================================================
// creates a bifurcation diagram for the logistic mapping

void logisticBifurcationDiagram(uint x_0_count, double delta_r)
{   
    VectorXd x_0_vec = linearlySpacedVector(0, 1, x_0_count);   
    double x_0 = 0;

    int r_min = 0;
    int r_max = 4;
    uint r_count = (r_max-r_min)/delta_r - 1;
    double r = 0;
    
    // Warmlaufen ------------------------------------------------------------------------------
    double warmlaufen_x;
    uint N_steps_warmlaufen = 10000;


    // finding fixpoints and orbitals ----------------------------------------------------------
    std::ofstream outputFile_fixpoints_logistic;
    outputFile_fixpoints_logistic.open("data/fixpoints_logistic.csv", std::ios_base::trunc);
    
    bool foundChaos_r = false;
    double chaos_r = r_max;
    
    VectorXd fixpoints;
    double epsilon = pow(10, -6);                       /*the maximum difference between two x from two iterations for them to be counted as one point*/
    for(int x_0_counter = 0; x_0_counter < x_0_count; x_0_counter++)
    {
        x_0 = x_0_vec(x_0_counter);
        
        foundChaos_r = false;

        r = 0;
        for(int r_counter = 0; r_counter < r_count; r_counter++)
        {
            r += delta_r;
            warmlaufen_x = logisticMappingWarmlaufen(r, x_0, N_steps_warmlaufen);
            fixpoints = logisticMapping(r, warmlaufen_x, epsilon);
            if((!foundChaos_r) && (orbitSize == 64)) {                             /*checks if you already found a r for which the orbit size is greater than 64*/
                if(r < chaos_r) {
                    chaos_r = r;
                }
                foundChaos_r = true;
            }
            outputFile_fixpoints_logistic << r << "\t" << fixpoints.transpose() << std::endl;
        }
    }
    std::cout << "Der r-Wert ab dem Chaos entsteht der logistischen Abb.:   " << chaos_r << std::endl;

    outputFile_fixpoints_logistic.close();
}



//==============================================================================================================================
// creates a bifurcation diagram for the logistic mapping

void cubicBifurcationDiagram(uint x_0_count, double delta_r)
{   
    VectorXd x_0_vec = linearlySpacedVector(-1, 1, x_0_count);   
    x_0_vec << -1, 1;   
    double x_0 = 0;

    int r_min = 0;
    int r_max = 3;
    uint r_count = (r_max-r_min)/delta_r - 1;
    double r = 0;
    
    // Warmlaufen ------------------------------------------------------------------------------
    double warmlaufen_x;
    uint N_steps_warmlaufen = 10000;


    // finding fixpoints and orbitals ----------------------------------------------------------
    std::ofstream outputFile_fixpoints_cubic;
    outputFile_fixpoints_cubic.open("data/fixpoints_cubic.csv", std::ios_base::trunc);
    
    bool foundChaos_r = false;
    double chaos_r = r_max;
    
    VectorXd fixpoints;
    double epsilon = pow(10, -6);                       /*the maximum difference between two x from two iterations for them to be counted as one point*/
    for(int x_0_counter = 0; x_0_counter < x_0_count; x_0_counter++)
    {
        x_0 = x_0_vec(x_0_counter);
        
        foundChaos_r = false;

        r = 0;
        for(int r_counter = 0; r_counter < r_count; r_counter++)
        {
            r += delta_r;
            warmlaufen_x = cubicMappingWarmlaufen(r, x_0, N_steps_warmlaufen);
            fixpoints = cubicMapping(r, warmlaufen_x, epsilon);
            if((!foundChaos_r) && (orbitSize == 64)) {                             /*checks if you already found a r for which the orbit size is greater than 64*/
                if(r < chaos_r) {
                    chaos_r = r;
                }
                foundChaos_r = true;
            }
            outputFile_fixpoints_cubic << r << "\t" << fixpoints.transpose() << std::endl;
        }
    }
    std::cout << "Der r-Wert ab dem Chaos entsteht der kubischen Abb.:   " << chaos_r << std::endl;

    outputFile_fixpoints_cubic.close();
}



//==============================================================================================================================
// create a vector with a given number of linearly spaced values in a given interval without the beginning and ending values

VectorXd linearlySpacedVector(double start, double end, uint count)
{
    double delta = abs(end-start)/(count+1.);
    VectorXd vec(count);
    vec(0) = start + delta;
    for(uint i = 1; i < count; i++)
    {
        vec(i) = vec(i-1) + delta;
    }
    return vec;
}


int main()
{
    uint x_0_count;
    double delta_r = pow(10, -3);

    x_0_count = 3;
    logisticBifurcationDiagram(x_0_count, delta_r);

    x_0_count = 2;
    cubicBifurcationDiagram(x_0_count, delta_r);

    return 0;
}
