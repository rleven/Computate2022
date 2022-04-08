#include <iostream>
#include <cmath>
using namespace std;

double fkt(double y){
  return -y;
}


int main()
{
  float x0, y0, delt, yn;
  float s_x0, s_y0, s_yn, s_y1;
  int i, n;

  x0 = 0;
  s_x0 = 0;
  y0 = 1;
  s_y0 = 1;
  n = 20;
  delt = 0.05; // Delta t
  s_y1 = exp(-delt);


  for (double t=0; t < 11; t++) {

    /* Euler's Method */
    cout<<"\n------------------------------\n";

    for(i=0; i < n; i++)
    {
      yn = y0*(1-delt);
      y0 = yn;
      x0 = x0+delt;

      s_yn = -2*delt*s_y1+s_y0;
      s_y0 = s_y1;
      s_y1 = s_yn;
      s_x0 = s_x0+delt;
    }

    /* Displaying result */
    cout<<"\nEulers Value of y at x = "<< t << " is " << yn;
    cout<<"\nSymm Eulers Value of y at x = "<< t << " is " << s_yn;
    cout<<"\nTrue Value of y at x = "<< t << " is " << exp(-t);
    }


  return 0;
}