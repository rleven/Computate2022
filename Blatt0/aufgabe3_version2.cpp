#include <iostream>
#include <cmath>
using namespace std;

void Euler(double y0,double value, double delta){
  double x0 = 0;
  while(x0 < value){
    double recursion = y0*(1-delta);
    //cout << "Value: " << recursion << "\n";
    y0 = recursion;
    x0 = x0 + delta;
  }
  cout << "\t"<< "Euler: " << "\n";
  cout << "\t"<< "\t"<<"Letzter Wert: " << y0 << "\n";
  cout << "\t"<< "\t" <<"Richtiger Wert: " << exp(-value) << "\n";
  cout << "\t"<< "\t"<< "Abweichung: " << abs(y0-exp(-value)) << "\n";
}
void Symm_Euler(double y0,double y1,double value, double delta){
  double x0 = 0;
  while(x0 < value){
    double recursion = -2*delta*y1+y0;
    //cout << "Value: " << recursion << "\n";
    y0 = y1;
    y1 = recursion;
    x0 = x0 + delta;
  }
  cout << "\t"<< "Symmetrischer Euler: " << "\n";
  cout << "\t"<< "\t"<<"Letzter Wert: " << y1 << "\n";
  cout << "\t"<< "\t"<< "Richtiger Wert: " << exp(-value) << "\n";
  cout << "\t"<< "\t"<< "Abweichung: " << abs(y0-exp(-value)) << "\n";
}

int main()
{
  double delta = 0.01;
  for(int i = 0;i < 11; i++){
    cout << "Wert: " << i << "\n";
    Euler(1,i,delta);
    Symm_Euler(1,exp(-delta),i,delta);
  }
  return 0;
}