#include <iostream>
#include <fstream>

#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Core>
#include <string>

using namespace Eigen;
double alpha;

MatrixXd rk4(int N, double t_start, double t_end, VectorXd y_start, VectorXd f(double, VectorXd), std::string filename = "") 
{
    // open file to save the computed values
    std::ofstream file_output;
    file_output.open(filename, std::ios_base::trunc);    

    // declare and initialize the needed variables
    VectorXd k1, k2, k3, k4;
    VectorXd y = y_start;
    MatrixXd y_matrix(N, 2);
    
    double h;
    // to calculate the slope for the first 4 steps for the adams and co. scheme (bad coding)
    if(N != 4)
    {
        h = (t_end - t_start) / N;
    }
    else if(N == 4)
    {
        h = 20./1000.;
    }
    double t = t_start;

    for (int n = 1; n <= N; n++)
    {
        // save the values in output file
        file_output << n << "   " << t << "   " << y.transpose() << std::endl;
        // save the values in a 2D-matrix
        y_matrix.row(n-1) = y;

        // compute the runge-kutta scheme in 4th order for the nth step
        k1 = h * f(t, y);
        k2 = h * f(t + h / 2., y + k1 / 2);
        k3 = h * f(t + h / 2., y + k2 / 2);
        k4 = h * f(t + h, y + k3);
        
        y += (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        
        // preperation for the next step
        t += h;
    }

    // file_output.close();

    return y_matrix;
}

MatrixXd adams_bashforth_moulton(int N, double t_start, double t_end, VectorXd y_start, VectorXd f(double, VectorXd), std::string filename = "")
{
    // open file to save the computed values
    std::ofstream file_output;
    file_output.open(filename, std::ios_base::trunc);    

    // declare and initialize the needed variables
    VectorXd v0, v1, v2, v3;
    VectorXd y = y_start;
    MatrixXd y_matrix(N, 2);

    double h = (t_end - t_start) / N;
    double t = t_start;

    // the first 4 values for the slope have to be calculated via another scheme (here runge-kutta of 4th order)
    MatrixXd v_start = rk4(4, t_start, t_end, y_start, f);
    v0 = v_start.row(0);
    v1 = v_start.row(1);
    v2 = v_start.row(2);
    v3 = v_start.row(3);

    // save the values in output file
    for(int i = 0; i <= 3; i++)
    {
        file_output << i << "   " << t << "   " << v_start.row(i) << std::endl;
        t += h;
    }
    // save the values in a 2D-matrix
    y_matrix.block(0, 0, 4, 2) = v_start;

    for (int n = 4; n <= N; n++)
    {
        // compute the adams scheme in for the nth step
        y +=  h / 24 * (55 * v0 - 59 * v1 + 37 * v2 - 9 * v3);
        t += h;

        // preperation for the next step
        v3 = v2;
        v2 = v1;
        v1 = v0;
        v0 = f(t, y);

        // save the values in output file
        file_output << n << "   " << t << "   " << y.transpose() << std::endl;
        // save the values in a 2D-matrix
        y_matrix.row(n-1) = y;
    }

    // file_output.close();

    return y_matrix;
}

// the DGL system of first order ordinary differential equations
VectorXd f(double t, VectorXd y)
{
    VectorXd func(2);
    func(0) = y(1);
    func(1) = -alpha*y(1) - y(0);

    return func;
}

int main()
{
    // declare and initialize the needed variables
    int dim = 1;
    VectorXd y_start(2*dim);
    y_start << 1, 0;

    alpha = 0.1;

    double N = 1000;
    double t_start = 0;
    double t_end = 20;

    /*a)*/
    MatrixXd y_matrix;
    alpha = -1;
    y_matrix = adams_bashforth_moulton(N, t_start, t_end, y_start, f, "data/aufgabe1_adams_minus1.csv");
    for(alpha = 0; alpha <= 2; alpha++)
    {
        y_matrix = adams_bashforth_moulton(N, t_start, t_end, y_start, f, "data/aufgabe1_adams_" + std::to_string(int(alpha)) + ".csv");
    }

    /*b)*/
    alpha = 0.1;
    y_matrix = adams_bashforth_moulton(N, t_start, t_end, y_start, f, "data/aufgabe1_adams_energieerhaltung.csv");

    /*c)*/

    // //============Start der Zeitmessung============
    // double time1 = 0.0, tstart;
    // tstart = clock();
    // //=============================================

    // MatrixXd m_adams = adams_bashforth_moulton(1e7, 0, 1e5, y_start, f, "Laufzeit_adams.csv");

    // //============Ende der Zeitmessung============
    // time1 += clock() - tstart;
    // time1 = time1/CLOCKS_PER_SEC; //Berechnungszeit in Sekunden
    // std::cout << time1 << std::endl;
    // //=============================================

    //     //============Start der Zeitmessung============
    // double time2 = 0.0, tstart2;
    // tstart2 = clock();
    // //=============================================

    // MatrixXd m_rk4 = rk4(1e7, 0, 1e5, y_start, f, "Laufzeit_rk4.csv");

    // //============Ende der Zeitmessung============
    // time2 += clock() - tstart2;
    // time2 = time2/CLOCKS_PER_SEC; //Berechnungszeit in Sekunden
    // std::cout << time2 << std::endl;
    // //=============================================

    return 0;
}
