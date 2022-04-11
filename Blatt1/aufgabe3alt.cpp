#include <ios>
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

double fkt(double y){
  return -y;
}


int main()
{
  /* Definitions */
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


  ofstream outfile, eulerdaten, symmdaten, truedaten; //defining out to file stream for general textfile and three files for matplotlib

  outfile.open("daten3.txt", ios_base::app);
  eulerdaten.open("eulerdaten.txt", ios_base::app);
  symmdaten.open("symmdaten.txt", ios_base::app);
  truedaten.open("truedaten.txt", ios_base::app);

  outfile << "Our chosen value for Delta t is 0.05" << endl;
  /*
  eulerdaten << "#x y";
  symmdaten << "#x y";
  truedaten << "#x y";
  */

  for (double t=0; t < 11; t++) {
    
    outfile<<"\n------------------------------\n";
    /* Eulers and symmetric Eulers Method is calculated */
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
    outfile<<"\nEulers Value of y at x = "<< t << " is " << yn;
    outfile<<"\nSymm Eulers Value of y at x = "<< t << " is " << s_yn;
    outfile<<"\nTrue Value of y at x = "<< t << " is " << exp(-t) << endl;

    /* Saving Euler Data */
    eulerdaten << "\n" << t << "," << yn;
    /* Saving symmetric Euler Data */
    symmdaten << "\n" << t << "," << s_yn;
    /* Saving true Data */
    truedaten << "\n" << t << "," << exp(-t);
    }
  outfile.close();
  eulerdaten.close();
  symmdaten.close();
  truedaten.close();

  return 0;
}