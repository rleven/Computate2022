#ifndef PROFILER_H
#define PROFILER_H

#include <chrono>

namespace Profiler {
    void             init                ( int numTimers );
    void             init                ( const std::vector<std::string>& names );
    void             reset               ( int i );
    void             resetAll            ();
    void             start               ( int i );
    void             stop                ( int i );
    int              getSize             ();
    double           getTimeInS          ( int i );
    long long        getTimeInNS         ( int i );
    std::string      getName             ( int i );

    void             checkSize           ( int i );
    void             print               ( std::ostream& out = std::cout );


    typedef std::chrono::high_resolution_clock::time_point timePoint;
    static std::vector<long long>       duration;
    static std::vector<timePoint>       tStart;
    static std::vector<std::string>     name;
}

#endif // PROFILER_H
