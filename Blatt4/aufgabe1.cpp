#include <array>
#include <ios>
#include <iostream>
#include <cmath>
#include <fstream>
#include <numeric>
#include <random>
#include <Eigen/Dense>

using namespace Eigen;

/* Für Idioten wie mich: m=1 ; o,e=1 ; A=L x L ; rc=L/2 ; h=0.01 */

/* Initialisierung */
std::array<double, 16> speedyboys(double T){
    std::mt19937 rnd;
    std::uniform_real_distribution<> dist(0, 1);
    std::array<double, 16> random_number;

    for(int i=0; i<16; i++){
        random_number[i] = (T+1.)*dist(rnd);
    }

    double sum = 0;

    for(int i=0; i<16; i++){
        sum += random_number[i];
    }

    if(sum!=0){
        for(int i=0; i<16; i++){
            random_number[i] = random_number[i]/sum - 0.0625;
        }
    }
    return random_number;
}

MatrixXd position(std::array<double, 16>(double), double L){
    MatrixXd pos(2, 16);
    for (int i=0; i<16; i+=4){
        for (int n=0; n<4; n++) {
        pos(0, i+n) = 1/8.*L*(1+2*n);
        pos(1, i+n) = 1/8.*L*(1+2*n);
        }
    }
}

int main(){
    speedyboys(30.0);
    return 0;
}
