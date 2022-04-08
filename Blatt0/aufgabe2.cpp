#include <iostream>
#include <cmath>
using namespace std;

class Expression_1 {
  public:
    double result(double x);
};

double Expression_1::result(double x) {
  return 1/(sqrt(x))-1/(sqrt(x+1));
}

class Expression_2 {
  public:
    double result(double x);
};

double Expression_2::result(double x) {
  return (1 - cos(x))/(sin(x));
}


class Expression_3 {
  public:
    double result(double x, double del);
};

double Expression_3::result(double x, double del) {
  return sin(x + del) - sin(x);
}


int main() {

    double big_x, small_x, small_del, x;
    Expression_1 exp1;
    Expression_2 exp2;
    Expression_3 exp3;

    cout << "Enter a big number for x: ";
    cin >> big_x;

    //print first expression
    cout << " The first expression calculated directly from the formula yields: " << exp1.result(big_x) << "\n";

    cout << "Enter a small number for x: ";
    cin >> small_x;
    // calculate second expression normally
    cout << " The second expression calculated directly from the formula yields: " << exp2.result(small_x) << "\n"; 

    cout << "Enter a small number for delta: ";
    cin >> small_del;
    cout << "Also enter a number for x: ";
    cin >> x;
    //print third expression
    cout << " The third expression calculated directly from the formula yields: " << exp3.result(x,small_del) << "\n"; 

    cout << "Testing Big numbers for Expression 1: \n"; 
    for (double i = 1*pow(10,15); i < pow(10,17); i= i*1.5) {
        cout << " Expression1 with " << i << ": " << exp1.result(i) << "\n";
    }
    double i = 1;
    while (exp1.result(i) != 0) {
        i = i + pow(10,7);
    }
    cout << "\n" << " Expression1 with " << i << ": " << exp1.result(i) << "\n";

    return 0;
}