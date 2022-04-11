#include <iostream>
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
    float x;
    x = 0;
    /* Set output files */
    ofstream teil_a, teil2, teil3;
    teil_a.open("teil_a.txt", ios_base::app);
    
    teil_a << "#h    y";
    
    for (float h = 0.1; h<30; h = h+0.1) {
    teil_a << "\n" << h << "," << zweipunkt(f_1,x,h);
    }

    /* Closing files */
    teil_a.close();


    return 0;
}