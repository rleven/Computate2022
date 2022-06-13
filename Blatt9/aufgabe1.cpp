#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <Eigen/Dense>

#include "profiler.h"

using namespace Eigen;

int main(){
    VectorXi N_lin = VectorXi::LinSpaced(1000, 1, 1000);
    VectorXd N_log = pow(2, ArrayXd::LinSpaced(30, 1, 30));

    MatrixXd M;
    VectorXd x, b;

    Profiler::init(3);

    std::ofstream outputFile;
    outputFile.open("data/Laufzeiten.csv");

    for(uint i = 0; i < N_lin.size(); i++)
    {
        // Erstellung der Matrix
        Profiler::reset(0);
        Profiler::start(0);
        M = MatrixXd::Random(N_lin(i), N_lin(i));
        Profiler::stop(0);
        b = VectorXd::Random(N_lin(i));

        // QR-Zerlegung
        Profiler::reset(1);
        ColPivHouseholderQR<MatrixXd> QR(M.rows(), M.cols());
        Profiler::start(1);
        QR.compute(M);
        Profiler::stop(1);

        // Lösen des LGS
        Profiler::reset(2);
        Profiler::start(2);
        x = QR.solve(b);
        Profiler::stop(2);

        outputFile << N_lin(i) << "\t" << Profiler::getTimeInS(0) << "\t" << Profiler::getTimeInS(1) << "\t" << Profiler::getTimeInS(2) << std::endl;
    }

    outputFile.close();

    return 0;
}
