#define _USE_MATH_DEFINES

#include <ios>
#include <iostream>
#include <cmath>
#include <fstream>
#include <Eigen/Dense>

using namespace Eigen;

/* Berücksichtigung der Luftreibung, Windwiderstand, nach-unten-ziehende-Kraft und Magnus */

VectorXd Force(Vector3d v, double wind, double magni){
    //Definierung der Konstanten
    double cw=0.2;
    double g=9.81;
    double m=0.43;
    double A=0.038;
    double rho=1.3;
    double gamma=0.001;

    //Definierung der benötigten Vektoren
    Vector3d v_wind(wind, 0.0, 0.0);
    Vector3d magnus(0.0, 0.0, -magni);
    Vector3d e_z(0.0, 0.0, 1.0);

    //Gibt die gesamte resultierende Reibungs- /Ablenkunskraft aus
    return -( cw*rho*A * pow((v-v_wind).norm(), 2) * (v-v_wind) ) / (2.0*(v-v_wind).norm() * m ) - g*e_z + gamma*magnus.cross(v)/m;
}

/* Erstellt einen sieben dimensionalen Vektor für das Runge-Kutta Verfahren */

VectorXd bettervector(VectorXd y, double t, double wind, double magni){

    //Geschwindigkeit aus den letzten Komponenten des y-vektors
    Vector3d v = y.tail(3);

    VectorXd y_imperia(7);
    y_imperia << v, magni, Force(v, wind, magni);

    //Ausgabe des mächtigen 7D Vektors!
    return y_imperia;
}

/* Hauptfunktion für das Runge-Kutta Verfahren */

VectorXd quadruple_kutta(VectorXd bettervector(VectorXd, double, double, double), VectorXd y, double wind, double magni, double t_begin, double t_end, double h, double alpha, bool distance, bool trajectory, bool goal, bool edge){

    double goal_alpha = 0;
    double goal_edge = 0;
    double t = t_begin;

    VectorXd kutta1, kutta2, kutta3, kutta4;

    std::ofstream outfile;
    outfile.open("data/trajectory.csv", std::ios_base::app);

    while ( t <= t_end && (y(2) >= 0.11) ){
        //Berechnung von Runge-Kutta nach Skript
        kutta1 = h * bettervector(y, t, wind, magni);
        kutta2 = h * bettervector(y + kutta1/2.0, t + h/2.0, wind, magni);
        kutta3 = h * bettervector(y + kutta2/2.0, t + h/2.0, wind, magni);
        kutta4 = h * bettervector(y + kutta3, t + h, wind, magni);

        y += (kutta1 + 2.0*kutta2 + 2.0*kutta3 + kutta4) / 6.0;

        //Falls die Flugbahn gewollt ist
        if ( trajectory == true ){
            outfile << t << "   " << y.head(3).transpose() << "\n";
        }

        //Falls das Tor getroffen wird
        if ( goal_alpha == 0 and (y(0) >= 60) and (y(2) >= 0.11) and (y(2) <= 2.33) ){
            goal_alpha = 1;
        }
        else if ( goal_alpha == 0 and (y(0) >= 60) ){
            goal_alpha = 2;
        }

        //Falls das Tor aus der Ecke getroffen wird
        if ( goal_edge == 0 and (y(0) >= 34.11) and (y(0) <= 41.21) and (y(1) <= -0.11) and (y(2) >= 0.11) and (y(2) <= 2.33) ){
            goal_edge = 1;
        }
        else if ( goal_edge == 0 and (y(1) <= -0.11) ){
            goal_edge = 2;
        }

        t += h;
    }

    outfile.close();

    //Speichern der Flugweite
    if ( distance == true ){
        outfile.open("data/distance.csv", std::ios_base::app);
        outfile << alpha << "   " << y(0) << "\n";
        outfile.close();
    }

    //Speichern der Winkel, die das Tor treffen
    if ( goal_alpha == 1 and goal == true ){
        outfile.open("data/goalangle.csv", std::ios_base::app);
        outfile << alpha << "\n";
        outfile.close();
    }

    //Speichern der Kreisfrequenz, die das Tor treffen
    if ( goal_edge == 1 and edge == true ){
        outfile.open("data/goaledge.csv", std::ios_base::app);
        outfile << magni << "\n";
        outfile.close();
    }

    return y;
}

int main(){
    //Initiale Variablen definieren
    VectorXd y0(6), r0(3), ri(3), v0(3), ymagn0s(7);
    Vector3d vmagn0s(3);

    //Aufgabenteil b)
    for ( int i=0; i<=1000; i++){
        double v_0 = 30.0;
        double R = 0.11;
        double alpha = i * M_PI/2000.0;
        double magni = 0;

        v0 << v_0 * cos(alpha), 0, v_0 * sin(alpha);
        r0 << 0, 0, R;
        ymagn0s << r0, magni, v0;

        quadruple_kutta(bettervector, ymagn0s, 0, magni, 0, 1000, 1e-2, alpha, true, false, false, false);
    }

    //Aufgabenteil c)
    for ( int i=-10; i<=10; i+=5){
        double v_0 = 30.0;
        double R = 0.11;
        double alpha = 0.713142;
        double magni = 0;
        double wind = i;

        v0 << v_0 * cos(alpha), 0, v_0 * sin(alpha);
        r0 << 0, 0, R;
        ymagn0s << r0, magni, v0;

        quadruple_kutta(bettervector, ymagn0s, wind, magni, 0, 1000, 1e-2, alpha, false, true, false, false);
    }

    //Aufgabenteil d)
    for ( int i=0; i<=1000; i++){
        double v_0 = 40.0;
        double R = 0.11;
        double alpha = i * M_PI/2000.0;
        double magni = 0;

        v0 << v_0 * cos(alpha), 0, v_0 * sin(alpha);
        r0 << 0, 0, R;
        ymagn0s << r0, magni, v0;

        quadruple_kutta(bettervector, ymagn0s, 0, magni, 0, 1000, 1e-2, alpha, false, false, true, false);
    }

    //Aufgabenteil f)
    for ( int i=0; i<=1000; i++){
        double R = 0.11;
        double alpha = 1.0;
        double magni = i * 0.1;

        vmagn0s << 19.0, 2.0, 14.0;
        r0 << 0, 0, R;
        ymagn0s << r0, magni, vmagn0s;

        quadruple_kutta(bettervector, ymagn0s, 0, magni, 0, 1000, 1e-2, alpha, false, false, false, true);
    }

    return 0;
}
