#include <ios>
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

float f_1 (float x)
{
    return sin(x);
}

float f_2 (float x)
{
    if (x >= 0){
        return 2*floor(x/M_PI) - cos(fmod( x, M_PI )) + 1;
    }
    else{
        return 2*floor(x/M_PI) + cos(fmod( x, M_PI )) + 1;
    }

}

typedef float (*Function) (float);

float zweipunkt (Function fun, float x, float h)
{
    return (fun(x+h)-fun(x-h))/(2*h);
}

float vierpunkt (Function fun, float x, float h)
{
    return (-fun(x+2*h) +8*fun(x+h) -8*fun(x-h) +fun(x-2*h))/(12*h);
}

int main(){
    /* Definitions of variables */
    float x_value;
    x_value = M_PI;

    /* Set output files */
    ofstream teil_a1, teil_a2, teil_b1, teil_b2;
    teil_a1.open("data/teil_a1.txt", ios_base::trunc);
    teil_a2.open("data/teil_a2.txt", ios_base::trunc);
    teil_b1.open("data/teil_b1.txt", ios_base::trunc);
    teil_b2.open("data/teil_b2.txt", ios_base::trunc);
    
    teil_a1 << "#h    y";
    
    for (float h = pow(10,-3); h<0.1; h = h+0.00001) {
    teil_a1 << "\n" << h << "," << zweipunkt(f_1,x_value,h);
    }

    float h_value;
    h_value = pow(10,-2);

    teil_a1 << "#h    y    delta_y";

    for (float x = -M_PI ; x <= M_PI; x = x + 0.01) {
    teil_a2 << "\n" << x << "," << zweipunkt(f_1,x,h_value) << "," << abs(cos(x)-zweipunkt(f_1,x,h_value));
    }

    /*Aufgabenteil b*/

    

    /* Closing files */
    teil_a1.close();
    teil_a2.close();
    teil_b1.close();
    teil_b2.close();


    return 0;
}
