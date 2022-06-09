#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // Für sort
#include <math.h> // Für sqrt

#include "profiler.h"

// Dies ist ein einfaches Beispiel zur Verwendung des mitgegebenen Profilers

int main( void )
{
    // BEISPIEL FÜR EINFACHES PROFILING
    // Das folgende Profiling misst einfach die Dauer eines einfachen Codeblocks
    std::cout << "\nBEISPIEL FÜR EINFACHES PROFILING\n";

    // Initialisiere 2 Timer ohne Namen
    Profiler::init( 2 );

    // Starte Timer 0
    Profiler::start( 0 );

    // Zu profilender Code
    std::vector<double> v ( 10000, 0. );
    for ( int i = 0; i < 10000; i++ )
        v[i] = (2. + i) / (5. + i);

    // Speichere Zeit von Timer 0
    Profiler::stop( 0 );

    // Gib Zeit von Timer 0 aus
    // Ausgabe in Nanosekunden (long long) oder Sekunden (double) möglich
    std::cout << "Timer 0: " << Profiler::getTimeInS( 0 ) << " seconds\t";
    std::cout << " or \t"    << Profiler::getTimeInNS( 0 ) << " nanoseconds \n";


    // BEISPIEL FÜR ADDITION MEHRERER ZEITEN
    // Das folgende Profiling überprüft, wie viel Zeit die einzelnen Programmteile
    //   über mehrere Schleifendurchläufe hinweg benötigen
    std::cout << "\nBEISPIEL FÜR ADDITION MEHRERER ZEITEN\n";

    // Timer sind noch von vorher initialisiert, Profiler::init also unnötig

    // Timer 0 soll nochmal verwendet werden, resette ihn dafür
    // Alternativ: Profiler::resetAll();
    Profiler::reset( 0 );

    // Durchlaufe eine Schleife, in der die Zeiten aufaddiert werden sollen
    for ( int N = 10000; N <= 50000; N += 10000 )
    {
        // Erstelle Daten: Gemessen von Timer 0
        Profiler::start( 0 );
        std::vector<double> w ( N, 0. );
        for ( int i = 0; i < 10000; i++ )
            w[i] = sqrt(2. + i) / (5. + i);
        Profiler::stop( 0 );

        // Sortiere Daten: Gemessen von Timer 1
        Profiler::start( 1 );
        std::sort( w.begin(), w.end() );
        Profiler::stop( 1 );

        // ACHTUNG: Auch start() und stop() haben selbst einen gewissen Overhead
        //          Dauert die gemessene Operation sehr kurz an, wird die Messung dadurch ungenau
        //          Daher wäre folgendes Profiling schlecht:
        //
        //          for ( long long i = 0; i < 18446744073709551615; i++)
        //              Profiler::start(0);
        //              v[i] = i; // Ich brauche kaum Zeit
        //              Profiler::stop(0);
    }

    // Zeiten aus jedem Schleifendurchlauf wurden aufaddiert
    // Gib nun die Zeiten aus
    std::cout << "Timer 0: " << Profiler::getTimeInS(0) << " s\n"
              << "Timer 1: " << Profiler::getTimeInS(1) << " s\n";



    // BEISPIEL FÜR ZWISCHENSPEICHERUNG DER ZEITEN
    // Hier werden die Zeiten in jedem Schleifendurchlauf zwischengespeichert,
    // Damit lassen sich einfacher Abschätzungen für größere Parameter N treffen
    //  und es lassen sich einfacher Programmteile vergleichen, die unterschiedlich mit N skalieren
    // Hier z.B. sollte man sehen, dass für kleine N die O(N)-Operation noch mehr Zeit benötigt, für
    //  größere N aber die O(N^4)-Operation dominiert. Ab welchem N sich das zeigt, kann jedoch
    //  abhängig vom Gerät und Compiler variiern
    std::cout << "\nBEISPIEL FÜR ZWISCHENSPEICHERUNG DER ZEITEN\n";

    // Timer sind noch von vorher initialisiert, Profiler::init also unnötig

    // Erstelle Vektoren zum Speichern der Zeiten
    std::vector<double> tLin ( 10 );
    std::vector<double> tQua ( 10 );

    // Durchlaufe eine Schleife, in der die Zeiten einzeln abgespeichert werden sollen
    for ( int i = 0; i < 10; i++ )
    {
        const int N = 10*(i+1);

        // Resette beide Timer für jeden Schleifendurchlauf
        Profiler::resetAll();

        // O(N)-Operation: Gemessen von Timer 0
        Profiler::start( 0 );
        std::vector<double> w ( N, 0. );
        for ( int i = 0; i < N; i++ )
        {
            // Der Aufruf ist diesmal komplexer, damit er für kleine N
            //  mehr Zeit als die O(N^4)-Operation benötigt
            w[i] = sqrt( sqrt(2. + i) / sqrt(5. + i) );
            for ( int j = 0; j < 1000; j++ )
                w[i] += sqrt( sqrt(2. + j) / sqrt(5. + j) );
        }
        Profiler::stop( 0 );

        // O(N^4)-Operation: Gemessen von Timer 1
        Profiler::start( 1 );
        for ( int i = 0; i < N; i++ )
            for ( int j = 0; j < N; j++ )
                for ( int k = 0; k < N; k++ )
                    for ( int l = 0; l < N; l++ )
                        w[i] -= i + j*j - k - l*l;
        Profiler::stop( 1 );

        // Speichere Zeiten in Vektor
        tLin[i] = Profiler::getTimeInS( 0 );
        tQua[i] = Profiler::getTimeInS( 1 );
    }

    // Gib Zeiten der Timer aus
    std::cout << "tLin[s] \t tQua[s]\n";
    for ( int i = 0; i < 10; i++ )
        std::cout << tLin[i] << '\t' << tQua[i] << '\n';

    // BEISPIEL FÜR VERSCHACHTELTE ZEITMESSUNG
    std::cout << "\nBEISPIEL FÜR VERSCHACHTELTE ZEITMESSUNG\n";

    // Diesmal initialisieren wir 3 Timer mit Namen
    Profiler::init( { "All", "Init", "Sort" } );

    // Timer 0 misst die Gesamtzeit
    Profiler::start( 0 );
    // Durchlaufe eine Schleife, in der die Zeiten aufaddiert werden sollen
    for ( int N = 10000; N <= 50000; N += 10000 )
    {
        // Erstelle Daten: Gemessen von Timer 1
        Profiler::start( 1 );
        std::vector<double> w ( N, 0. );
        for ( int i = 0; i < 10000; i++ )
            w[i] = sqrt(2. + i) / (5. + i);
        Profiler::stop( 1 );

        // Sortiere Daten: Gemessen von Timer 2
        Profiler::start( 2 );
        std::sort( w.begin(), w.end() );
        Profiler::stop( 2 );
    }
    Profiler::stop( 0 );

    // ACHTUNG: Bei Verschachtelunen misst der äußere Timer auch die Zeit mit,
    //          welche die Aufrufe von start() und stop() der inneren Timer benötigen

    // Gib Zeiten der Timer aus, diesmal mit eingebauter print-Funktion
    Profiler::print( std::cout );
}
