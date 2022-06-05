#include <ios>
#include <iostream>
#include <cmath>
#include <fstream>
#include <Eigen/Dense>
#include <time.h>

using namespace Eigen;


MatrixXd initializeMatrix(int N);
MatrixXd householderAlgorithm(MatrixXd M);
MatrixXd iterativeQRdecomposition(MatrixXd M, uint iterationCount);
MatrixXd jacobiRotation(MatrixXd M, double epsilon);

//==============================================================================================================================
// initializes the matrix which EW you want to get
MatrixXd initializeMatrix(int N)
{
    MatrixXd M(N, N);
    for(uint i = 0; i < N; i++)
    {
        for(uint j = 0; j < N; j++)
        {
            M(i,j) = i + j;
            if(i == j) {
                M(i,j) += i;
            }
        }
    }

    return M;
}


//==============================================================================================================================
// uses the "householder algorithm" to bring the matrix to a tridiagonal form conserving its EW
MatrixXd householderAlgorithm(MatrixXd M)
{
    uint N = M.rows();
    MatrixXd P;
    MatrixXd S;
    VectorXd v;
    VectorXd unitVector = VectorXd::Zero(N);
    double k;
    VectorXd u;

    for(uint n = 1; n < N-1; n++)
    {
        // construct the vector v, thus the value k and thus the vector u
        v = M(seq(n, N-1), n-1);
        if(v(0) >= 0) {
            k = v.norm();
        }
        else {
            k = -v.norm();
        }
        unitVector = VectorXd::Zero(N-n);
        unitVector(0) = 1;
        u = (v - k*unitVector) / (v - k*unitVector).norm();

        // construct the transformation matrix using the vector u
        P = MatrixXd::Zero(N, N);
        P.block(0, 0, n, n) = MatrixXd::Identity(n, n);
        S = MatrixXd::Identity(N-n, N-n) - 2 * u * u.transpose();
        P.block(n, n, N-n, N-n) = S;

        // apply the transformation matrix to M
        M = P * M * P;

        // clean up the matrix so that very small values are rated as 0
        for(uint i = 0; i < N; i++) {
            for(uint j = 0; j < N; j++) {
                if(std::abs(M(i,j)) < std::pow(10, -14)) {
                    M(i,j) = 0;
                }
            }
        }
    }

    return M;
}


//==============================================================================================================================
// iterative algorithm that uses the "QR-Zerlegung" to transform a tridiagonal matrix to a diagonal form conserving its EW
MatrixXd iterativeQRdecomposition(MatrixXd M, uint iterationCount)
{
    uint N = M.rows();
    MatrixXd diagonalM = M;                                     /*matrix after each step*/
    MatrixXd tempDiagonalM = M;                                 /*matrix used in the QR decomposition*/
    MatrixXd Q;                                                 /*transform matrix*/
    MatrixXd P;                                                 /*Jacobi matrix*/
    double diagElement, secDiagElement;                         /*diagonal and secondary diagonal element*/
    double c, s, t;

    for(uint counter = 0; counter < iterationCount; counter++)
    {
        Q = MatrixXd::Identity(N, N);                           /*reset the transform matrix for each step*/

        // calculate the transform matrix Q as a product of N-1 Jacobi matrices P_(n,n+1)
        for(uint n = 0; n < N-1; n++)
        {
            diagElement = tempDiagonalM(n,n);
            secDiagElement = tempDiagonalM(n+1,n);
            if(diagElement != 0) {                              /*check if diagonal element is 0*/
                t = secDiagElement / diagElement;
                c = 1. / (sqrt(t*t + 1.));
                s = t * c;
            }
            else {
                c = 0.;
                s = 1.;
            }

            P = MatrixXd::Identity(N, N);
            P.block(n, n, 2, 2) << c, s,                        /*construct the Jacobi matrix*/
                                  -s, c;

            Q.transpose() = P * Q.transpose();                  /*construct the transform matrix*/
            tempDiagonalM = P * tempDiagonalM;                  /*rotate the lower secondary element away*/
        }
        diagonalM = Q.transpose() * (diagonalM * Q);            /*iteration step: get new matrix from old one*/
        tempDiagonalM = diagonalM;                              /*update the matrix for the next #qr decomposition*/
    }
    
    return diagonalM;
}


