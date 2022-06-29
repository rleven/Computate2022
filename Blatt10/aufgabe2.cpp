#include <iostream>
#include <cmath>
#include <fstream>
#include <Eigen/Dense>
#include <random>

using namespace Eigen;


// ========================================================================================================
// eine Standard-Gauß-Verteilung mit dem Box-Müller-Verfahren erzeugen
void boxMuellerMethod(uint count)
{
    std::ofstream outputFile;
    outputFile.open("data/BoxMueller.csv");

    std::mt19937 mt(std::random_device{}());
    std::uniform_real_distribution<double> uniformRandomNumber(0.0, 1.0);

    double u1, u2, c_help, x1, x2;

    for(uint i = 0; i < count; i++)
    {
        u1 = uniformRandomNumber(mt);
        u2 = uniformRandomNumber(mt);

        c_help = sqrt(-2.0 * log(u1));
        x1 = c_help * cos(2*M_PI * u2);
        x2 = c_help * sin(2*M_PI * u2);

        outputFile << x1 << "\t" << x2 << std::endl;
    }

    outputFile.close();
}


// ========================================================================================================
// eine Standard-Gauß-Verteilung mit dem zentralen Grenzwertsatz erzeugen
void zentralerGrenzwertsatz(uint count, uint sumCount)
{
    std::ofstream outputFile;
    outputFile.open("data/zentralerGrenzwertsatz.csv");

    std::mt19937 mt(std::random_device{}());
    std::uniform_real_distribution<double> uniformRandomNumber(0.0, 1.0);

    VectorXd uRanNum(sumCount);
    double S, sigma, mu, x;
    mu = 1/2;
    sigma = 1/sqrt(12);

    for(uint i = 0; i < count; i++)
    {
        for(uint n = 0; n < uRanNum.size(); n++)
        {
            uRanNum(n) = uniformRandomNumber(mt);
        }
        S = uRanNum.sum();
        x = (S - mu*sumCount)/(sigma*sqrt(sumCount));

        outputFile << x << std::endl;
    }

    outputFile.close();

}

int main()
{
    uint count = pow(10, 5);
    boxMuellerMethod(count);
    zentralerGrenzwertsatz(count, 12);

    return 0;
}
