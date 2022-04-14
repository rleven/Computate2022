#include <ios>
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

/* first function */
float f_1(float x)
{
    return sin(x);
}

/* second function */
float f_2(float x)
{
    if (x >= 0)
    {
        return 2*floor(x/M_PI) - cos(fmodf(x, M_PI)) + 1;
    }
    else
    {
        return 2*floor(x/M_PI) + cos(fmodf(x, M_PI)) + 1;
    }

}

/* derivative of the second function */
float f_2_ableitung(float x)
{
    if (x >= 0)
    {
        return sin(fmod(x, M_PI));
    }
    else
    {
        return -sin(fmod(x, M_PI));
    }

}

/* here we define a passing of a function */
typedef float (*Function)(float);

/* the two-point-rule for derivation is implemented */
float zweipunkt(Function fun, float x, float h)
{
    return (fun(x+h) - fun(x-h)) / (2*h);
}

/* the four-point-rule for derivation is implemented */
float vierpunkt(Function fun, float x, float h)
{
    return (-fun(x+2*h) + 8*fun(x+h) - 8*fun(x-h) + fun(x-2*h)) / (12*h);
}

/* the twofold two-point-rule for the second derivative is implemented */
float second_derivative(Function fun, float x, float h)
{
    return (fun(x+h) - 2*fun(x) + fun(x-h)) / (pow(h, 2));
}


int main()
{
    /* Set output files */
    ofstream teil_a1, teil_a2, teil_b1, teil_b2, teil_c1, teil_c2, teil_d1, teil_d2, teil_d3, teil_d4;
    teil_a1.open("data/teil_a1.txt", ios_base::trunc);
    teil_a2.open("data/teil_a2.txt", ios_base::trunc);
    teil_b1.open("data/teil_b1.txt", ios_base::trunc);
    teil_b2.open("data/teil_b2.txt", ios_base::trunc);
    teil_c1.open("data/teil_c1.txt", ios_base::trunc);
    teil_c2.open("data/teil_c2.txt", ios_base::trunc);
    teil_d1.open("data/teil_d1.txt", ios_base::trunc);
    teil_d2.open("data/teil_d2.txt", ios_base::trunc);
    teil_d3.open("data/teil_d3.txt", ios_base::trunc);
    teil_d4.open("data/teil_d4.txt", ios_base::trunc);
    
    //a)

    /* choose an arbitrary x value at which the selection of h takes place */
    float x_value_zweipunkt;
    x_value_zweipunkt = M_PI;

    /* write the data file to select a suitable step size h */
    teil_a1 << "#h    y";
    
    for (float h = pow(10, -3); h<0.1; h = h+0.00001)
    {
        teil_a1 << "\n" << h << "," << zweipunkt(f_1, x_value_zweipunkt, h);
    }

    float h_value_zweipunkt;
    h_value_zweipunkt = pow(10, -2);

    /* write the data file show the error from the analytical derivative */
    teil_a2 << "#h    y    delta_y";

    for (float x = -M_PI; x <= M_PI; x = x + h_value_zweipunkt)
    {
        teil_a2 << "\n" << x << "," << zweipunkt(f_1, x, h_value_zweipunkt) << "," << (cos(x) - zweipunkt(f_1, x, h_value_zweipunkt));
    }

    //b)

    /* choose an arbitrary x value at which the selection of h takes place */
    float x_value_zweite_abl;
    x_value_zweite_abl = M_PI/2;
    
    /* write the data file to select a suitable step size h */
    teil_b1 << "#h    y";
    
    for (float h = pow(10, -3); h<1; h = h+0.00001)
    {
        teil_b1 << "\n" << h << "," << second_derivative(f_1, x_value_zweite_abl, h);
    }

    float h_value_zweite_abl;
    h_value_zweite_abl = 7 * pow(10, -2);

    /* write the data file show the error from the analytical derivative */
    teil_b2 << "#h    y    delta_y";

    for (float x = -M_PI; x <= M_PI; x = x + h_value_zweite_abl)
    {
        teil_b2 << "\n" << x << "," << second_derivative(f_1, x, h_value_zweite_abl) << "," << (-sin(x) - second_derivative(f_1, x, h_value_zweite_abl));
    }

    //c)

    /* choose an arbitrary x value at which the selection of h takes place */
    float x_value_vier;
    x_value_vier = M_PI;

    /* write the data file to select a suitable step size h */
    teil_c1 << "#h    y";
    
    for (float h = pow(10, -5); h<1; h = h+0.00001)
    {
        teil_c1 << "\n" << h << "," << vierpunkt(f_1, x_value_vier, h);
    }

    float h_value_vier;
    h_value_vier = 1.5 * pow(10, -1);

    /* write the data file show the error from the analytical derivative */
    teil_c2 << "#h    y    delta_y";

    for (float x = -M_PI; x <= M_PI; x = x + 0.01)
    {
        teil_c2 << "\n" << x << "," << vierpunkt(f_1, x, h_value_vier) << "," << (cos(x) - vierpunkt(f_1, x, h_value_vier));
    }

    //d)

    /* choose an arbitrary x value at which the selection of h takes place */
    x_value_zweipunkt = M_PI/2;

    /* write the data file to select a suitable step size h */
    teil_d1 << "#h    y";
    
    for (float h = pow(10, -6); h<1; h = h+pow(10, -6))
    {
        teil_d1 << "\n" << h << "," << zweipunkt(f_2, x_value_zweipunkt, h);
    }

    h_value_zweipunkt = pow(10, -2);

    /* write the data file show the error from the analytical derivative */
    teil_d2 << "#h    y    delta_y";

    for (float x = -M_PI; x <= M_PI; x = x + h_value_zweipunkt)
    {
        teil_d2 << "\n" << x << "," << zweipunkt(f_2, x, h_value_zweipunkt) << "," << (f_2_ableitung(x) - zweipunkt(f_2, x, h_value_zweipunkt));
    }

    /* choose an arbitrary x value at which the selection of h takes place */
    x_value_vier = M_PI/2;

    /* write the data file to select a suitable step size h */
    teil_d3 << "#h    y";
    
    for (float h = pow(10, -5); h<1; h = h+0.00001)
    {
        teil_d3 << "\n" << h << "," << vierpunkt(f_2, x_value_vier, h);
    }

    h_value_vier = pow(10, -1);

    /* write the data file show the error from the analytical derivative */
    teil_d4 << "#h    y    delta_y";

    for (float x = -M_PI; x <= M_PI; x = x + 0.01)
    {
        teil_d4 << "\n" << x << "," << vierpunkt(f_2, x, h_value_vier) << "," << (f_2_ableitung(x) - vierpunkt(f_2, x, h_value_vier));
    }

    /* Closing files */
    teil_a1.close();
    teil_a2.close();
    teil_b1.close();
    teil_b2.close();
    teil_c1.close();
    teil_c2.close();
    teil_d1.close();
    teil_d2.close();
    teil_d3.close();
    teil_d4.close();


    return 0;
}
