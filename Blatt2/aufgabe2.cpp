#include <ios>
#include <iostream>
#include <cmath>
#include <vector>
#include <array>
#include <fstream>


/*get acceleration for mass m caused by gravitational force*/
std::array<double,2> beschleunigung(std::array<double,2> a, int m, std::array<double,2> r_1, std::array<double,2> r_2)
{
    double G = 6.67430 * pow(10, -11);
    a[0] = -G * m * 1/pow(pow(r_1[0] - r_2[0], 2) + pow(r_1[1] - r_2[1], 2), 1.5) * (r_1[0] - r_2[0]);
    a[1] = -G * m * 1/pow(pow(r_1[0] - r_2[0], 2) + pow(r_1[1] - r_2[1], 2), 1.5) * (r_1[1] - r_2[1]);

    return a;
}

void euler(double h, double T, int m_1, int m_2, std::array<double,2> r_1_start, std::array<double,2> r_2_start, std::array<double,2> v_1_start, std::array<double,2> v_2_start, std::array<double,2> a)
{
    std::ofstream teil_a1;
    teil_a1.open("data/teil_a1.txt", std::ios_base::trunc);

    std::array<double,2> r_1_prev = r_1_start;
    std::array<double,2> v_1_prev = v_1_start;
    std::array<double,2> r_2_prev = r_2_start;
    std::array<double,2> v_2_prev = v_2_start;
    std::array<double,2> r_1_next;
    std::array<double,2> v_1_next;
    std::array<double,2> r_2_next;
    std::array<double,2> v_2_next;

    std::array<double,2> beschl;
    double N = T / h;

    for(int n=1; n<N; n++)
    {
        /*compute the values of mass 1 for the nth step*/
        beschl = beschleunigung(a, m_1, r_1_prev, r_2_prev);

        r_1_next[0] = r_1_prev[0] + (v_1_prev[0] * h);
        v_1_next[0] = v_1_prev[0] + (beschl[0] / m_1 * h);
        r_1_next[1] = r_1_prev[1] + (v_1_prev[1] * h);
        v_1_next[1] = v_1_prev[1] + (beschl[1] / m_1 * h);

        /*compute the values of mass 1 for the nth step*/
        beschl = beschleunigung(a, m_2, r_1_prev, r_2_prev);

        r_2_next[0] = r_2_prev[0] + (v_2_prev[0] * h);
        v_2_next[0] = v_2_prev[0] + (beschl[0] / m_2 * h);
        r_2_next[1] = r_2_prev[1] + (v_2_prev[1] * h);
        v_2_next[1] = v_2_prev[1] + (beschl[1] / m_2 * h);

        teil_a1 << "\n" << r_1_next[0] << "," << r_1_next[1] << "," << r_2_next[0] << "," << r_2_next[1] << "," << v_1_next[0] << "," << v_1_next[1] << v_2_next[0] << "," << v_2_next[1];
        
        /*overwrite values for next loop*/
        r_1_prev = r_1_next;
        v_1_prev = v_1_next;
        r_2_prev = r_2_next;
        v_2_prev = v_2_next;
    }

    teil_a1.close();
}

int main()
{
    /*initialize the starting values*/
    int m_1 = 1;
    int m_2 = 2;

    /*the first argument in the array is always the x- and the second argument is always the y-coordinate*/
    std::array<double,2> r_1_start = {0, 1};
    std::array<double,2> r_2_start = {0, -0.5};
    std::array<double,2> v_1_start = {0.8, 0};
    std::array<double,2> v_2_start = {-0.4, 0};

    std::array<double,2> a;

    // std::array<double,2> ptr = beschleunigung(a, m_1, r_1_start, r_2_start);

    // std::cout << ptr[0] << "\n" << ptr[1];

    double T = 100;
    double h = 10000;
    euler(h, T, m_1, m_2, r_1_start, r_2_start, v_1_start, v_2_start, a);

    return 0;
}