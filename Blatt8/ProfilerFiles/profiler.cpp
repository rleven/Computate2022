#include <iostream>
#include <vector>
#include <string>
#include <chrono> // Ermöglicht Zeitmessungen

#include "profiler.h"

// Initialisiere 'numTimers' viele Timer ohne Namen
void Profiler::init ( int numTimers )
{
    duration = std::vector<long long>( numTimers, 0 );
    tStart = std::vector<std::chrono::high_resolution_clock::time_point>( numTimers );
    name = std::vector<std::string>( numTimers, "" );
}

// Initialisiere mehrere Timers mit Namen
// Die Namen sind nützlich, wenn print() verwendet wird,
//  weil dann Namen und Zeit zusammen ausgegeben werden
void Profiler::init ( const std::vector<std::string>& names )
{
    duration = std::vector<long long>( names.size(), 0 );
    tStart = std::vector<std::chrono::high_resolution_clock::time_point>( names.size() );
    name = names;
}

// Lösche die bisher mit Timer i gemessene Zeit
void Profiler::reset ( int i )
{
    checkSize( i );
    duration[i] = 0.;
}

// Lösche alle bisher gemessenen Zeiten
void Profiler::resetAll ()
{
    for ( long long & dur: duration )
        dur = 0.;
}

// Starte die Zeitmessung mit Timer i
//  Dies speichert nur den aktuellen Zeitpunkt in tStart[i]
//  Die gemessene Zeit wird erst für die Ausgabe gespeichert,
//   wenn stop(i) aufgerufen wird
void Profiler::start ( int i )
{
    checkSize( i );
    tStart[i] = std::chrono::high_resolution_clock::now();
}

// Addiere die Zeit seit dem letzten Start von i auf
//  Solange kein reset aufgerufen wird, können durch wiederholte
//   Anwendung von start() und stop() Zeiten aus mehreren
//   Schleifendurchläufen aufaddiert werden
void Profiler::stop ( int i )
{
    checkSize( i );
    auto tEnd = std::chrono::high_resolution_clock::now();
    duration[i] += std::chrono::duration_cast<std::chrono::nanoseconds>(tEnd - tStart[i]).count();
}

// Lies die Anzahl an Timern aus
int Profiler::getSize ()
{
    return duration.size();
}

// Lies die bisher aufaddierte Zeit von Timer i in Nanosekunden aus
//  Dies ist die Auflösung der Uhr, weshalb die Ausgabe als Integer erfolgt
long long Profiler::getTimeInNS ( int i )
{
    checkSize( i );
    return duration[i];
}

// Lies die bisher aufaddierte Zeit von Timer i in Sekunden aus
//  Die Ausgabe ist ein double, um auch kleinere Zeiträume auflösen zu können
double Profiler::getTimeInS ( int i )
{
    checkSize( i );
    return duration[i] * 1e-9;
}

// Lies Name von Timer i aus
std::string Profiler::getName ( int i )
{
    checkSize( i );
    return name[i];
}

// Von anderen Funktionen genutzter Zwischencheck,
//  ob Index für Timer valide ist
void Profiler::checkSize ( int i )
{
    if ( i >= duration.size() || i < 0 )
    {
        std::cerr << "ERROR in Profiler: " << i << " is no valid timer index\nNumTimers = " << duration.size() << std::endl;
        throw( "Timer index out of range" );
    }
}

// Ausgabe aller Timernamen mit aufaddierten Zeiten
void Profiler::print ( std::ostream& out )
{
    for ( int i = 0; i < Profiler::getSize(); i++ )
        out << "# ----- " << Profiler::getName(i) << ": " << Profiler::getTimeInS(i) << " s -----\n";
    out << std::flush;
}