//==============================================================================================================================
// iterative algorithm that uses the "QR-Zerlegung" to transform a tridiagonal matrix to a diagonal form conserving its EW
MatrixXd jacobiRotation(MatrixXd M, double epsilon)
{
    uint N = M.rows();
    MatrixXd diagonalM = M;                                     /*matrix after each Jacobi rotation*/
    MatrixXd P;                                                 /*Jacobi matrix*/
    double off;                                                 /*the sum of not diagonal squares*/
    double max;                                                 /*maximal non-diagonal element according to amount*/
    uint i_max, j_max;                                          /*indices of this maximal element*/
    double theta;
    double c, s, t;

    // calculate starting off
    off = 0.;
    for(uint i = 0; i < N; i++)
    {
        for(uint j = 0; j < N; j++)
        {
            if(i != j) {
                off += pow(diagonalM(i,j), 2.);
            }
        }
    }


    while(off > epsilon)
    {
        // find the maximal non-diagonal element according to amount (betragsmäßig)
        max = 0.;
        for(uint i = 0; i < N; i++)
        {
            for(uint j = 0; j < N; j++)
            {
                if(((i!=j) && abs(diagonalM(i,j)) > max)) {
                    max = abs(diagonalM(i,j));
                    i_max = i;
                    j_max = j;
                }
            }
        }

        // construct the Jacobi matrix
        theta = (diagonalM(j_max,j_max) - diagonalM(i_max,i_max)) / (2.*diagonalM(i_max,j_max));
        t = (theta/abs(theta)) / (abs(theta) + sqrt(theta*theta + 1.));
        c = 1. / sqrt(t*t + 1.);
        s = t * c;

        P = MatrixXd::Identity(N,N);
        P(i_max,i_max) =  c;
        P(i_max,j_max) =  s;
        P(j_max,i_max) = -s;
        P(j_max,j_max) =  c;

        // iteration step: get new matrix from old one
        diagonalM = P.transpose() * diagonalM * P;

        // calculate off the check if its smaller than epsilon
        off = 0.;
        for(uint i = 0; i < N; i++)
        {
            for(uint j = 0; j < N; j++)
            {
                if(i != j) {
                    off += pow(diagonalM(i,j), 2.);
                }
            }
        }
    
    }
    return diagonalM;
}


int main()
{
    double time, startTime;

    MatrixXd M;
    MatrixXd tridiagonalM;
    MatrixXd diagonalM;

    uint matrixSize[] = {10, 100, 1000};

    // diagonalize with iterative QR algorithm
    uint iterationCount[] = {1000, 1000, 10};
    for(uint i = 0; i < sizeof(matrixSize)/sizeof(matrixSize[0]); i++)
    {
        std::ofstream outputFile;
        outputFile.open("data/Eigenwerte_QR_" + std::to_string(matrixSize[i]) + ".csv", std::ios_base::trunc);
        
        M = initializeMatrix(matrixSize[i]);
        tridiagonalM = householderAlgorithm(M);
        
        /***time measurement***/
        /*******************************************/ 
        // time = 0.0;
        startTime = clock();

        diagonalM = iterativeQRdecomposition(tridiagonalM, iterationCount[i]);

        time = clock() - startTime;
        time = time / CLOCKS_PER_SEC;
        /*******************************************/ 
        
        VectorXd EW = diagonalM.diagonal();
        std::sort(EW.data(), EW.data()+EW.size());                          /*sort the EW for better comparison*/
        outputFile << "Laufzeit:  " << time << "s\n\n" << "Eigenwerte mit QR Iteration:\n" << EW << std::endl;
        outputFile.close();
    }

    // diagonalize with iterative Jacobi algorithm
    double epsilon[] = {pow(10, -6), pow(10, -6), 1};
    for(uint i = 0; i < sizeof(matrixSize)/sizeof(matrixSize[0]); i++)
    {
        std::ofstream outputFile;
        outputFile.open("data/Eigenwerte_Jacobi_" + std::to_string(matrixSize[i]) + ".csv", std::ios_base::trunc);
        
        M = initializeMatrix(matrixSize[i]);

        /***time measurement***/
        /*******************************************/ 
        // time = 0.0;
        startTime = clock();

        diagonalM = jacobiRotation(M, epsilon[i]);

        time = clock() - startTime;
        time = time / CLOCKS_PER_SEC;
        /*******************************************/ 
        
        outputFile << "Laufzeit:  " << time << "s\n\n" << "Eigenwerte mit Jacobi Iteration:\n" << diagonalM.diagonal() << std::endl;
        outputFile.close();
    }

    return 0;
}
