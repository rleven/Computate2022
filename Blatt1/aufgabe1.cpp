#include <ios>
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

float f_1(float x){
    return sin(x);
}

float f_2(float x){
    if (x >= 0){
        return 2*floor(x/M_PI) - cos(fmod(x, M_PI)) + 1;
    }
    else{
        return 2*floor(x/M_PI) + cos(fmod(x, M_PI)) + 1;
    }

}

/* here we define a passing of a function */
typedef float (*Function)(float);

float zweipunkt(Function fun, float x, float h){
    return (fun(x+h)-fun(x-h))/(2*h);
}

float vierpunkt(Function fun, float x, float h){
    return (-fun(x+2*h) +8*fun(x+h) -8*fun(x-h) +fun(x-2*h))/(12*h);
}

/* the twofold two-point-rule for the second derivative is implemented */
float second_derivative(Function fun, float x, float h)
{
    return (fun(x+h) - 2*fun(x) + fun(x-h)) / (pow(h, 2));
}


int main()
{
    /* Set output files */
    ofstream teil_a1, teil_a2, teil_b1, teil_b2, teil_c1, teil_c2;
    teil_a1.open("data/teil_a1.txt", ios_base::trunc);
    teil_a2.open("data/teil_a2.txt", ios_base::trunc);
    teil_b1.open("data/teil_b1.txt", ios_base::trunc);
    teil_b2.open("data/teil_b2.txt", ios_base::trunc);
    teil_c1.open("data/teil_c1.txt", ios_base::trunc);
    teil_c2.open("data/teil_c2.txt", ios_base::trunc);
    
    //a)

    /* Definitions of variables */
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

    float x_value_zweite_abl;
    x_value_zweite_abl = M_PI/2;
    
    /* write the data file to select a suitable step size h */
    teil_b1 << "#h    y";
    
    for (float h = pow(10, -3); h<1; h = h+0.00001)
    {
        teil_b1 << "\n" << h << "," << second_derivative(f_1, x_value_zweite_abl, h);
    }

    float h_value_zweite_abl;
    h_value_zweite_abl = 5 * pow(10, -2);

    /* write the data file show the error from the analytical derivative */
    teil_b2 << "#h    y    delta_y";

    for (float x = -M_PI; x <= M_PI; x = x + h_value_zweite_abl)
    {
        teil_b2 << "\n" << x << "," << second_derivative(f_1, x, h_value_zweite_abl) << "," << (-sin(x) - second_derivative(f_1, x, h_value_zweite_abl));
    }

    //c)

    float x_value_vier;
    x_value_vier = M_PI;

    /* write the data file to select a suitable step size h */
    teil_c1 << "#h    y";
    
    for (float h = pow(10, -5); h<1; h = h+0.00001)
    {
        teil_c1 << "\n" << h << "," << vierpunkt(f_1, x_value_vier, h);
    }

    float h_value_vier;
    h_value_vier = pow(10, -1);

    /* write the data file show the error from the analytical derivative */
    teil_c2 << "#h    y    delta_y";

    for (float x = -M_PI; x <= M_PI; x = x + h_value_vier)
    {
        teil_c2 << "\n" << x << "," << vierpunkt(f_1, x, h_value_vier) << "," << (cos(x) - vierpunkt(f_1, x, h_value_vier));
    }

    /* Closing files */
    teil_a1.close();
    teil_a2.close();
    teil_b1.close();
    teil_b2.close();
    teil_c1.close();
    teil_c2.close();


    return 0;
}
