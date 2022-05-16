#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

#include<random>

double L=10;

MatrixXd Verlett(double h, double t, MatrixXd R, MatrixXd V);
VectorXd force(VectorXd r1, MatrixXd R, int j);
VectorXd portal(VectorXd r1, VectorXd r2);
VectorXd cutoff(VectorXd r1, VectorXd r2);
VectorXd F(VectorXd r1, VectorXd r2);
MatrixXd Rmatrix();
MatrixXd Vmatrix(double T);
VectorXd velocity_of_center_of_mass(MatrixXd V);
double Ekin(MatrixXd V);


//===================================================================================================
// verlett algorithm

MatrixXd Verlett(double h, double t, MatrixXd R_0, MatrixXd V_0){
    int N = round(t/h);
    MatrixXd R = R_0;
    MatrixXd V = V_0;
    MatrixXd A(2, 16);

    ofstream output_file_Ekin, output_file_R;
    output_file_Ekin.open("Ekin.csv", std::ios_base::trunc);
    output_file_R.open("Bahnkurven.csv", std::ios_base::trunc);
    
    VectorXd E_kin(N);

    for(int i = 0; i < N; i++) /*begin of time loop*/
    {
        output_file_R << R << endl;

        // calculate the kinetic energy
        E_kin(i) = Ekin(V);
        
        // calculate the accelerations
        for(int j = 0; j < 16; j++)
        {
            A.col(j) = force(R.col(j), R, j); // divide by mass m=1
        }
        
        // calculate the positions taking the periodic boundry conditions into account
        for(int j = 0; j < 16; j++)
        {
            R.col(j) = R.col(j) + V.col(j)*h + 0.5*A.col(j)*h*h;
            if(R(0,j) > L){
                R(0,j) = fmod(R(0,j), L);
            }
            else if(R(0,j) < 0) {
                R(0,j) = L - fmod(abs(R(0,j)), L);
            }
            if(R(1,j) > L){
                R(1,j) = fmod(R(1,j), L);
            }
            else if(R(1,j) < 0) {
                R(1,j) = L - fmod(abs(R(1,j)), L);
            }
        }
        
        // calculate the velocities
        for(int j = 0; j < 16; j++)
        {
            V.col(j) = V.col(j) + 0.5*(force(R.col(j), R, j) + A.col(j))*h;
        }
    } /*end of time loop*/
    
    output_file_R.close();
    output_file_Ekin << E_kin; 
    output_file_Ekin.close();

    return R;
}



//================================================================================================
// calculate the total force of all masses acting on one mass (calls "portal()" for every single mass-mass interaction)

VectorXd force(VectorXd r1, MatrixXd R, int j){
    VectorXd totalforce(2);
    totalforce << 0, 0;
    for(int k = 0; k < 16; k++){
        if(k != j){
            totalforce += portal(r1, R.col(k));
        }
    }
    return totalforce;
}



//================================================================================================
// controls of two masses interact normaly or if they interact through the wall because of per. boundry conditions (calls "cutoff()")

VectorXd portal(VectorXd r1, VectorXd r2)
{
    string xRichtung, yRichtung;
    if((r2 - r1)(0) > L/2) {
        if(r2(0) < r1(0)) {
            r2(0) += L;
            xRichtung = "rechts";
        }
        if(r2(0) > r1(0)) {
            r2(0) -= L;
            xRichtung = "links";
        }
    }
    if((r2-r1)(1) > L/2) {
        if(r2(1) < r1(1)) {
            r2(1) += L;
            yRichtung = "oben";
        }
        if(r2(1) > r1(1)) {
            r2(1) -= L;
            yRichtung = "unten";
        }
    }
    VectorXd F(2);
    F = cutoff(r1, r2);

    return F;
}



//================================================================================================
// controls wether the interacting masses lie within the cutoff radius

VectorXd cutoff(VectorXd r1, VectorXd r2)
{
    double rc = L/2;
    double r = (r2 - r1).norm();
    if(r < rc) {
        return F(r1, r2);
    }
    else {
        VectorXd null(2);
        null << 0, 0;
        return null;
    }
}



//================================================================================================
// calculates the force of the mass at r2 on the mass at r1

VectorXd F(VectorXd r1, VectorXd r2)
{
    double r = (r2 - r1).norm();
    double K = 24  * (-pow(r, -7.) + 2*pow(r, -13.));
    VectorXd normal(2);
    normal = (r2 - r1)/r;
    return normal*K;
}



/*----------------------------------------------------------------------------------------------------------------------------
//================================================================================================
// calculates the potential energy between two masses

double P(VectorXd r1, VectorXd r2){
    double r = (r2-r1).norm();
    double Pot = 4 * (pow(r,-12.)-pow(r,-6.));
    return Pot;
}



// //================================================================================================
// calculate the total potential between all masses and one mass (calls "portal()" for every single mass-mass interaction)

double PotEnergie(MatrixXd R){
    double Gesamtpotential;
    for(int i=0; i<16; i++){
        for(int j=i+1; j<16; j++){
            Gesamtpotential += portal(R.col(i), R.col(j));
        }
    }

    return Gesamtpotential;
}
----------------------------------------------------------------------------------------------------------------------------*/



//================================================================================================
// creates matrix with the starting positions of the masses

MatrixXd Rmatrix(){
    MatrixXd R(2,16);
    VectorXd Relement(2);
    int zaehler=0;
    for(int n=0; n<4; n++){
        for(int m=0; m<4; m++){
            Relement << L/8*(1+2*n), L/8*(1+2*m);
            R.col(zaehler) = Relement;
            zaehler++;
        }
    }
    return R;
}



//================================================================================================
// creates matrix with the starting velocities of the masses
// matrix is created randomly under the following conditions:
//1) velocity_of_center_of_mass = 0
//2) starting temperature = T

MatrixXd Vmatrix(double T){
    MatrixXd V(2,16);
    mt19937 rnd(42);
    uniform_real_distribution<> dist(-1, 1);
    VectorXd Velement(2);
    for(int z = 0; z < 16; z++){
        Velement << dist(rnd), dist(rnd);
        V.col(z) = Velement;
    }

    VectorXd SPV(2);
    SPV = velocity_of_center_of_mass(V);
    for(int i = 0; i < 16; i++){
        V.col(i) = V.col(i) - SPV;
    }

    double summe = 0;
    for(int i = 0; i < 16; i++){
        summe += V.col(i).dot(V.col(i));
    }
    // double k_B = 1;
    double k_B = pow(1.380658, -23.);
    double skalKonst = 30 * k_B * T / summe;

    V *= sqrt(skalKonst);

    return V;
}



//================================================================================================
// calculates the center of mass velocity

VectorXd velocity_of_center_of_mass(MatrixXd V){
    VectorXd Vx(16);
    VectorXd Vy(16);
    Vx = V.row(0);
    Vy = V.row(1);
    VectorXd SPV(2);
    SPV << Vx.sum(), Vy.sum();
    return SPV/16.;
}


//================================================================================================
// calculates the kinetic energy of the system

double Ekin(MatrixXd V){
    double E = 0;
    for(int i=0; i<16; i++){
        E += V.col(i).dot(V.col(i));
    }
    return E/2;
}


//================================================================================================
//Hauptprogramm

int main(){

    double T = 1;
    MatrixXd R(2,16), V(2,16);
    R = Rmatrix();
    V = Vmatrix(T);

    double h=0.01;
    double t=100.;
    MatrixXd lsg_verlett = Verlett(h,t,R,V);

    return 0;
}
